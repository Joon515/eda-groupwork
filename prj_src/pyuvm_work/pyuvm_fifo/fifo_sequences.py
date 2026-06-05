"""Reusable FIFO PyUVM sequences and virtual scenarios.

The classes in this module generate only ``FifoCommandItem`` stimulus for the
write/read sequencers.  They intentionally avoid direct BFM calls so tests can
reuse the same command streams in simulation and in deterministic unit scripts.
"""

from __future__ import annotations

from collections.abc import Callable, Iterable, Sequence
import inspect
import random
from typing import Any, cast

try:  # PyUVM is present in the simulation environment, but not in every shell.
    import pyuvm  # pyright: ignore[reportMissingImports]
except ModuleNotFoundError:  # pragma: no cover - compile-only fallback

    class _FallbackSequence:
        def __init__(self, name: str = "uvm_sequence") -> None:
            self.name = name

        async def start_item(self, item: Any) -> None:
            return None

        async def finish_item(self, item: Any) -> None:
            return None

        async def start(self, seqr: Any = None, call_pre_post: bool = True) -> None:
            body = getattr(self, "body", None)
            if callable(body):
                result = body()
                if inspect.isawaitable(result):
                    await result

    class _FallbackPyuvm:
        uvm_sequence = _FallbackSequence

    pyuvm = _FallbackPyuvm()  # type: ignore[assignment]

try:  # cocotb is available for simulation; unit scripts only inspect commands.
    import cocotb  # pyright: ignore[reportMissingImports]
except ModuleNotFoundError:  # pragma: no cover - compile-only fallback

    class _FallbackCocotb:
        @staticmethod
        def start_soon(awaitable: Any) -> Any:
            raise RuntimeError("cocotb.start_soon requires a simulator")

    cocotb = _FallbackCocotb()  # type: ignore[assignment]

from .fifo_item import FifoCommandItem  # pyright: ignore[reportMissingImports]


_SequenceBase = cast(Any, pyuvm.uvm_sequence)
DataPattern = str | Iterable[int] | Callable[[int, random.Random, int], int]


def _validate_non_negative(name: str, value: int) -> int:
    value = int(value)
    if value < 0:
        raise ValueError(f"{name} must be non-negative, got {value}")
    return value


def _mask_for_width(width: int) -> int:
    width = int(width)
    if width <= 0:
        raise ValueError(f"width must be positive, got {width}")
    return (1 << width) - 1


def _rng(seed: int | None) -> random.Random:
    return random.Random(seed)


def _delay_for(index: int, *, delay: int | None, delays: Sequence[int] | None, max_delay: int, rng: random.Random) -> int:
    if delays is not None:
        if not delays:
            raise ValueError("delays must not be empty")
        return _validate_non_negative("delay", delays[index % len(delays)])
    if delay is not None:
        return _validate_non_negative("delay", delay)
    max_delay = _validate_non_negative("max_delay", max_delay)
    return rng.randint(0, max_delay) if max_delay else 0


def _coerce_data_pattern(pattern: DataPattern | None, width: int) -> DataPattern:
    return "random" if pattern is None else pattern


def _data_for(index: int, *, pattern: DataPattern | None, width: int, rng: random.Random) -> int:
    mask = _mask_for_width(width)
    pattern = _coerce_data_pattern(pattern, width)

    if callable(pattern):
        return int(pattern(index, rng, width)) & mask

    if isinstance(pattern, str):
        normalized = pattern.strip().lower()
        if normalized in {"zero", "zeros"}:
            return 0
        if normalized in {"all_ones", "ones", "max"}:
            return mask
        if normalized in {"alternating", "alt"}:
            return (0xAAAA if index % 2 == 0 else 0x5555) & mask
        if normalized in {"walking", "walking_one", "single_bit"}:
            return (1 << (index % width)) & mask
        if normalized in {"boundary", "edges"}:
            values = (0, 1, mask >> 1, mask, 0xAAAA & mask, 0x5555 & mask)
            return values[index % len(values)] & mask
        if normalized in {"incrementing", "increment", "count"}:
            return index & mask
        if normalized in {"random", "seeded_random"}:
            return rng.randrange(mask + 1)
        if normalized in {"legacy_order", "order_test"}:
            values = (0x0001, 0x00AA, 0x5555, 0xBEEF, 0xFFFF)
            return values[index % len(values)] & mask
        if normalized in {"simultaneous", "simultaneous_test"}:
            values = (0x0101, 0x0222, 0x1333, 0x2444, 0x3555, 0x4666, 0x5777, 0x6888, 0x7999, 0x8AAA, 0x9BBB, 0xACCC)
            return values[index % len(values)] & mask
        raise ValueError(f"unsupported data pattern {pattern!r}")

    values = tuple(int(value) & mask for value in pattern)
    if not values:
        raise ValueError("data_pattern iterable must not be empty")
    return values[index % len(values)]


def command_summary(commands: Iterable[FifoCommandItem]) -> tuple[tuple[str, int, int, bool, bool, str], ...]:
    """Return a stable, simulator-free summary for deterministic checks."""

    return tuple(
        (
            cmd.kind,
            int(cmd.data),
            int(cmd.delay),
            bool(cmd.allow_when_full),
            bool(cmd.allow_when_empty),
            str(cmd.tag),
        )
        for cmd in commands
    )


class FifoCommandSequence(_SequenceBase):
    """Base sequence that sends a precomputed command list to one sequencer."""

    def __init__(self, name: str = "fifo_command_sequence") -> None:
        super().__init__(name)
        self.sequence_name = name
        self.commands: list[FifoCommandItem] = []

    def generated_commands(self) -> list[FifoCommandItem]:
        return list(self.commands)

    def command_summary(self) -> tuple[tuple[str, int, int, bool, bool, str], ...]:
        return command_summary(self.generated_commands())

    async def body(self) -> None:
        for item in self.generated_commands():
            await self.start_item(item)
            await self.finish_item(item)


class WriteBurstSeq(FifoCommandSequence):
    """Generate a deterministic burst of write commands."""

    def __init__(
        self,
        name: str = "write_burst_seq",
        *,
        count: int = 10,
        seed: int | None = None,
        width: int = 16,
        delay: int | None = 0,
        delays: Sequence[int] | None = None,
        max_delay: int = 0,
        data_pattern: DataPattern | None = "random",
        allow_when_full: bool = False,
        tag: str = "write_burst",
    ) -> None:
        super().__init__(name)
        self.count = _validate_non_negative("count", count)
        self.seed = seed
        self.width = int(width)
        self.delay = delay
        self.delays = tuple(delays) if delays is not None else None
        self.max_delay = max_delay
        self.data_pattern = data_pattern
        self.allow_when_full = bool(allow_when_full)
        self.tag = tag
        self.commands = self._build_commands()

    def _build_commands(self) -> list[FifoCommandItem]:
        rand = _rng(self.seed)
        commands: list[FifoCommandItem] = []
        for index in range(self.count):
            commands.append(
                FifoCommandItem.write(
                    _data_for(index, pattern=self.data_pattern, width=self.width, rng=rand),
                    name=f"{self.sequence_name}_item_{index}",
                    delay=_delay_for(index, delay=self.delay, delays=self.delays, max_delay=self.max_delay, rng=rand),
                    allow_when_full=self.allow_when_full,
                    tag=f"{self.tag}[{index}]",
                )
            )
        return commands


class ReadBurstSeq(FifoCommandSequence):
    """Generate a deterministic burst of read commands."""

    def __init__(
        self,
        name: str = "read_burst_seq",
        *,
        count: int = 10,
        seed: int | None = None,
        delay: int | None = 0,
        delays: Sequence[int] | None = None,
        max_delay: int = 0,
        allow_when_empty: bool = False,
        tag: str = "read_burst",
    ) -> None:
        super().__init__(name)
        self.count = _validate_non_negative("count", count)
        self.seed = seed
        self.delay = delay
        self.delays = tuple(delays) if delays is not None else None
        self.max_delay = max_delay
        self.allow_when_empty = bool(allow_when_empty)
        self.tag = tag
        self.commands = self._build_commands()

    def _build_commands(self) -> list[FifoCommandItem]:
        rand = _rng(self.seed)
        commands: list[FifoCommandItem] = []
        for index in range(self.count):
            commands.append(
                FifoCommandItem.read(
                    name=f"{self.sequence_name}_item_{index}",
                    delay=_delay_for(index, delay=self.delay, delays=self.delays, max_delay=self.max_delay, rng=rand),
                    allow_when_empty=self.allow_when_empty,
                    tag=f"{self.tag}[{index}]",
                )
            )
        return commands


class FillFifoSeq(WriteBurstSeq):
    """Write exactly ``depth`` words by default, useful for full-boundary setup."""

    def __init__(self, name: str = "fill_fifo_seq", *, depth: int = 16, count: int | None = None, **kwargs: Any) -> None:
        super().__init__(name, count=depth if count is None else count, tag=kwargs.pop("tag", "fill_fifo"), **kwargs)
        self.depth = _validate_non_negative("depth", depth)


class DrainFifoSeq(ReadBurstSeq):
    """Read exactly ``depth`` words by default, useful for empty-boundary setup."""

    def __init__(self, name: str = "drain_fifo_seq", *, depth: int = 16, count: int | None = None, **kwargs: Any) -> None:
        super().__init__(name, count=depth if count is None else count, tag=kwargs.pop("tag", "drain_fifo"), **kwargs)
        self.depth = _validate_non_negative("depth", depth)


class AlternatingPatternSeq(WriteBurstSeq):
    """Write zero/ones/alternating/walking-style data, defaulting to 0xAAAA/0x5555."""

    def __init__(self, name: str = "alternating_pattern_seq", *, count: int = 8, **kwargs: Any) -> None:
        super().__init__(
            name,
            count=count,
            data_pattern=kwargs.pop("data_pattern", "alternating"),
            tag=kwargs.pop("tag", "alternating_pattern"),
            **kwargs,
        )


class FifoVirtualSequence(_SequenceBase):
    """Base virtual sequence that resolves env write/read sequencers."""

    def __init__(self, name: str = "fifo_virtual_sequence", *, env: Any | None = None) -> None:
        super().__init__(name)
        self.sequence_name = name
        self.env = env

    def resolve_sequencers(self, env: Any | None = None) -> tuple[Any, Any]:
        target_env = env if env is not None else self.env
        if target_env is None:
            raise RuntimeError(f"{self.sequence_name} requires env or self.env to resolve child sequencers")
        write_agent = getattr(target_env, "write_agent", None)
        read_agent = getattr(target_env, "read_agent", None)
        write_sequencer = getattr(write_agent, "sequencer", None)
        read_sequencer = getattr(read_agent, "sequencer", None)
        if write_sequencer is None or read_sequencer is None:
            raise RuntimeError("expected env.write_agent.sequencer and env.read_agent.sequencer to be built")
        return write_sequencer, read_sequencer

    async def _start_concurrent(self, write_seq: FifoCommandSequence, read_seq: FifoCommandSequence) -> None:
        write_sequencer, read_sequencer = self.resolve_sequencers()
        write_task = cocotb.start_soon(write_seq.start(write_sequencer))
        read_task = cocotb.start_soon(read_seq.start(read_sequencer))
        await write_task
        await read_task

    async def _start_write_then_read(self, write_seq: FifoCommandSequence, read_seq: FifoCommandSequence) -> None:
        write_sequencer, read_sequencer = self.resolve_sequencers()
        await write_seq.start(write_sequencer)
        await read_seq.start(read_sequencer)


class BoundaryOverflowUnderflowSeq(FifoVirtualSequence):
    """Fill, attempt overflow writes, drain, then attempt underflow reads via command policy flags."""

    def __init__(
        self,
        name: str = "boundary_overflow_underflow_seq",
        *,
        env: Any | None = None,
        depth: int = 16,
        width: int = 16,
        seed: int | None = None,
        delay: int | None = 0,
        overflow_attempts: int = 2,
        underflow_attempts: int = 2,
        data_pattern: DataPattern | None = "boundary",
    ) -> None:
        super().__init__(name, env=env)
        self.depth = _validate_non_negative("depth", depth)
        self.width = int(width)
        self.seed = seed
        self.delay = delay
        self.overflow_attempts = _validate_non_negative("overflow_attempts", overflow_attempts)
        self.underflow_attempts = _validate_non_negative("underflow_attempts", underflow_attempts)
        self.data_pattern = data_pattern
        overflow_seed = None if seed is None else seed + 1
        self.fill_seq = FillFifoSeq(
            f"{name}_fill",
            depth=depth,
            width=width,
            seed=seed,
            delay=delay,
            data_pattern=data_pattern,
        )
        self.overflow_seq = WriteBurstSeq(
            f"{name}_overflow_attempts",
            count=overflow_attempts,
            width=width,
            seed=overflow_seed,
            delay=delay,
            data_pattern="all_ones",
            allow_when_full=True,
            tag="overflow_attempt",
        )
        self.drain_seq = DrainFifoSeq(f"{name}_drain", depth=depth, delay=delay)
        self.underflow_seq = ReadBurstSeq(
            f"{name}_underflow_attempts",
            count=underflow_attempts,
            delay=delay,
            allow_when_empty=True,
            tag="underflow_attempt",
        )

    def generated_commands(self) -> dict[str, list[FifoCommandItem]]:
        return {
            "write": self.fill_seq.generated_commands() + self.overflow_seq.generated_commands(),
            "read": self.drain_seq.generated_commands() + self.underflow_seq.generated_commands(),
        }

    def command_summary(self) -> dict[str, tuple[tuple[str, int, int, bool, bool, str], ...]]:
        commands = self.generated_commands()
        return {domain: command_summary(items) for domain, items in commands.items()}

    async def body(self) -> None:
        write_sequencer, read_sequencer = self.resolve_sequencers()
        await self.fill_seq.start(write_sequencer)
        await self.overflow_seq.start(write_sequencer)
        await self.drain_seq.start(read_sequencer)
        await self.underflow_seq.start(read_sequencer)


class ConcurrentRandomVirtualSeq(FifoVirtualSequence):
    """Run seeded random write and read bursts concurrently on env sequencers."""

    def __init__(
        self,
        name: str = "concurrent_random_virtual_seq",
        *,
        env: Any | None = None,
        count: int = 1000,
        seed: int | None = 0xEDA2026,
        width: int = 16,
        max_delay: int = 2,
        data_pattern: DataPattern | None = "random",
    ) -> None:
        super().__init__(name, env=env)
        write_seed = seed
        read_seed = None if seed is None else seed ^ 0x5A5A_0001
        self.write_seq = WriteBurstSeq(
            f"{name}_writes",
            count=count,
            seed=write_seed,
            width=width,
            delay=None,
            max_delay=max_delay,
            data_pattern=data_pattern,
            tag="concurrent_random_write",
        )
        self.read_seq = ReadBurstSeq(
            f"{name}_reads",
            count=count,
            seed=read_seed,
            delay=None,
            max_delay=max_delay,
            tag="concurrent_random_read",
        )

    def generated_commands(self) -> dict[str, list[FifoCommandItem]]:
        return {"write": self.write_seq.generated_commands(), "read": self.read_seq.generated_commands()}

    def command_summary(self) -> dict[str, tuple[tuple[str, int, int, bool, bool, str], ...]]:
        return {domain: command_summary(items) for domain, items in self.generated_commands().items()}

    async def body(self) -> None:
        await self._start_concurrent(self.write_seq, self.read_seq)


class StressVirtualSeq(ConcurrentRandomVirtualSeq):
    """High-frequency concurrent read/write stress scenario."""

    def __init__(self, name: str = "stress_virtual_seq", *, count: int = 2000, seed: int | None = 0xF1F0, **kwargs: Any) -> None:
        super().__init__(name, count=count, seed=seed, max_delay=kwargs.pop("max_delay", 0), **kwargs)
        for cmd in self.write_seq.commands:
            cmd.tag = cmd.tag.replace("concurrent_random", "stress")
        for cmd in self.read_seq.commands:
            cmd.tag = cmd.tag.replace("concurrent_random", "stress")


class FwftSingleWordSeq(FifoVirtualSequence):
    """Single-word FWFT scenario: write one word, then consume the visible word with one read."""

    def __init__(
        self,
        name: str = "fwft_single_word_seq",
        *,
        env: Any | None = None,
        data: int = 0x5A3C,
        width: int = 16,
        write_delay: int = 0,
        read_delay: int = 0,
    ) -> None:
        super().__init__(name, env=env)
        data &= _mask_for_width(width)
        self.write_seq = WriteBurstSeq(
            f"{name}_write",
            count=1,
            width=width,
            delay=write_delay,
            data_pattern=(data,),
            tag="fwft_single_word_write",
        )
        self.read_seq = ReadBurstSeq(f"{name}_read", count=1, delay=read_delay, tag="fwft_single_word_read")

    def generated_commands(self) -> dict[str, list[FifoCommandItem]]:
        return {"write": self.write_seq.generated_commands(), "read": self.read_seq.generated_commands()}

    def command_summary(self) -> dict[str, tuple[tuple[str, int, int, bool, bool, str], ...]]:
        return {domain: command_summary(items) for domain, items in self.generated_commands().items()}

    async def body(self) -> None:
        await self._start_write_then_read(self.write_seq, self.read_seq)


class OutRegLatencySeq(FwftSingleWordSeq):
    """Single-word OUT_REG scenario with read command tagged for two-cycle latency checks."""

    def __init__(self, name: str = "out_reg_latency_seq", *, data: int = 0x6D3A, **kwargs: Any) -> None:
        super().__init__(name, data=data, **kwargs)
        for cmd in self.write_seq.commands:
            cmd.tag = cmd.tag.replace("fwft_single_word", "out_reg_latency")
        for cmd in self.read_seq.commands:
            cmd.tag = cmd.tag.replace("fwft_single_word", "out_reg_latency")


__all__ = [
    "AlternatingPatternSeq",
    "BoundaryOverflowUnderflowSeq",
    "ConcurrentRandomVirtualSeq",
    "DrainFifoSeq",
    "FillFifoSeq",
    "FifoCommandSequence",
    "FifoVirtualSequence",
    "FwftSingleWordSeq",
    "OutRegLatencySeq",
    "ReadBurstSeq",
    "StressVirtualSeq",
    "WriteBurstSeq",
    "command_summary",
]
