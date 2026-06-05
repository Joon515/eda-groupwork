"""Monitor-driven FIFO reference model and PyUVM scoreboard."""

from __future__ import annotations

from collections import deque
from collections.abc import Callable
from dataclasses import dataclass
from importlib import import_module
from typing import Any, Protocol, cast

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

        def check_phase(self) -> None:
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


@dataclass(slots=True)
class FifoScoreboardError:
    """Structured error record emitted by the FIFO reference model."""

    kind: str
    message: str
    expected: int | None = None
    observed: int | None = None
    write_count: int = 0
    read_count: int = 0
    occupancy: int = 0


def _format_data(value: int | None, width: int) -> str:
    if value is None:
        return "<none>"
    digits = max(1, (width + 3) // 4)
    return f"0x{value:0{digits}X}"


class FifoReferenceModel:
    """Deque-backed FIFO golden model updated only from monitor observations."""

    def __init__(self, width: int = 16, depth: int = 16) -> None:
        if width <= 0:
            raise ValueError(f"FIFO width must be positive, got {width}")
        if depth <= 0:
            raise ValueError(f"FIFO depth must be positive, got {depth}")
        self.width = int(width)
        self.depth = int(depth)
        self.mask = (1 << self.width) - 1
        self.expected: deque[int] = deque()
        self.accepted_write_count = 0
        self.accepted_read_count = 0
        self.overflow_attempt_count = 0
        self.underflow_attempt_count = 0
        self.errors: list[FifoScoreboardError] = []

    @property
    def expected_queue(self) -> deque[int]:
        """Compatibility alias for older helper users."""

        return self.expected

    @property
    def write_count(self) -> int:
        return self.accepted_write_count

    @property
    def read_count(self) -> int:
        return self.accepted_read_count

    @property
    def mismatch_count(self) -> int:
        return sum(1 for error in self.errors if error.kind == "mismatch")

    @property
    def error_count(self) -> int:
        return len(self.errors)

    @property
    def occupancy(self) -> int:
        return len(self.expected)

    @property
    def is_empty(self) -> bool:
        return not self.expected

    @property
    def is_full(self) -> bool:
        return len(self.expected) >= self.depth

    def leftover_values(self) -> list[int]:
        return list(self.expected)

    def push_write(self, data: int) -> None:
        """Compatibility wrapper for accepted write data."""

        self._push_accepted(int(data), context="compatibility push_write")

    def pop_and_check(self, actual: int) -> None:
        """Compatibility wrapper for accepted read data."""

        self._pop_and_compare(int(actual), context="compatibility pop_and_check")

    def assert_empty(self) -> None:
        if self.expected:
            raise AssertionError(
                f"FIFO scoreboard still holds {self.occupancy} unread item(s): "
                f"{[_format_data(value, self.width) for value in self.expected]}"
            )

    def observe_write(self, observation: object) -> None:
        if not isinstance(observation, FifoWriteObservation):
            raise TypeError(f"Expected FifoWriteObservation, got {type(observation)!r}")
        write_observation = cast(Any, observation)
        if write_observation.attempted and not write_observation.accepted:
            if write_observation.wfull:
                self.overflow_attempt_count += 1
            return
        if write_observation.accepted:
            self._push_accepted(
                write_observation.data,
                context=f"write observation time={write_observation.sim_time} tag={write_observation.tag!r}",
            )

    def observe_read(self, observation: object) -> None:
        if not isinstance(observation, FifoReadObservation):
            raise TypeError(f"Expected FifoReadObservation, got {type(observation)!r}")
        read_observation = cast(Any, observation)
        if read_observation.attempted and not read_observation.accepted:
            if read_observation.rempty:
                self.underflow_attempt_count += 1
            return
        if read_observation.accepted:
            self._pop_and_compare(
                read_observation.data,
                context=f"read observation time={read_observation.sim_time} tag={read_observation.tag!r}",
            )

    def _push_accepted(self, data: int, *, context: str) -> None:
        masked = int(data) & self.mask
        if self.is_full:
            self._record_error(
                "accepted_overflow",
                f"Unexpected accepted write while model full: observed={_format_data(masked, self.width)}; "
                f"writes={self.accepted_write_count}, reads={self.accepted_read_count}, "
                f"occupancy={self.occupancy}/{self.depth}; {context}",
                observed=masked,
            )
            return
        self.expected.append(masked)
        self.accepted_write_count += 1

    def _pop_and_compare(self, actual: int, *, context: str) -> None:
        observed = int(actual) & self.mask
        if self.is_empty:
            self._record_error(
                "accepted_underflow",
                f"Unexpected accepted read while model empty: observed={_format_data(observed, self.width)}; "
                f"writes={self.accepted_write_count}, reads={self.accepted_read_count}, "
                f"occupancy={self.occupancy}/{self.depth}; {context}",
                observed=observed,
            )
            return

        expected = self.expected.popleft()
        self.accepted_read_count += 1
        if observed != expected:
            self._record_error(
                "mismatch",
                f"FIFO data mismatch: expected={_format_data(expected, self.width)}, "
                f"observed={_format_data(observed, self.width)}; "
                f"writes={self.accepted_write_count}, reads={self.accepted_read_count}, "
                f"occupancy={self.occupancy}/{self.depth}; {context}",
                expected=expected,
                observed=observed,
            )

    def _record_error(
        self,
        kind: str,
        message: str,
        *,
        expected: int | None = None,
        observed: int | None = None,
    ) -> None:
        self.errors.append(
            FifoScoreboardError(
                kind=kind,
                message=message,
                expected=expected,
                observed=observed,
                write_count=self.accepted_write_count,
                read_count=self.accepted_read_count,
                occupancy=self.occupancy,
            )
        )

    def summary(self) -> str:
        return (
            "FIFO scoreboard summary: "
            f"accepted_writes={self.accepted_write_count}, "
            f"accepted_reads={self.accepted_read_count}, "
            f"overflow_attempts={self.overflow_attempt_count}, "
            f"underflow_attempts={self.underflow_attempt_count}, "
            f"mismatches={self.mismatch_count}, errors={self.error_count}, "
            f"occupancy={self.occupancy}/{self.depth}"
        )


class _DirectAnalysisSink:
    """Small write-compatible sink for local tests and fallback imports."""

    def __init__(self, callback: Callable[[object], None]) -> None:
        self._callback: Callable[[object], None] = callback

    def write(self, observation: object) -> None:
        self._callback(observation)


class FifoScoreboard(_ComponentBase):
    """UVM component scoreboard consuming monitor observations only."""

    def __init__(
        self,
        name: str = "fifo_scoreboard",
        parent: object | None = None,
        *,
        width: int = 16,
        depth: int = 16,
        allow_leftovers: bool = False,
    ) -> None:
        super().__init__(name, parent)
        self._width_arg = int(width)
        self._depth_arg = int(depth)
        self.allow_leftovers = bool(allow_leftovers)
        self.model = FifoReferenceModel(width=self._width_arg, depth=self._depth_arg)
        self.write_fifo: object | None = None
        self.read_fifo: object | None = None
        self.write_get_port: object | None = None
        self.read_get_port: object | None = None
        self.write_export: object = _DirectAnalysisSink(self.write_observed)
        self.read_export: object = _DirectAnalysisSink(self.read_observed)

    @property
    def width(self) -> int:
        return self.model.width

    @property
    def depth(self) -> int:
        return self.model.depth

    @property
    def mask(self) -> int:
        return self.model.mask

    @property
    def expected_queue(self) -> deque[int]:
        return self.model.expected_queue

    @property
    def write_count(self) -> int:
        return self.model.write_count

    @property
    def read_count(self) -> int:
        return self.model.read_count

    @property
    def error_count(self) -> int:
        return self.model.error_count

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

    def check_phase(self) -> None:
        super().check_phase()
        self.drain_analysis_fifos()
        failures = self.failure_messages()
        if failures:
            raise AssertionError("FIFO scoreboard failed:\n" + "\n".join(f"- {msg}" for msg in failures))

    def report_phase(self) -> None:
        super().report_phase()
        self.drain_analysis_fifos()
        summary = self.model.summary()
        logger = getattr(self, "logger", None)
        if logger is not None:
            logger.info(summary)
            for error in self.model.errors:
                logger.error(error.message)
        else:
            print(summary)
            for error in self.model.errors:
                print(error.message)

    def write_observed(self, observation: object) -> None:
        self.model.observe_write(observation)

    def read_observed(self, observation: object) -> None:
        self.model.observe_read(observation)

    def push_write(self, data: int) -> None:
        self.model.push_write(data)

    def pop_and_check(self, actual: int) -> None:
        self.model.pop_and_check(actual)

    def assert_empty(self) -> None:
        self.model.assert_empty()

    def failure_messages(self) -> list[str]:
        messages = [error.message for error in self.model.errors]
        if self.model.occupancy and not self.allow_leftovers:
            messages.append(
                f"FIFO scoreboard leftover occupancy: {self.model.occupancy}/{self.depth}; "
                f"unread={[_format_data(value, self.width) for value in self.model.leftover_values()]}"
            )
        return messages

    def passed(self) -> bool:
        return not self.failure_messages()

    def drain_analysis_fifos(self) -> None:
        observations: list[tuple[int, int, int, object]] = []
        observations.extend(self._collect_port(self.write_get_port, domain_order=0))
        observations.extend(self._collect_port(self.read_get_port, domain_order=1))
        for _, _, domain_order, observation in sorted(observations):
            if domain_order == 0:
                self.write_observed(observation)
            else:
                self.read_observed(observation)

    def _apply_config_if_available(self) -> None:
        try:
            cfg = get_fifo_config(self)
        except Exception:
            cfg = None
        if isinstance(cfg, FifoConfig):
            self.model = FifoReferenceModel(width=cfg.width, depth=cfg.depth)
        try:
            config_db_type = getattr(pyuvm, "ConfigDB")
            configured = config_db_type().get(self, "", "allow_scoreboard_leftovers")
        except Exception:
            return
        if configured is not None:
            self.allow_leftovers = bool(configured)

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

    @staticmethod
    def _collect_port(port: object | None, *, domain_order: int) -> list[tuple[int, int, int, object]]:
        if port is None or not hasattr(port, "can_get") or not hasattr(port, "try_get"):
            return []
        drain_port = cast(_DrainPort, port)
        observations: list[tuple[int, int, int, object]] = []
        sequence = 0
        while drain_port.can_get():
            got, observation = drain_port.try_get()
            if not got:
                break
            sim_time = int(getattr(observation, "sim_time", 0))
            observations.append((sim_time, sequence, domain_order, observation))
            sequence += 1
        return observations


__all__ = [
    "FifoReferenceModel",
    "FifoScoreboard",
    "FifoScoreboardError",
]
