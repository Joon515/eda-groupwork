from collections import deque


class FifoScoreboard:
    def __init__(self, width: int, depth: int):
        assert width > 0, "FIFO width must be positive"
        assert depth > 0, "FIFO depth must be positive"
        self.width = width
        self.depth = depth
        self.mask = (1 << width) - 1
        self.expected_queue = deque()
        self.write_count = 0
        self.read_count = 0

    def push_write(self, data: int):
        self.expected_queue.append(int(data) & self.mask)
        self.write_count += 1

    def pop_and_check(self, actual: int):
        assert self.expected_queue, (
            f"FIFO scoreboard underflow: observed read 0x{int(actual) & self.mask:0{self.width // 4}X} "
            "with no expected data queued"
        )
        expected = self.expected_queue.popleft()
        observed = int(actual) & self.mask
        self.read_count += 1
        assert observed == expected, (
            f"FIFO data mismatch: expected 0x{expected:0{self.width // 4}X}, "
            f"got 0x{observed:0{self.width // 4}X}"
        )

    def assert_empty(self):
        assert not self.expected_queue, (
            f"FIFO scoreboard still holds {len(self.expected_queue)} unread item(s): "
            f"{[hex(value) for value in self.expected_queue]}"
        )

    def check_flags(self, dut, depth: int | None = None, capacity: int | None = None):
        stable_depth = self.depth if depth is None else depth
        current_capacity = len(self.expected_queue) if capacity is None else capacity

        rempty = getattr(dut, "rempty")
        wfull = getattr(dut, "wfull")
        assert rempty.value.is_resolvable, "rempty is not resolvable at stable check"
        assert wfull.value.is_resolvable, "wfull is not resolvable at stable check"

        rempty_value = int(rempty.value)
        wfull_value = int(wfull.value)

        if current_capacity == 0:
            assert rempty_value == 1, "FIFO should report rempty=1 when scoreboard is empty"
        else:
            assert rempty_value == 0, (
                f"FIFO should report rempty=0 when scoreboard holds {current_capacity} item(s)"
            )

        if current_capacity >= stable_depth:
            assert wfull_value == 1, (
                f"FIFO should report wfull=1 when scoreboard reaches depth {stable_depth}"
            )
        else:
            assert wfull_value == 0, (
                f"FIFO should report wfull=0 when scoreboard holds {current_capacity}/{stable_depth} item(s)"
            )
