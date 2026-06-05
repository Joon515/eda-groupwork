"""Reusable PyUVM FIFO agents, drivers, sequencers, and monitors."""

from __future__ import annotations

from typing import Any

import cocotb  # pyright: ignore[reportMissingImports]
import pyuvm  # pyright: ignore[reportMissingImports]
from cocotb.triggers import NextTimeStep, ReadOnly, RisingEdge
from cocotb.utils import get_sim_time

from .fifo_config import FifoConfig, get_fifo_config
from .fifo_item import (  # pyright: ignore[reportMissingImports]
    READ,
    WRITE,
    FifoCommandItem,
    FifoReadObservation,
    FifoWriteObservation,
)


def _as_bool(signal: Any) -> bool:
    return bool(int(signal.value))


def _as_int(signal: Any) -> int:
    return int(signal.value)


def _optional_bool(dut: Any, name: str) -> bool:
    signal = getattr(dut, name, None)
    return False if signal is None else _as_bool(signal)


def _require_dut(cfg: FifoConfig, component_name: str) -> Any:
    if cfg.dut is None:
        raise ValueError(f"{component_name} requires FifoConfig.dut to be set")
    return cfg.dut


def _coerce_active(value: Any) -> bool:
    if isinstance(value, str):
        return value.strip().lower() not in {"0", "false", "f", "no", "n", "off", "passive"}
    return bool(value)


class FifoWriteSequencer(pyuvm.uvm_sequencer):
    """Sequencer for write-domain FIFO command items."""


class FifoReadSequencer(pyuvm.uvm_sequencer):
    """Sequencer for read-domain FIFO command items."""


class FifoWriteDriver(pyuvm.uvm_driver):
    """Drive write-domain commands onto ``winc``/``wdata``."""

    def build_phase(self) -> None:
        super().build_phase()
        self.cfg = get_fifo_config(self)
        self.dut = _require_dut(self.cfg, self.get_full_name())

    async def run_phase(self) -> None:
        getattr(self.dut, "winc").value = 0
        getattr(self.dut, "wdata").value = 0

        await RisingEdge(getattr(self.dut, "wclk"))
        while not _as_bool(getattr(self.dut, "wrst")):
            await RisingEdge(getattr(self.dut, "wclk"))

        while True:
            cmd = await self.seq_item_port.get_next_item()
            try:
                await self._drive_command(cmd)
            finally:
                self.seq_item_port.item_done()

    async def _drive_command(self, cmd: FifoCommandItem) -> None:
        for _ in range(max(0, int(cmd.delay))):
            getattr(self.dut, "winc").value = 0
            await RisingEdge(getattr(self.dut, "wclk"))

        if cmd.kind == WRITE:
            if cmd.allow_when_full:
                await self._wait_for_write_policy(cmd)
                await NextTimeStep()
            getattr(self.dut, "wdata").value = cmd.masked_data(self.cfg.width)
            getattr(self.dut, "winc").value = 1
            await RisingEdge(getattr(self.dut, "wclk"))
            await ReadOnly()
            await NextTimeStep()
            getattr(self.dut, "winc").value = 0
            await RisingEdge(getattr(self.dut, "wclk"))
        else:
            getattr(self.dut, "winc").value = 0
            await RisingEdge(getattr(self.dut, "wclk"))

    async def _wait_for_write_policy(self, cmd: FifoCommandItem) -> None:
        expected_full = bool(cmd.allow_when_full)
        while True:
            await RisingEdge(getattr(self.dut, "wclk"))
            await ReadOnly()
            if _as_bool(getattr(self.dut, "wfull")) == expected_full:
                return


class FifoReadDriver(pyuvm.uvm_driver):
    """Drive read-domain commands onto ``rinc``."""

    def build_phase(self) -> None:
        super().build_phase()
        self.cfg = get_fifo_config(self)
        self.dut = _require_dut(self.cfg, self.get_full_name())

    async def run_phase(self) -> None:
        getattr(self.dut, "rinc").value = 0

        await RisingEdge(getattr(self.dut, "rclk"))
        while not _as_bool(getattr(self.dut, "rrst")):
            await RisingEdge(getattr(self.dut, "rclk"))

        while True:
            cmd = await self.seq_item_port.get_next_item()
            try:
                await self._drive_command(cmd)
            finally:
                self.seq_item_port.item_done()

    async def _drive_command(self, cmd: FifoCommandItem) -> None:
        for _ in range(max(0, int(cmd.delay))):
            getattr(self.dut, "rinc").value = 0
            await RisingEdge(getattr(self.dut, "rclk"))

        if cmd.kind == READ:
            if cmd.allow_when_empty:
                await self._wait_for_read_policy(cmd)
                await NextTimeStep()
            getattr(self.dut, "rinc").value = 1
            await RisingEdge(getattr(self.dut, "rclk"))
            await ReadOnly()
            await NextTimeStep()
            getattr(self.dut, "rinc").value = 0
            await RisingEdge(getattr(self.dut, "rclk"))
        else:
            getattr(self.dut, "rinc").value = 0
            await RisingEdge(getattr(self.dut, "rclk"))

    async def _wait_for_read_policy(self, cmd: FifoCommandItem) -> None:
        expected_empty = bool(cmd.allow_when_empty)
        while True:
            await RisingEdge(getattr(self.dut, "rclk"))
            await ReadOnly()
            if _as_bool(getattr(self.dut, "rempty")) == expected_empty:
                return


class FifoWriteMonitor(pyuvm.uvm_monitor):
    """Publish write-domain observations after stable ``wclk`` edges."""

    def build_phase(self) -> None:
        super().build_phase()
        self.cfg = get_fifo_config(self)
        self.dut = _require_dut(self.cfg, self.get_full_name())
        self.analysis_port = pyuvm.uvm_analysis_port("analysis_port", self)

    async def run_phase(self) -> None:
        previous_winc = False
        while True:
            await RisingEdge(getattr(self.dut, "wclk"))
            await ReadOnly()
            if not _as_bool(getattr(self.dut, "wrst")):
                previous_winc = False
                continue

            current_winc = _as_bool(getattr(self.dut, "winc"))
            attempted = current_winc and not previous_winc
            previous_winc = current_winc
            wfull = _as_bool(getattr(self.dut, "wfull"))
            observation = FifoWriteObservation(
                attempted=attempted,
                accepted=attempted and not wfull,
                data=_as_int(getattr(self.dut, "wdata")),
                wfull=wfull,
                walmost_full=_optional_bool(self.dut, "walmost_full"),
                sim_time=get_sim_time(),
            )
            self.analysis_port.write(observation)


class FifoReadMonitor(pyuvm.uvm_monitor):
    """Publish read-domain observations after stable ``rclk`` edges."""

    def build_phase(self) -> None:
        super().build_phase()
        self.cfg = get_fifo_config(self)
        self.dut = _require_dut(self.cfg, self.get_full_name())
        self.analysis_port = pyuvm.uvm_analysis_port("analysis_port", self)

    async def run_phase(self) -> None:
        previous_rinc = False
        while True:
            await RisingEdge(getattr(self.dut, "rclk"))
            await ReadOnly()
            if not _as_bool(getattr(self.dut, "rrst")):
                previous_rinc = False
                continue

            current_rinc = _as_bool(getattr(self.dut, "rinc"))
            attempted = current_rinc and not previous_rinc
            previous_rinc = current_rinc
            rempty = _as_bool(getattr(self.dut, "rempty"))
            accepted = attempted and not rempty
            ralmost_empty = _optional_bool(self.dut, "ralmost_empty")
            if accepted:
                if int(self.cfg.read_latency) <= 0:
                    observation = FifoReadObservation(
                        attempted=True,
                        accepted=True,
                        data=_as_int(getattr(self.dut, "rdata")),
                        rempty=rempty,
                        ralmost_empty=ralmost_empty,
                        sim_time=get_sim_time(),
                    )
                    self.analysis_port.write(observation)
                else:
                    cocotb.start_soon(self._publish_accepted_read(rempty, ralmost_empty))
            else:
                observation = FifoReadObservation(
                    attempted=attempted,
                    accepted=False,
                    data=_as_int(getattr(self.dut, "rdata")),
                    rempty=rempty,
                    ralmost_empty=ralmost_empty,
                    sim_time=get_sim_time(),
                )
                self.analysis_port.write(observation)

    async def _publish_accepted_read(self, rempty: bool, ralmost_empty: bool) -> None:
        for _ in range(max(0, int(self.cfg.read_latency))):
            await RisingEdge(getattr(self.dut, "rclk"))
        await ReadOnly()
        observation = FifoReadObservation(
            attempted=True,
            accepted=True,
            data=_as_int(getattr(self.dut, "rdata")),
            rempty=rempty,
            ralmost_empty=ralmost_empty,
            sim_time=get_sim_time(),
        )
        self.analysis_port.write(observation)


class _FifoAgentBase(pyuvm.uvm_agent):
    sequencer_type: type[pyuvm.uvm_sequencer]
    driver_type: type[pyuvm.uvm_driver]
    monitor_type: type[pyuvm.uvm_monitor]

    def __init__(self, name: str, parent: pyuvm.uvm_component | None, is_active: bool | None = None) -> None:
        super().__init__(name, parent)
        self._is_active_arg = is_active
        self.is_active = True if is_active is None else bool(is_active)
        self.sequencer = None
        self.driver = None
        self.monitor = None

    def build_phase(self) -> None:
        super().build_phase()
        self.is_active = self._configured_active()
        if self.is_active:
            self.sequencer = self.sequencer_type("sequencer", self)
            self.driver = self.driver_type("driver", self)
        self.monitor = self.monitor_type("monitor", self)

    def connect_phase(self) -> None:
        super().connect_phase()
        if self.is_active and self.driver is not None and self.sequencer is not None:
            self.driver.seq_item_port.connect(self.sequencer.seq_item_export)

    def _configured_active(self) -> bool:
        if self._is_active_arg is not None:
            return bool(self._is_active_arg)
        try:
            configured = pyuvm.ConfigDB().get(self, "", "is_active")
        except Exception:
            return True
        return True if configured is None else _coerce_active(configured)


class FifoWriteAgent(_FifoAgentBase):
    """Write-domain FIFO agent; active builds sequencer/driver/monitor."""

    sequencer_type = FifoWriteSequencer
    driver_type = FifoWriteDriver
    monitor_type = FifoWriteMonitor


class FifoReadAgent(_FifoAgentBase):
    """Read-domain FIFO agent; active builds sequencer/driver/monitor."""

    sequencer_type = FifoReadSequencer
    driver_type = FifoReadDriver
    monitor_type = FifoReadMonitor


__all__ = [
    "FifoReadAgent",
    "FifoReadDriver",
    "FifoReadMonitor",
    "FifoReadSequencer",
    "FifoWriteAgent",
    "FifoWriteDriver",
    "FifoWriteMonitor",
    "FifoWriteSequencer",
]
