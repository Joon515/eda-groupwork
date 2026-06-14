from dataclasses import dataclass


@dataclass(slots=True)
class FifoTransaction:
    data: int
    is_write: bool
    delay: int = 0

    def masked_data(self, width: int = 16) -> int:
        return self.data & ((1 << width) - 1)
