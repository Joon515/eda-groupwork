"""Reusable pyuvm FIFO helpers."""

from .fifo_transaction import FifoTransaction
from .fifo_config import FifoConfig, get_fifo_config, set_fifo_config
from .fifo_item import (  # pyright: ignore[reportMissingImports]
    BOUNDARY,
    DATA_PATTERN,
    MIXED,
    READ,
    READ_ONLY,
    WRITE,
    WRITE_ONLY,
    FifoCommandItem,
    FifoReadObservation,
    FifoWriteObservation,
    randomized_fifo_commands,
)
from .fifo_scoreboard import FifoReferenceModel, FifoScoreboard, FifoScoreboardError  # pyright: ignore[reportMissingImports]
from .fifo_coverage import FifoCoverage, FifoCoverageStats  # pyright: ignore[reportMissingImports]
from .fifo_sequences import (  # pyright: ignore[reportMissingImports]
    AlternatingPatternSeq,
    BoundaryOverflowUnderflowSeq,
    ConcurrentRandomVirtualSeq,
    DrainFifoSeq,
    FillFifoSeq,
    FifoCommandSequence,
    FifoVirtualSequence,
    FwftSingleWordSeq,
    OutRegLatencySeq,
    ReadBurstSeq,
    StressVirtualSeq,
    WriteBurstSeq,
    command_summary,
)

try:  # Optional dependencies are not always present in a minimal shell.
    from .fifo_bfm import read_word, reset_fifo, start_clocks, wait_rclk, wait_wclk, write_word
    from .fifo_agent import (  # pyright: ignore[reportMissingImports]
        FifoReadAgent,
        FifoReadDriver,
        FifoReadMonitor,
        FifoReadSequencer,
        FifoWriteAgent,
        FifoWriteDriver,
        FifoWriteMonitor,
        FifoWriteSequencer,
    )
    from .fifo_env import FifoEnv
except ModuleNotFoundError:  # pragma: no cover - keeps config-only imports working
    read_word = reset_fifo = start_clocks = wait_rclk = wait_wclk = write_word = None
    FifoEnv = FifoReadDriver = FifoWriteDriver = None
    FifoReadAgent = FifoReadMonitor = FifoReadSequencer = None
    FifoWriteAgent = FifoWriteMonitor = FifoWriteSequencer = None

__all__ = [
    "FifoConfig",
    "FifoCommandItem",
    "FifoCoverage",
    "FifoCoverageStats",
    "FifoEnv",
    "FifoReferenceModel",
    "FifoReadAgent",
    "FifoReadObservation",
    "FifoReadDriver",
    "FifoReadMonitor",
    "FifoReadSequencer",
    "FifoScoreboard",
    "FifoScoreboardError",
    "FifoTransaction",
    "FifoWriteAgent",
    "FifoWriteObservation",
    "FifoWriteDriver",
    "FifoWriteMonitor",
    "FifoWriteSequencer",
    "BOUNDARY",
    "DATA_PATTERN",
    "AlternatingPatternSeq",
    "BoundaryOverflowUnderflowSeq",
    "ConcurrentRandomVirtualSeq",
    "DrainFifoSeq",
    "FillFifoSeq",
    "FifoCommandSequence",
    "MIXED",
    "FwftSingleWordSeq",
    "FifoVirtualSequence",
    "OutRegLatencySeq",
    "READ",
    "READ_ONLY",
    "ReadBurstSeq",
    "StressVirtualSeq",
    "WRITE",
    "WRITE_ONLY",
    "WriteBurstSeq",
    "command_summary",
    "get_fifo_config",
    "randomized_fifo_commands",
    "read_word",
    "reset_fifo",
    "start_clocks",
    "set_fifo_config",
    "wait_rclk",
    "wait_wclk",
    "write_word",
]
