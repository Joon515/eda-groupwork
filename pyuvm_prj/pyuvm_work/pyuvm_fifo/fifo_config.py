"""FIFO configuration helpers for the PyUVM environment.

The defaults mirror the FIFO Makefile exports so the Python environment can
construct a configuration object directly from the same parameter set used by
simulation.
"""

from __future__ import annotations

from dataclasses import dataclass, field
from os import getenv
from typing import Any

try:
    import pyuvm  # pyright: ignore[reportMissingImports]
except ModuleNotFoundError:  # pragma: no cover - import-time fallback for local shells
    pyuvm = None  # type: ignore[assignment]


def _env_int(name: str, default: int) -> int:
    value = getenv(name)
    return default if value is None else int(value, 0)


def _env_bool(name: str, default: bool) -> bool:
    value = getenv(name)
    if value is None:
        return default
    return value.strip().lower() in {"1", "true", "t", "yes", "y", "on"}


@dataclass(slots=True)
class FifoConfig:
    """Reusable configuration object for the FIFO PyUVM environment.

    Attributes follow the FIFO RTL and Makefile parameter names so test code can
    use a single config object for build-time and run-time setup.
    """

    dut: Any | None = field(default=None, repr=False, compare=False)
    width: int = 16
    depth: int = 16
    fwft_en: bool = False
    out_reg_en: bool = False
    sync_stages: int = 2
    almost_full_en: bool = False
    almost_full_val: int = 4
    almost_empty_en: bool = False
    almost_empty_val: int = 4
    wclk_period_ns: int = 10
    rclk_period_ns: int = 14
    reset_cycles: int = 5
    timeout_cycles: int = 2000

    @property
    def read_latency(self) -> int:
        """Return the effective read latency in rclk cycles.

        FWFT mode is direct: data may be visible without an extra explicit read
        latency. Standard FIFO reads take 1 rclk, while OUT_REG adds a second
        rclk of latency.
        """

        if self.fwft_en:
            return 0
        return 2 if self.out_reg_en else 1

    @classmethod
    def from_env(cls, dut: Any | None = None) -> "FifoConfig":
        """Build a config from Makefile-exported environment variables."""

        return cls(
            dut=dut,
            width=_env_int("WIDTH", 16),
            depth=_env_int("DEPTH", 16),
            fwft_en=_env_bool("FWFT_EN", False),
            out_reg_en=_env_bool("OUT_REG_EN", False),
            sync_stages=_env_int("SYNC_STAGES", 2),
            almost_full_en=_env_bool("ALMOST_FULL_EN", False),
            almost_full_val=_env_int("ALMOST_FULL_VAL", 4),
            almost_empty_en=_env_bool("ALMOST_EMPTY_EN", False),
            almost_empty_val=_env_int("ALMOST_EMPTY_VAL", 4),
        )


_CONFIG_DB_FIELD = "fifo_config"


def _config_db() -> Any:
    if pyuvm is None:
        raise ModuleNotFoundError(
            "pyuvm is required to use FIFO ConfigDB helpers"
        )
    return pyuvm.ConfigDB()


def set_fifo_config(component_or_context: Any, cfg: FifoConfig) -> None:
    """Store FIFO config in PyUVM ConfigDB for downstream components."""

    _config_db().set(component_or_context, "*", _CONFIG_DB_FIELD, cfg)


def get_fifo_config(component_or_context: Any) -> FifoConfig:
    """Retrieve FIFO config from PyUVM ConfigDB."""

    cfg = _config_db().get(component_or_context, "", _CONFIG_DB_FIELD)
    if cfg is None:
        raise KeyError("FIFO config not found in ConfigDB")
    if not isinstance(cfg, FifoConfig):
        raise TypeError(f"Expected FifoConfig, got {type(cfg)!r}")
    return cfg


__all__ = [
    "FifoConfig",
    "get_fifo_config",
    "set_fifo_config",
]
