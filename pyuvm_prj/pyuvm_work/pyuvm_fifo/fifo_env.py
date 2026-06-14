"""PyUVM FIFO environment assembled from reusable agents and subscribers."""

from __future__ import annotations

from typing import Any

import pyuvm  # pyright: ignore[reportMissingImports]

from .fifo_agent import FifoReadAgent, FifoWriteAgent  # pyright: ignore[reportMissingImports]
from .fifo_config import FifoConfig, get_fifo_config, set_fifo_config
from .fifo_coverage import FifoCoverage  # pyright: ignore[reportMissingImports]
from .fifo_scoreboard import FifoScoreboard


_REQUIRED_DUT_SIGNALS = (
    "wclk",
    "wrst",
    "winc",
    "wdata",
    "wfull",
    "rclk",
    "rrst",
    "rinc",
    "rdata",
    "rempty",
)


class FifoEnv(pyuvm.uvm_env):
    """Standard FIFO verification environment.

    The environment owns construction and TLM wiring only. Agents drive and
    monitor the DUT, while the scoreboard and coverage collector consume the
    monitor analysis streams.
    """

    def __init__(self, name: str = "fifo_env", parent: pyuvm.uvm_component | None = None) -> None:
        super().__init__(name, parent)
        self.cfg: FifoConfig | None = None
        self.write_agent: FifoWriteAgent | None = None
        self.read_agent: FifoReadAgent | None = None
        self.scoreboard: FifoScoreboard | None = None
        self.coverage: FifoCoverage | None = None

    def build_phase(self) -> None:
        super().build_phase()
        self.cfg = self._require_config()
        set_fifo_config(self, self.cfg)

        self.write_agent = FifoWriteAgent("write_agent", self)
        self.read_agent = FifoReadAgent("read_agent", self)
        self.scoreboard = FifoScoreboard("scoreboard", self, width=self.cfg.width, depth=self.cfg.depth)
        self.coverage = FifoCoverage("coverage", self, width=self.cfg.width, depth=self.cfg.depth)

    def connect_phase(self) -> None:
        super().connect_phase()
        write_port = self._analysis_port(self.write_agent, "write")
        read_port = self._analysis_port(self.read_agent, "read")

        scoreboard = self._require_child(self.scoreboard, "scoreboard")
        coverage = self._require_child(self.coverage, "coverage")
        write_port.connect(scoreboard.write_export)
        write_port.connect(coverage.write_export)
        read_port.connect(scoreboard.read_export)
        read_port.connect(coverage.read_export)

    def check_phase(self) -> None:
        super().check_phase()
        self._require_child(self.scoreboard, "scoreboard").check_phase()

    def report_phase(self) -> None:
        super().report_phase()
        for child_name, child in (
            ("scoreboard", self.scoreboard),
            ("coverage", self.coverage),
        ):
            self._call_report_phase(self._require_child(child, child_name))

    def _require_config(self) -> FifoConfig:
        try:
            cfg = get_fifo_config(self)
        except Exception as exc:
            raise RuntimeError(
                f"{self.get_full_name()} requires a FifoConfig in ConfigDB under key 'fifo_config'"
            ) from exc

        if cfg.dut is None:
            raise ValueError(f"{self.get_full_name()} requires FifoConfig.dut to be set")
        missing = [name for name in _REQUIRED_DUT_SIGNALS if not hasattr(cfg.dut, name)]
        if missing:
            raise ValueError(
                f"{self.get_full_name()} FifoConfig.dut is missing required signal(s): "
                + ", ".join(missing)
            )
        return cfg

    @staticmethod
    def _require_child(component: Any, name: str) -> Any:
        if component is None:
            raise RuntimeError(f"FifoEnv {name} was not built before phase use")
        return component

    def _analysis_port(self, agent: Any, domain: str) -> Any:
        agent = self._require_child(agent, f"{domain}_agent")
        monitor = getattr(agent, "monitor", None)
        for owner, attr in ((monitor, "analysis_port"), (agent, "analysis_port"), (agent, "ap")):
            if owner is not None and hasattr(owner, attr):
                return getattr(owner, attr)
        raise RuntimeError(
            f"{self.get_full_name()} could not find {domain} monitor analysis port; "
            f"expected monitor.analysis_port, agent.analysis_port, or agent.ap"
        )

    @staticmethod
    def _call_report_phase(component: Any) -> None:
        report_phase = getattr(component, "report_phase", None)
        if not callable(report_phase):
            return
        try:
            _ = report_phase()
        except RuntimeError as exc:
            if "No simulator available" not in str(exc):
                raise
            summary = getattr(getattr(component, "model", None), "summary", None)
            if callable(summary):
                print(summary())
                for error in getattr(component.model, "errors", ()):
                    print(error.message)
                return
            summary = getattr(component, "summary", None)
            if callable(summary):
                print(summary())
                return
            raise


__all__ = ["FifoEnv"]
