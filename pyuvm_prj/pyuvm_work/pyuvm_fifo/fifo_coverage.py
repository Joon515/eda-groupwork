"""cocotb-coverage collector for monitor-driven FIFO observations."""

from __future__ import annotations

from collections.abc import Callable
from dataclasses import dataclass
from importlib import import_module
from pathlib import Path
from typing import Any, Protocol, cast

from cocotb_coverage.coverage import (  # pyright: ignore[reportMissingImports]
    CoverCross,
    CoverPoint,
    coverage_db,
    coverage_section,
)

try:
    import pyuvm  # pyright: ignore[reportMissingImports]
except ModuleNotFoundError:  # pragma: no cover - import-time fallback for unit scripts

    class _FallbackComponent:
        def __init__(self, name: str = "", parent: Any | None = None) -> None:
            self.name = name
            self.parent = parent

        def build_phase(self) -> None:
            pass

        def connect_phase(self) -> None:
            pass

        def report_phase(self) -> None:
            pass

        def get_full_name(self) -> str:
            return self.name

    class _FallbackPyuvm:
        uvm_component = _FallbackComponent
        uvm_tlm_analysis_fifo = None
        uvm_get_port = None

    pyuvm = _FallbackPyuvm()  # type: ignore[assignment]

from .fifo_config import FifoConfig, get_fifo_config

_fifo_item_module = import_module(".fifo_item", __package__)
FifoReadObservation = cast(Any, getattr(_fifo_item_module, "FifoReadObservation"))
FifoWriteObservation = cast(Any, getattr(_fifo_item_module, "FifoWriteObservation"))

_ComponentBase = cast(type[Any], pyuvm.uvm_component)


class _DrainPort(Protocol):
    def can_get(self) -> bool: ...

    def try_get(self) -> tuple[bool, object]: ...


class _DirectAnalysisSink:
    """Small write-compatible sink for local tests and fallback imports."""

    def __init__(self, callback: Callable[[object], None]) -> None:
        self._callback: Callable[[object], None] = callback

    def write(self, observation: object) -> None:
        self._callback(observation)


@dataclass(slots=True)
class FifoCoverageStats:
    """Simple event counters reported beside cocotb-coverage data."""

    write_observations: int = 0
    read_observations: int = 0
    accepted_writes: int = 0
    accepted_reads: int = 0
    blocked_writes: int = 0
    blocked_reads: int = 0
    occupancy: int = 0


def _sample_value(sample: dict[str, object], name: str) -> object:
    return sample[name]


def _data_pattern(value: int, width: int) -> str:
    mask = (1 << width) - 1
    masked = int(value) & mask
    alt_a = 0xAAAA & mask
    alt_5 = 0x5555 & mask
    if masked == 0:
        return "zero"
    if masked == mask:
        return "all_ones"
    if masked == alt_a:
        return "alternating_a"
    if masked == alt_5:
        return "alternating_5"
    return "other"


def _occupancy_region(occupancy: int, depth: int) -> str:
    bounded = max(0, min(int(occupancy), int(depth)))
    if bounded == 0:
        return "empty"
    if bounded == 1:
        return "one"
    if bounded >= depth:
        return "full"
    if bounded >= max(1, depth - 1):
        return "almost_full_region"
    if bounded <= max(1, depth // 4):
        return "low"
    if bounded >= max(1, (depth * 3) // 4):
        return "almost_full_region"
    return "mid"


@coverage_section(
    CoverPoint(
        "fifo.operation",
        xf=lambda sample: _sample_value(sample, "operation"),
        bins=["write", "read"],
    ),
    CoverPoint(
        "fifo.attempted",
        xf=lambda sample: _sample_value(sample, "attempted"),
        bins=[False, True],
    ),
    CoverPoint(
        "fifo.accepted",
        xf=lambda sample: _sample_value(sample, "accepted"),
        bins=[False, True],
    ),
    CoverPoint(
        "fifo.data_pattern",
        xf=lambda sample: _sample_value(sample, "data_pattern"),
        bins=["zero", "all_ones", "alternating_a", "alternating_5", "other"],
    ),
    CoverPoint(
        "fifo.occupancy_region",
        xf=lambda sample: _sample_value(sample, "occupancy_region"),
        bins=["empty", "one", "low", "mid", "almost_full_region", "full"],
    ),
    CoverPoint(
        "fifo.flags.wfull",
        xf=lambda sample: _sample_value(sample, "wfull"),
        bins=[False, True],
    ),
    CoverPoint(
        "fifo.flags.rempty",
        xf=lambda sample: _sample_value(sample, "rempty"),
        bins=[False, True],
    ),
    CoverPoint(
        "fifo.flags.walmost_full",
        xf=lambda sample: _sample_value(sample, "walmost_full"),
        bins=[False, True],
    ),
    CoverPoint(
        "fifo.flags.ralmost_empty",
        xf=lambda sample: _sample_value(sample, "ralmost_empty"),
        bins=[False, True],
    ),
    CoverCross(
        "fifo.cross.operation_attempt_accept",
        items=["fifo.operation", "fifo.attempted", "fifo.accepted"],
    ),
    CoverCross(
        "fifo.cross.required_flag_state",
        items=[
            "fifo.flags.wfull",
            "fifo.flags.rempty",
            "fifo.flags.walmost_full",
            "fifo.flags.ralmost_empty",
        ],
    ),
)
def _sample_fifo_coverage(sample: dict[str, object]) -> None:
    """Sample one normalized FIFO observation into cocotb-coverage."""


class FifoCoverage(_ComponentBase):
    """PyUVM-compatible FIFO functional coverage collector.

    The collector consumes typed write/read monitor observations through analysis
    exports or direct helper methods. It keeps a bounded reference occupancy from
    accepted operations only and never samples private DUT internals.
    """

    def __init__(
        self,
        name: str = "fifo_coverage",
        parent: object | None = None,
        *,
        width: int = 16,
        depth: int = 16,
        report_dir: str | Path = "coverage",
    ) -> None:
        super().__init__(name, parent)
        if width <= 0:
            raise ValueError(f"FIFO width must be positive, got {width}")
        if depth <= 0:
            raise ValueError(f"FIFO depth must be positive, got {depth}")
        self.width = int(width)
        self.depth = int(depth)
        self.mask = (1 << self.width) - 1
        self.report_dir = Path(report_dir)
        self.stats = FifoCoverageStats()
        self._last_wfull = False
        self._last_rempty = True
        self._last_walmost_full = False
        self._last_ralmost_empty = False
        self.write_fifo: object | None = None
        self.read_fifo: object | None = None
        self.write_get_port: object | None = None
        self.read_get_port: object | None = None
        self.write_export: object = _DirectAnalysisSink(self.write_observed)
        self.read_export: object = _DirectAnalysisSink(self.read_observed)

    @property
    def occupancy(self) -> int:
        return self.stats.occupancy

    def build_phase(self) -> None:
        super().build_phase()
        self._apply_config_if_available()
        analysis_fifo_type = getattr(pyuvm, "uvm_tlm_analysis_fifo", None)
        get_port_type = getattr(pyuvm, "uvm_get_port", None)
        if analysis_fifo_type is not None and get_port_type is not None:
            analysis_fifo_type = cast(Any, analysis_fifo_type)
            get_port_type = cast(Any, get_port_type)
            self.write_fifo = analysis_fifo_type("write_fifo", self)
            self.read_fifo = analysis_fifo_type("read_fifo", self)
            self.write_get_port = get_port_type("write_get_port", self)
            self.read_get_port = get_port_type("read_get_port", self)
            self.write_export = cast(Any, self.write_fifo).analysis_export
            self.read_export = cast(Any, self.read_fifo).analysis_export

    def connect_phase(self) -> None:
        super().connect_phase()
        if self.write_get_port is not None and self.write_fifo is not None:
            cast(Any, self.write_get_port).connect(cast(Any, self.write_fifo).get_export)
        if self.read_get_port is not None and self.read_fifo is not None:
            cast(Any, self.read_get_port).connect(cast(Any, self.read_fifo).get_export)

    def report_phase(self) -> None:
        super().report_phase()
        self.drain_analysis_fifos()
        self.report_dir.mkdir(parents=True, exist_ok=True)
        xml_path = self.report_dir / "fifo_coverage.xml"
        yaml_path = self.report_dir / "fifo_coverage.yml"

        log_info = self._log_info
        log_info(self.summary())
        coverage_db.report_coverage(log_info, bins=True, node="fifo")
        coverage_db.export_to_xml(filename=str(xml_path))
        coverage_db.export_to_yaml(filename=str(yaml_path))
        log_info(f"FIFO coverage reports written: {xml_path} and {yaml_path}")

    def write_observed(self, observation: object) -> None:
        if not isinstance(observation, FifoWriteObservation):
            raise TypeError(f"Expected FifoWriteObservation, got {type(observation)!r}")
        write_observation = cast(Any, observation)
        self.stats.write_observations += 1
        self._last_wfull = bool(write_observation.wfull)
        self._last_walmost_full = bool(write_observation.walmost_full)
        if write_observation.attempted and not write_observation.accepted:
            self.stats.blocked_writes += 1
        if write_observation.accepted:
            self.stats.accepted_writes += 1
            self.stats.occupancy = min(self.depth, self.stats.occupancy + 1)
        self._sample("write", write_observation)

    def read_observed(self, observation: object) -> None:
        if not isinstance(observation, FifoReadObservation):
            raise TypeError(f"Expected FifoReadObservation, got {type(observation)!r}")
        read_observation = cast(Any, observation)
        self.stats.read_observations += 1
        self._last_rempty = bool(read_observation.rempty)
        self._last_ralmost_empty = bool(read_observation.ralmost_empty)
        if read_observation.attempted and not read_observation.accepted:
            self.stats.blocked_reads += 1
        if read_observation.accepted:
            self.stats.accepted_reads += 1
            self.stats.occupancy = max(0, self.stats.occupancy - 1)
        self._sample("read", read_observation)

    def drain_analysis_fifos(self) -> None:
        self._drain_port(self.write_get_port, self.write_observed)
        self._drain_port(self.read_get_port, self.read_observed)

    def summary(self) -> str:
        return (
            "FIFO coverage summary: "
            f"write_observations={self.stats.write_observations}, "
            f"read_observations={self.stats.read_observations}, "
            f"accepted_writes={self.stats.accepted_writes}, "
            f"accepted_reads={self.stats.accepted_reads}, "
            f"blocked_writes={self.stats.blocked_writes}, "
            f"blocked_reads={self.stats.blocked_reads}, "
            f"occupancy={self.stats.occupancy}/{self.depth}"
        )

    def _log_info(self, message: object) -> None:
        logger = getattr(self, "logger", None)
        if logger is None:
            print(message)
            return
        try:
            logger.info(message)
        except RuntimeError as exc:
            if "No simulator available" not in str(exc):
                raise
            print(message)

    def _sample(self, operation: str, observation: Any) -> None:
        data = int(getattr(observation, "data", 0)) & self.mask
        sample: dict[str, object] = {
            "operation": operation,
            "attempted": bool(observation.attempted),
            "accepted": bool(observation.accepted),
            "data_pattern": _data_pattern(data, self.width),
            "occupancy_region": _occupancy_region(self.stats.occupancy, self.depth),
            "wfull": self._last_wfull,
            "rempty": self._last_rempty,
            "walmost_full": self._last_walmost_full,
            "ralmost_empty": self._last_ralmost_empty,
        }
        _sample_fifo_coverage(sample)

    def _apply_config_if_available(self) -> None:
        try:
            cfg = get_fifo_config(self)
        except Exception:
            return
        if isinstance(cfg, FifoConfig):
            self.width = int(cfg.width)
            self.depth = int(cfg.depth)
            self.mask = (1 << self.width) - 1
            self.stats.occupancy = max(0, min(self.stats.occupancy, self.depth))

    @staticmethod
    def _drain_port(port: object | None, callback: Callable[[object], None]) -> None:
        if port is None or not hasattr(port, "can_get") or not hasattr(port, "try_get"):
            return
        drain_port = cast(_DrainPort, port)
        while drain_port.can_get():
            got, observation = drain_port.try_get()
            if not got:
                break
            callback(observation)


__all__ = ["FifoCoverage", "FifoCoverageStats"]
