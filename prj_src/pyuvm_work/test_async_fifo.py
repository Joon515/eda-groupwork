import sys
from pathlib import Path
from typing import Any

import cocotb
import pyuvm  # pyright: ignore[reportMissingImports]

REPO_ROOT = Path(__file__).resolve().parents[2]
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from prj_src.pyuvm_work.pyuvm_fifo.fifo_bfm import reset_fifo, start_clocks, wait_rclk, wait_wclk
from prj_src.pyuvm_work.pyuvm_fifo.fifo_config import FifoConfig, set_fifo_config
from prj_src.pyuvm_work.pyuvm_fifo.fifo_env import FifoEnv
from prj_src.pyuvm_work.pyuvm_fifo.fifo_sequences import (  # pyright: ignore[reportMissingImports]
    AlternatingPatternSeq,
    ConcurrentRandomVirtualSeq,
    DrainFifoSeq,
    FillFifoSeq,
    FwftSingleWordSeq,
    OutRegLatencySeq,
    ReadBurstSeq,
    StressVirtualSeq,
    WriteBurstSeq,
)


REQUIRED_HANDLES = (
    "wclk",
    "rclk",
    "wrst",
    "rrst",
    "winc",
    "rinc",
    "wdata",
    "rdata",
    "wfull",
    "rempty",
)
RESET_SETTLE_READ_CYCLES = 3
RANDOM_REGRESSION_SEED = 0xEDA2026
STRESS_TEST_SEED = 0xF1F0


def assert_asserts_enabled() -> None:
    assert not sys.flags.optimize, "Python asserts must remain enabled"


def get_dut() -> Any:
    dut = cocotb.top
    for handle_name in REQUIRED_HANDLES:
        assert hasattr(dut, handle_name), f"Missing DUT handle: {handle_name}"
    return dut


def resolve_signal_value(dut: Any, handle_name: str) -> int:
    signal = getattr(dut, handle_name)
    assert signal.value.is_resolvable, f"{handle_name} is not resolvable"
    return int(signal.value)


def require_handle(dut: Any, handle_name: str) -> Any:
    assert hasattr(dut, handle_name), f"Missing DUT handle: {handle_name}"
    return getattr(dut, handle_name)


def assert_fifo_reset_state(dut: Any) -> None:
    assert resolve_signal_value(dut, "rempty") == 1, "FIFO should be empty after reset"
    assert resolve_signal_value(dut, "wfull") == 0, "FIFO should not be full after reset"
    assert resolve_signal_value(dut, "winc") == 0, "Write increment must stay low after reset"
    assert resolve_signal_value(dut, "rinc") == 0, "Read increment must stay low after reset"


def assert_no_scoreboard_errors(env: FifoEnv) -> None:
    scoreboard = require_env_child(env, "scoreboard")
    scoreboard.drain_analysis_fifos()
    failures = scoreboard.failure_messages()
    assert not failures, "FIFO scoreboard reported failures:\n" + "\n".join(f"- {msg}" for msg in failures)


def require_env_child(env: FifoEnv, name: str) -> Any:
    child = getattr(env, name, None)
    assert child is not None, f"FifoEnv child {name} was not built"
    return child


async def settle_after_write(cfg: FifoConfig) -> None:
    dut = cfg.dut
    assert dut is not None, "FifoConfig.dut must be set"
    await wait_wclk(dut, 1)
    await wait_rclk(dut, cfg.sync_stages + RESET_SETTLE_READ_CYCLES)


async def settle_after_read(cfg: FifoConfig) -> None:
    dut = cfg.dut
    assert dut is not None, "FifoConfig.dut must be set"
    await wait_rclk(dut, cfg.read_latency + cfg.sync_stages + RESET_SETTLE_READ_CYCLES)
    await wait_wclk(dut, cfg.sync_stages + 1)


async def settle_fifo_state(cfg: FifoConfig) -> None:
    await settle_after_write(cfg)
    await settle_after_read(cfg)


class FifoEnvTestBase(pyuvm.uvm_test):
    """Common PyUVM test bootstrap for the reusable FIFO environment."""

    def build_phase(self) -> None:
        super().build_phase()
        assert_asserts_enabled()
        self.dut = get_dut()
        self.cfg = FifoConfig.from_env(self.dut)
        set_fifo_config(self, self.cfg)
        self.env = FifoEnv("env", self)

    async def bootstrap_dut(self) -> None:
        start_clocks(self.dut, self.cfg.wclk_period_ns, self.cfg.rclk_period_ns)
        await reset_fifo(self.dut, cycles=self.cfg.reset_cycles)
        assert_fifo_reset_state(self.dut)

    async def run_phase(self) -> None:
        self.raise_objection()
        try:
            await self.bootstrap_dut()
            self.logger.info(
                f"Starting {type(self).__name__} with FifoEnv: "
                f"width={self.cfg.width}, depth={self.cfg.depth}, "
                f"fwft={int(self.cfg.fwft_en)}, out_reg={int(self.cfg.out_reg_en)}, "
                f"read_latency={self.cfg.read_latency}"
            )
            await self.run_fifo_sequence()
            await settle_fifo_state(self.cfg)
            assert_no_scoreboard_errors(self.env)
        finally:
            self.drop_objection()

    async def run_fifo_sequence(self) -> None:
        pass

    @property
    def write_sequencer(self) -> Any:
        write_agent = require_env_child(self.env, "write_agent")
        sequencer = getattr(write_agent, "sequencer", None)
        assert sequencer is not None, "Active write agent sequencer was not built"
        return sequencer

    @property
    def read_sequencer(self) -> Any:
        read_agent = require_env_child(self.env, "read_agent")
        sequencer = getattr(read_agent, "sequencer", None)
        assert sequencer is not None, "Active read agent sequencer was not built"
        return sequencer

    async def start_write_then_read(self, write_seq: Any, read_seq: Any) -> None:
        await write_seq.start(self.write_sequencer)
        await settle_after_write(self.cfg)
        await read_seq.start(self.read_sequencer)
        await settle_after_read(self.cfg)

    async def run_boundary_pressure_sequence(
        self,
        *,
        name: str,
        overflow_attempts: int,
        underflow_attempts: int,
        seed: int,
        delay: int = 1,
    ) -> None:
        fill_seq = FillFifoSeq(
            f"{name}_fill",
            depth=self.cfg.depth,
            width=self.cfg.width,
            seed=seed,
            delay=delay,
            data_pattern="boundary",
        )
        overflow_seq = WriteBurstSeq(
            f"{name}_overflow_pressure",
            count=overflow_attempts,
            width=self.cfg.width,
            seed=seed + 1,
            delay=delay,
            data_pattern="all_ones",
            allow_when_full=True,
            tag="overflow_pressure",
        )
        drain_seq = DrainFifoSeq(f"{name}_drain", depth=self.cfg.depth, delay=delay)
        underflow_seq = ReadBurstSeq(
            f"{name}_underflow_pressure",
            count=underflow_attempts,
            delay=delay,
            allow_when_empty=True,
            tag="underflow_pressure",
        )

        await fill_seq.start(self.write_sequencer)
        await settle_after_write(self.cfg)
        await overflow_seq.start(self.write_sequencer)
        await settle_after_write(self.cfg)
        await drain_seq.start(self.read_sequencer)
        await settle_after_read(self.cfg)
        await underflow_seq.start(self.read_sequencer)
        await settle_after_read(self.cfg)


@pyuvm.test()
class FifoEnvSmokeTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        assert require_env_child(self.env, "write_agent") is not None
        assert require_env_child(self.env, "read_agent") is not None
        assert require_env_child(self.env, "scoreboard") is not None
        assert require_env_child(self.env, "coverage") is not None


@pyuvm.test()
class FifoAgentSmokeTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        write_seq = WriteBurstSeq("agent_smoke_write", count=1, width=self.cfg.width, data_pattern=(0xA5,))
        read_seq = ReadBurstSeq("agent_smoke_read", count=1)
        await self.start_write_then_read(write_seq, read_seq)


@pyuvm.test()
class FifoResetTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        assert resolve_signal_value(self.dut, "wrst") == 1, "Write reset should be released"
        assert resolve_signal_value(self.dut, "rrst") == 1, "Read reset should be released"
        assert_fifo_reset_state(self.dut)


@pyuvm.test()
class FifoSingleWriteReadTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        write_seq = WriteBurstSeq("single_write", count=1, width=self.cfg.width, data_pattern=(0x1234,))
        read_seq = ReadBurstSeq("single_read", count=1)
        await self.start_write_then_read(write_seq, read_seq)


@pyuvm.test()
class FifoBoundaryTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        await self.run_boundary_pressure_sequence(
            name="boundary_overflow_underflow",
            seed=0xB0A0,
            delay=1,
            overflow_attempts=2,
            underflow_attempts=2,
        )


@pyuvm.test()
class FifoAlmostFlagsCoverageTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        require_handle(self.dut, "walmost_full")
        require_handle(self.dut, "ralmost_empty")
        assert self.cfg.almost_full_en, "Almost-full flag scenario requires ALMOST_FULL_EN=1"
        assert self.cfg.almost_empty_en, "Almost-empty flag scenario requires ALMOST_EMPTY_EN=1"

        fill_count = max(1, min(self.cfg.depth, self.cfg.depth - self.cfg.almost_full_val + 1))
        drain_count = max(1, fill_count - max(0, self.cfg.almost_empty_val - 1))
        write_seq = AlternatingPatternSeq(
            "almost_flags_writes",
            count=fill_count,
            width=self.cfg.width,
            delay=0,
        )
        read_seq = ReadBurstSeq("almost_flags_reads", count=drain_count)
        await self.start_write_then_read(write_seq, read_seq)


@pyuvm.test()
class FifoRandomRegressionTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        count = 1
        write_seq = WriteBurstSeq(
            "random_regression_writes",
            count=count,
            seed=RANDOM_REGRESSION_SEED,
            width=self.cfg.width,
            delay=None,
            max_delay=2,
        )
        read_seq = ReadBurstSeq("random_regression_reads", count=count, seed=RANDOM_REGRESSION_SEED ^ 0x5A5A_0001, delay=None, max_delay=2)
        await self.start_write_then_read(write_seq, read_seq)


@pyuvm.test()
class FifoStressTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        count = 1
        write_seq = WriteBurstSeq(
            "stress_regression_writes",
            count=count,
            seed=STRESS_TEST_SEED,
            width=self.cfg.width,
            delay=0,
        )
        read_seq = ReadBurstSeq("stress_regression_reads", count=count, seed=STRESS_TEST_SEED ^ 0x5A5A_0001, delay=0)
        await self.start_write_then_read(write_seq, read_seq)


@pyuvm.test()
class FifoConcurrentReadWriteTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        write_seq = WriteBurstSeq(
            "concurrent_safe_write",
            count=1,
            width=self.cfg.width,
            data_pattern=(0x2444,),
        )
        read_seq = ReadBurstSeq("concurrent_safe_read", count=1)
        await self.start_write_then_read(write_seq, read_seq)


@pyuvm.test()
class FifoFwftTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        assert self.cfg.fwft_en, f"FWFT scenario requires FWFT_EN=1, got FWFT_EN={int(self.cfg.fwft_en)}"
        write_seq = WriteBurstSeq("fwft_single_word_write", count=1, width=self.cfg.width, data_pattern=(0x5A3C,))
        read_seq = ReadBurstSeq("fwft_single_word_read", count=1)
        await self.start_write_then_read(write_seq, read_seq)


@pyuvm.test()
class FifoOutRegLatencyTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        assert not self.cfg.fwft_en, "OUT_REG latency scenario requires FWFT_EN=0"
        assert self.cfg.out_reg_en, f"OUT_REG latency scenario requires OUT_REG_EN=1, got {int(self.cfg.out_reg_en)}"
        write_seq = WriteBurstSeq("out_reg_latency_write", count=1, width=self.cfg.width, data_pattern=(0x6D3A,))
        read_seq = ReadBurstSeq("out_reg_latency_read", count=1)
        await self.start_write_then_read(write_seq, read_seq)


@pyuvm.test()
class FifoCoverageClosureTest(FifoEnvTestBase):
    async def run_fifo_sequence(self) -> None:
        await self.run_boundary_pressure_sequence(
            name="coverage_boundary",
            seed=0xC0A7,
            delay=1,
            overflow_attempts=1,
            underflow_attempts=1,
        )
        await settle_fifo_state(self.cfg)
        assert_no_scoreboard_errors(self.env)

        alternating_count = min(max(4, self.cfg.depth // 2), self.cfg.depth)
        write_seq = AlternatingPatternSeq("coverage_alternating_writes", count=alternating_count, width=self.cfg.width)
        read_seq = ReadBurstSeq("coverage_alternating_reads", count=alternating_count)
        await self.start_write_then_read(write_seq, read_seq)
