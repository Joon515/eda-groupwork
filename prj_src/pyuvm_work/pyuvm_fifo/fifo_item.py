"""FIFO sequence and monitor observation items for the PyUVM environment."""

from __future__ import annotations

from collections.abc import Iterable
from dataclasses import dataclass, field
import random
from typing import Any, ClassVar, cast

try:  # PyUVM is available in the verification environment, but not always in lint shells.
    import pyuvm  # pyright: ignore[reportMissingImports]
except ModuleNotFoundError:  # pragma: no cover - compile-only fallback

    class _FallbackSequenceItem:
        def __init__(self, name: str = "") -> None:
            self.name = name

    class _FallbackPyuvm:
        uvm_sequence_item = _FallbackSequenceItem

    pyuvm = _FallbackPyuvm()  # type: ignore[assignment]

_SequenceItemBase = cast(Any, pyuvm.uvm_sequence_item)


WRITE = "WRITE"
READ = "READ"

WRITE_ONLY = "write_only"
READ_ONLY = "read_only"
MIXED = "mixed"
BOUNDARY = "boundary"
DATA_PATTERN = "data_pattern"

_COMMAND_KINDS = (WRITE, READ)
_RANDOM_MODES = (WRITE_ONLY, READ_ONLY, MIXED, BOUNDARY, DATA_PATTERN)


def _mask_for_width(width: int) -> int:
    if width <= 0:
        raise ValueError(f"width must be positive, got {width}")
    return (1 << width) - 1


def _coerce_rng(rng: random.Random | None, seed: int | None) -> random.Random:
    if rng is not None and seed is not None:
        raise ValueError("pass rng or seed, not both")
    return rng if rng is not None else random.Random(seed)


class FifoCommandItem(_SequenceItemBase):
    """Command item consumed by FIFO read/write sequencers and drivers."""

    WRITE: ClassVar[str] = WRITE
    READ: ClassVar[str] = READ

    WRITE_ONLY: ClassVar[str] = WRITE_ONLY
    READ_ONLY: ClassVar[str] = READ_ONLY
    MIXED: ClassVar[str] = MIXED
    BOUNDARY: ClassVar[str] = BOUNDARY
    DATA_PATTERN: ClassVar[str] = DATA_PATTERN

    def __init__(
        self,
        name: str = "fifo_command_item",
        *,
        kind: str = WRITE,
        data: int = 0,
        delay: int = 0,
        allow_when_full: bool = False,
        allow_when_empty: bool = False,
        tag: str = "",
    ) -> None:
        super().__init__(name)
        self.kind = self._normalize_kind(kind)
        self.data = int(data)
        self.delay = int(delay)
        self.allow_when_full = bool(allow_when_full)
        self.allow_when_empty = bool(allow_when_empty)
        self.tag = str(tag)

    @staticmethod
    def _normalize_kind(kind: str) -> str:
        normalized = str(kind).upper()
        if normalized not in _COMMAND_KINDS:
            raise ValueError(f"kind must be one of {_COMMAND_KINDS}, got {kind!r}")
        return normalized

    @classmethod
    def write(
        cls,
        data: int,
        *,
        name: str = "fifo_write_command",
        delay: int = 0,
        allow_when_full: bool = False,
        tag: str = "",
    ) -> "FifoCommandItem":
        return cls(
            name,
            kind=WRITE,
            data=data,
            delay=delay,
            allow_when_full=allow_when_full,
            tag=tag,
        )

    @classmethod
    def read(
        cls,
        *,
        name: str = "fifo_read_command",
        delay: int = 0,
        allow_when_empty: bool = False,
        tag: str = "",
    ) -> "FifoCommandItem":
        return cls(
            name,
            kind=READ,
            delay=delay,
            allow_when_empty=allow_when_empty,
            tag=tag,
        )

    @classmethod
    def randomized(
        cls,
        *,
        rng: random.Random | None = None,
        seed: int | None = None,
        mode: str = MIXED,
        width: int = 16,
        max_delay: int = 0,
        data_pattern: Iterable[int] | None = None,
        allow_illegal: bool = False,
        tag: str = "",
        name: str = "fifo_random_command",
    ) -> "FifoCommandItem":
        """Create one deterministic random command using a caller RNG or seed."""

        rand = _coerce_rng(rng, seed)
        mode = str(mode).lower()
        if mode not in _RANDOM_MODES:
            raise ValueError(f"mode must be one of {_RANDOM_MODES}, got {mode!r}")
        if max_delay < 0:
            raise ValueError(f"max_delay must be non-negative, got {max_delay}")

        mask = _mask_for_width(width)
        delay = rand.randint(0, max_delay) if max_delay else 0

        if mode == WRITE_ONLY:
            kind = WRITE
        elif mode == READ_ONLY:
            kind = READ
        elif mode == DATA_PATTERN:
            kind = WRITE
        else:
            kind = rand.choice(_COMMAND_KINDS)

        if mode == BOUNDARY:
            boundary_values = [0, 1, mask >> 1, mask]
            data = rand.choice(boundary_values) & mask
        elif mode == DATA_PATTERN:
            values = tuple(data_pattern) if data_pattern is not None else (0x0000, mask, 0xAAAA, 0x5555)
            if not values:
                raise ValueError("data_pattern must not be empty")
            data = rand.choice(values) & mask
        else:
            data = rand.randint(0, mask)

        allow_when_full = bool(allow_illegal and kind == WRITE and rand.choice((False, True)))
        allow_when_empty = bool(allow_illegal and kind == READ and rand.choice((False, True)))

        return cls(
            name,
            kind=kind,
            data=data,
            delay=delay,
            allow_when_full=allow_when_full,
            allow_when_empty=allow_when_empty,
            tag=tag,
        )

    @classmethod
    def randomized_list(
        cls,
        count: int,
        *,
        rng: random.Random | None = None,
        seed: int | None = None,
        **kwargs: Any,
    ) -> list["FifoCommandItem"]:
        """Create a deterministic command list while advancing one RNG stream."""

        if count < 0:
            raise ValueError(f"count must be non-negative, got {count}")
        rand = _coerce_rng(rng, seed)
        return [cls.randomized(rng=rand, **kwargs) for _ in range(count)]

    def masked_data(self, width: int = 16) -> int:
        return self.data & _mask_for_width(width)

    def convert2string(self) -> str:
        return (
            "FifoCommandItem("
            f"kind={self.kind}, data=0x{self.data:x}, delay={self.delay}, "
            f"allow_when_full={self.allow_when_full}, "
            f"allow_when_empty={self.allow_when_empty}, tag={self.tag!r})"
        )

    def __str__(self) -> str:
        return self.convert2string()


@dataclass(slots=True)
class FifoWriteObservation:
    """Write-clock monitor observation from winc/wdata/wfull/walmost_full."""

    attempted: bool
    accepted: bool
    data: int
    wfull: bool = False
    walmost_full: bool = False
    sim_time: int | float = 0
    flags: tuple[str, ...] = field(default_factory=tuple)
    tag: str = ""

    def __post_init__(self) -> None:
        if not self.flags:
            self.flags = tuple(
                name
                for name, asserted in (
                    ("wfull", self.wfull),
                    ("walmost_full", self.walmost_full),
                )
                if asserted
            )

    @property
    def full(self) -> bool:
        return self.wfull

    @property
    def almost_full(self) -> bool:
        return self.walmost_full

    def masked_data(self, width: int = 16) -> int:
        return self.data & _mask_for_width(width)

    def convert2string(self) -> str:
        return (
            "FifoWriteObservation("
            f"accepted={self.accepted}, attempted={self.attempted}, "
            f"data=0x{self.data:x}, wfull={self.wfull}, "
            f"walmost_full={self.walmost_full}, flags={self.flags}, "
            f"time={self.sim_time}, tag={self.tag!r})"
        )

    def __str__(self) -> str:
        return self.convert2string()


@dataclass(slots=True)
class FifoReadObservation:
    """Read-clock monitor observation from rinc/rdata/rempty/ralmost_empty."""

    attempted: bool
    accepted: bool
    data: int
    rempty: bool = False
    ralmost_empty: bool = False
    sim_time: int | float = 0
    flags: tuple[str, ...] = field(default_factory=tuple)
    tag: str = ""

    def __post_init__(self) -> None:
        if not self.flags:
            self.flags = tuple(
                name
                for name, asserted in (
                    ("rempty", self.rempty),
                    ("ralmost_empty", self.ralmost_empty),
                )
                if asserted
            )

    @property
    def empty(self) -> bool:
        return self.rempty

    @property
    def almost_empty(self) -> bool:
        return self.ralmost_empty

    def convert2string(self) -> str:
        return (
            "FifoReadObservation("
            f"accepted={self.accepted}, attempted={self.attempted}, "
            f"data=0x{self.data:x}, rempty={self.rempty}, "
            f"ralmost_empty={self.ralmost_empty}, flags={self.flags}, "
            f"time={self.sim_time}, tag={self.tag!r})"
        )

    def __str__(self) -> str:
        return self.convert2string()


def randomized_fifo_commands(
    count: int,
    *,
    rng: random.Random | None = None,
    seed: int | None = None,
    **kwargs: Any,
) -> list[FifoCommandItem]:
    """Module-level convenience wrapper for deterministic command generation."""

    return FifoCommandItem.randomized_list(count, rng=rng, seed=seed, **kwargs)


__all__ = [
    "BOUNDARY",
    "DATA_PATTERN",
    "MIXED",
    "READ",
    "READ_ONLY",
    "WRITE",
    "WRITE_ONLY",
    "FifoCommandItem",
    "FifoReadObservation",
    "FifoWriteObservation",
    "randomized_fifo_commands",
]
