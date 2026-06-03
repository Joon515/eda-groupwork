import os
import random
import sys

import cocotb
import pyuvm  # pyright: ignore[reportMissingImports]
from cocotb.triggers import ReadOnly
from pyuvm_fifo import FifoScoreboard  # pyright: ignore[reportMissingImports]

from pyuvm_fifo.fifo_bfm import (  # pyright: ignore[reportMissingImports]
    read_word,
    reset_fifo,
    start_clocks,
    wait_rclk,
    wait_wclk,
    write_word,
)


WIDTH = int(os.getenv("WIDTH", "16"))
DEPTH = int(os.getenv("DEPTH", "16"))
FWFT_EN = int(os.getenv("FWFT_EN", "0"))
OUT_REG_EN = int(os.getenv("OUT_REG_EN", "0"))
SYNC_STAGES = int(os.getenv("SYNC_STAGES", "2"))
ALMOST_FULL_VAL = int(os.getenv("ALMOST_FULL_VAL", "4"))
ALMOST_EMPTY_VAL = int(os.getenv("ALMOST_EMPTY_VAL", "4"))
ORDER_TEST_SEQUENCE = [0x0001, 0x00AA, 0x5555, 0xBEEF, 0xFFFF]
SIMULTANEOUS_TEST_SEQUENCE = [
    0x0101,
    0x0222,
    0x1333,
    0x2444,
    0x3555,
    0x4666,
    0x5777,
    0x6888,
    0x7999,
    0x8AAA,
    0x9BBB,
    0xACCC,
]
RANDOM_REGRESSION_SEED = 0xEDA2026
STRESS_TEST_SEED = 0xF1F0


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


def assert_asserts_enabled():
    assert not sys.flags.optimize, "Python asserts must remain enabled"


def get_dut():
    dut = cocotb.top
    for handle_name in REQUIRED_HANDLES:
        assert hasattr(dut, handle_name), f"Missing DUT handle: {handle_name}"
    return dut


def resolve_signal_value(dut, handle_name: str) -> int:
    signal = getattr(dut, handle_name)
    assert signal.value.is_resolvable, f"{handle_name} is not resolvable"
    return int(signal.value)


def require_handle(dut, handle_name: str):
    assert hasattr(dut, handle_name), f"Missing DUT handle: {handle_name}"
    return getattr(dut, handle_name)


def assert_fifo_reset_state(dut):
    assert resolve_signal_value(dut, "rempty") == 1, "FIFO should be empty after reset"
    assert resolve_signal_value(dut, "wfull") == 0, "FIFO should not be full after reset"
    assert resolve_signal_value(dut, "winc") == 0, "Write increment must stay low after reset"
    assert resolve_signal_value(dut, "rinc") == 0, "Read increment must stay low after reset"


async def setup_fifo():
    assert_asserts_enabled()
    dut = get_dut()
    start_clocks(dut)
    await reset_fifo(dut)
    return dut


async def wait_for_flag_state(dut, flag_name: str, expected_value: int, clock_name: str, max_cycles: int):
    assert clock_name in {"wclk", "rclk"}, f"Unsupported clock name: {clock_name}"
    for _ in range(max_cycles):
        if resolve_signal_value(dut, flag_name) == expected_value:
            return
        if clock_name == "wclk":
            await wait_wclk(dut, 1)
        else:
            await wait_rclk(dut, 1)
    assert resolve_signal_value(dut, flag_name) == expected_value, (
        f"{flag_name} did not reach expected value {expected_value} within {max_cycles} {clock_name} cycles"
    )


async def settle_fifo_state(dut, write_cycles: int = 2, read_cycles: int = SYNC_STAGES + 3):
    await wait_wclk(dut, write_cycles)
    await wait_rclk(dut, read_cycles)


async def legal_write(dut, scoreboard: FifoScoreboard, data: int, delay: int = 0):
    await wait_for_flag_state(dut, "wfull", 0, "wclk", SYNC_STAGES + 6)
    await write_word(dut, data, delay=delay)
    scoreboard.push_write(data)


async def legal_read(dut, scoreboard: FifoScoreboard, delay: int = 0, latency: int = 1) -> int:
    await wait_for_flag_state(dut, "rempty", 0, "rclk", SYNC_STAGES + 6)
    read_data = await read_word(dut, delay=delay, latency=latency)
    scoreboard.pop_and_check(read_data)
    return read_data


async def pulse_write_when_full(dut, data: int):
    require_handle(dut, "wdata").value = int(data)
    require_handle(dut, "winc").value = 1
    await wait_wclk(dut, 1)
    require_handle(dut, "winc").value = 0


async def pulse_read_when_empty(dut):
    require_handle(dut, "rinc").value = 1
    await wait_rclk(dut, 1)
    require_handle(dut, "rinc").value = 0


@pyuvm.test()
class FifoSmokeTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            assert_fifo_reset_state(dut)
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoResetTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()

            assert resolve_signal_value(dut, "wrst") == 1, "Write reset should be released"
            assert resolve_signal_value(dut, "rrst") == 1, "Read reset should be released"
            assert_fifo_reset_state(dut)
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoSingleWriteReadTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            expected_data = 0x1234

            await write_word(dut, expected_data)
            await wait_rclk(dut, 3)

            read_data = await read_word(dut, latency=1)
            assert read_data == expected_data, (
                f"Expected to read 0x{expected_data:04X}, got 0x{read_data:04X}"
            )
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoDelayBehaviorTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            expected_data = [0x1111, 0x1234, 0xABCD, 0x0F0F]
            delays = [0, 1, 3, 5]
            observed_data = []

            assert any(delay > 0 for delay in delays), "At least one nonzero delay must be exercised"

            for data, delay in zip(expected_data, delays):
                await write_word(dut, data, delay=delay)

            await wait_wclk(dut, 1)
            await wait_rclk(dut, 3)

            for delay in delays:
                observed_data.append(await read_word(dut, delay=delay, latency=1))

            assert observed_data == expected_data, (
                f"Expected read order {expected_data}, got {observed_data}"
            )
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoOrderPreservationTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            scoreboard = FifoScoreboard(width=WIDTH, depth=DEPTH)

            for data in ORDER_TEST_SEQUENCE:
                await write_word(dut, data)
                scoreboard.push_write(data)

            await wait_wclk(dut, 1)
            await wait_rclk(dut, 4)
            scoreboard.check_flags(dut)

            for _ in ORDER_TEST_SEQUENCE:
                read_data = await read_word(dut, latency=1)
                scoreboard.pop_and_check(read_data)

            await wait_rclk(dut, 3)
            scoreboard.check_flags(dut)
            scoreboard.assert_empty()
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoMultiItemDrainTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            scoreboard = FifoScoreboard(width=WIDTH, depth=DEPTH)
            drain_count = DEPTH // 2
            expected_data = [((index + 1) * 0x0111) & 0xFFFF for index in range(drain_count)]

            for data in expected_data:
                await write_word(dut, data)
                scoreboard.push_write(data)

            await wait_wclk(dut, 1)
            await wait_rclk(dut, 4)
            scoreboard.check_flags(dut)

            for _ in range(drain_count):
                read_data = await read_word(dut, latency=1)
                scoreboard.pop_and_check(read_data)

            await wait_wclk(dut, 2)
            await wait_rclk(dut, 4)
            scoreboard.check_flags(dut)
            assert resolve_signal_value(dut, "rempty") == 1, "FIFO should be empty after draining"
            assert resolve_signal_value(dut, "wfull") == 0, "FIFO should not be full after draining"
            scoreboard.assert_empty()
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoFullEmptyBoundaryTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            scoreboard = FifoScoreboard(width=WIDTH, depth=DEPTH)
            fill_data = [((index + 1) * 0x0101) & 0xFFFF for index in range(DEPTH)]
            overflow_data = 0xDEAD
            observed_data = []

            assert DEPTH == 8, f"This boundary test expects DEPTH=8, got DEPTH={DEPTH}"

            for data in fill_data:
                await write_word(dut, data)
                scoreboard.push_write(data)

            await wait_wclk(dut, SYNC_STAGES + 2)
            scoreboard.check_flags(dut)
            assert resolve_signal_value(dut, "wfull") == 1, "FIFO should assert wfull after reaching depth"

            await pulse_write_when_full(dut, overflow_data)
            await wait_wclk(dut, 1)
            assert resolve_signal_value(dut, "wfull") == 1, "FIFO should remain full after blocked overflow write"

            await wait_rclk(dut, SYNC_STAGES + 2)

            for _ in fill_data:
                read_data = await read_word(dut, latency=1)
                observed_data.append(read_data)
                scoreboard.pop_and_check(read_data)

            assert observed_data == fill_data, (
                f"FIFO boundary drain mismatch: expected {fill_data}, got {observed_data}"
            )

            await wait_rclk(dut, SYNC_STAGES + 2)
            scoreboard.check_flags(dut)
            assert resolve_signal_value(dut, "rempty") == 1, "FIFO should assert rempty after draining"
            scoreboard.assert_empty()
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoEmptyReadProtectionTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            scoreboard = FifoScoreboard(width=WIDTH, depth=DEPTH)

            assert_fifo_reset_state(dut)
            await pulse_read_when_empty(dut)
            await wait_rclk(dut, SYNC_STAGES + 3)

            scoreboard.check_flags(dut)
            assert resolve_signal_value(dut, "rempty") == 1, "FIFO should remain empty after an empty read pulse"
            scoreboard.assert_empty()
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoAlmostFlagsTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            scoreboard = FifoScoreboard(width=WIDTH, depth=DEPTH)
            fill_data = [((index + 1) * 0x0211) & 0xFFFF for index in range(DEPTH)]
            almost_full_threshold = DEPTH - ALMOST_FULL_VAL
            drain_to_almost_empty = DEPTH - ALMOST_EMPTY_VAL

            assert DEPTH == 8, f"This almost-flag test expects DEPTH=8, got DEPTH={DEPTH}"
            assert ALMOST_FULL_VAL == 2, (
                f"This almost-flag test expects ALMOST_FULL_VAL=2, got {ALMOST_FULL_VAL}"
            )
            assert ALMOST_EMPTY_VAL == 2, (
                f"This almost-flag test expects ALMOST_EMPTY_VAL=2, got {ALMOST_EMPTY_VAL}"
            )
            require_handle(dut, "walmost_full")
            require_handle(dut, "ralmost_empty")

            for data in fill_data[: almost_full_threshold - 1]:
                await write_word(dut, data)
                scoreboard.push_write(data)

            await wait_wclk(dut, 2)
            assert resolve_signal_value(dut, "walmost_full") == 0, (
                "walmost_full should stay low before the occupancy threshold is reached"
            )

            walmost_full_asserted = False
            for data in fill_data[almost_full_threshold - 1 :]:
                await write_word(dut, data)
                scoreboard.push_write(data)
                await wait_wclk(dut, 1)
                if resolve_signal_value(dut, "walmost_full") == 1:
                    walmost_full_asserted = True

            assert walmost_full_asserted, (
                "walmost_full should assert after stable occupancy reaches the threshold"
            )

            await wait_rclk(dut, SYNC_STAGES + 2)
            scoreboard.check_flags(dut)
            assert resolve_signal_value(dut, "ralmost_empty") == 0, (
                "ralmost_empty should deassert while the FIFO occupancy is well above the threshold"
            )

            for _ in range(drain_to_almost_empty):
                read_data = await read_word(dut, latency=1)
                scoreboard.pop_and_check(read_data)

            ralmost_empty_asserted = False
            for _ in range(SYNC_STAGES + 3):
                await wait_rclk(dut, 1)
                if resolve_signal_value(dut, "ralmost_empty") == 1:
                    ralmost_empty_asserted = True
                    break
            assert ralmost_empty_asserted, (
                "ralmost_empty should assert after stable drain reaches the threshold"
            )
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoAsyncSimultaneousReadWriteTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            scoreboard = FifoScoreboard(width=WIDTH, depth=DEPTH)
            write_delays = [0, 1, 0, 2, 1, 0, 1, 2, 0, 1, 0, 2]
            read_spacing = [0, 1, 0, 0, 1, 0, 2, 0, 1, 0, 1, 0]

            async def writer():
                for data, delay in zip(SIMULTANEOUS_TEST_SEQUENCE, write_delays):
                    await legal_write(dut, scoreboard, data, delay=delay)

            async def reader():
                reads_completed = 0
                max_attempts = len(SIMULTANEOUS_TEST_SEQUENCE) * (SYNC_STAGES + 8)
                for _ in range(max_attempts):
                    if reads_completed == len(SIMULTANEOUS_TEST_SEQUENCE):
                        break
                    spacing = read_spacing[reads_completed % len(read_spacing)]
                    if spacing:
                        await wait_rclk(dut, spacing)
                    if resolve_signal_value(dut, "rempty") == 0:
                        _ = await legal_read(dut, scoreboard, latency=1)
                        reads_completed += 1
                    else:
                        await wait_rclk(dut, 1)
                assert reads_completed == len(SIMULTANEOUS_TEST_SEQUENCE), (
                    f"Simultaneous reader completed {reads_completed} reads, expected {len(SIMULTANEOUS_TEST_SEQUENCE)}"
                )

            writer_task = cocotb.start_soon(writer())
            reader_task = cocotb.start_soon(reader())
            await writer_task
            await reader_task

            await settle_fifo_state(dut)
            scoreboard.check_flags(dut)
            scoreboard.assert_empty()
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoRandomRegressionTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            scoreboard = FifoScoreboard(width=WIDTH, depth=DEPTH)
            rng = random.Random(RANDOM_REGRESSION_SEED)
            total_operations = 200
            max_delay = 2

            for _ in range(total_operations):
                occupancy = len(scoreboard.expected_queue)
                if occupancy == 0:
                    operation = "write"
                elif occupancy >= DEPTH:
                    operation = "read"
                else:
                    operation = "write" if rng.randrange(2) == 0 else "read"

                if operation == "write":
                    data = rng.randrange(1 << WIDTH)
                    delay = rng.randrange(max_delay + 1)
                    await legal_write(dut, scoreboard, data, delay=delay)
                else:
                    delay = rng.randrange(max_delay + 1)
                    _ = await legal_read(dut, scoreboard, delay=delay, latency=1)

            remaining_reads = len(scoreboard.expected_queue)
            for _ in range(remaining_reads):
                _ = await legal_read(dut, scoreboard, latency=1)

            await settle_fifo_state(dut)
            scoreboard.check_flags(dut)
            scoreboard.assert_empty()
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoStressTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            scoreboard = FifoScoreboard(width=WIDTH, depth=DEPTH)
            rng = random.Random(STRESS_TEST_SEED)
            rounds = 250
            operations_executed = 0

            for round_index in range(rounds):
                for burst_index in range(2):
                    data = ((round_index + 1) * 0x1F1F + (burst_index * 0x0101) + rng.randrange(1 << min(WIDTH, 12))) & (
                        (1 << WIDTH) - 1
                    )
                    delay = rng.randrange(2)
                    await legal_write(dut, scoreboard, data, delay=delay)
                    operations_executed += 1

                for _ in range(2):
                    delay = rng.randrange(2)
                    _ = await legal_read(dut, scoreboard, delay=delay, latency=1)
                    operations_executed += 1

            assert operations_executed == 1000, f"Stress test must execute exactly 1000 operations, got {operations_executed}"
            assert not scoreboard.expected_queue, "Stress test must end with an empty scoreboard after 1000 operations"

            await settle_fifo_state(dut)
            scoreboard.check_flags(dut)
            scoreboard.assert_empty()
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoFwftDirectTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            expected_data = 0x5A3C

            assert FWFT_EN == 1, f"FWFT direct test expects FWFT_EN=1, got FWFT_EN={FWFT_EN}"
            assert OUT_REG_EN == 0, (
                f"FWFT direct test expects OUT_REG_EN=0, got OUT_REG_EN={OUT_REG_EN}"
            )

            await write_word(dut, expected_data)
            await settle_fifo_state(dut, write_cycles=1, read_cycles=SYNC_STAGES + 3)

            assert resolve_signal_value(dut, "rempty") == 0, "FWFT FIFO should be non-empty after first write settles"
            assert resolve_signal_value(dut, "rdata") == expected_data, (
                "FWFT direct mode should expose the first word without an extra explicit read latency"
            )

            require_handle(dut, "rinc").value = 1
            await wait_rclk(dut, 1)
            require_handle(dut, "rinc").value = 0

            await wait_rclk(dut, SYNC_STAGES + 3)
            assert resolve_signal_value(dut, "rempty") == 1, "FWFT direct FIFO should drain after consuming the visible word"
        finally:
            self.drop_objection()


@pyuvm.test()
class FifoOutRegLatencyTest(pyuvm.uvm_test):
    async def run_phase(self):
        self.raise_objection()
        try:
            dut = await setup_fifo()
            expected_data = 0x6D3A

            assert FWFT_EN == 0, f"OUT_REG latency test expects FWFT_EN=0, got FWFT_EN={FWFT_EN}"
            assert OUT_REG_EN == 1, (
                f"OUT_REG latency test expects OUT_REG_EN=1, got OUT_REG_EN={OUT_REG_EN}"
            )

            await write_word(dut, expected_data)
            await settle_fifo_state(dut, write_cycles=1, read_cycles=SYNC_STAGES + 3)

            assert resolve_signal_value(dut, "rempty") == 0, "OUT_REG FIFO should be non-empty after first write settles"
            assert resolve_signal_value(dut, "rdata") == 0, (
                "OUT_REG standard mode should not expose unread data before a read pulse"
            )

            require_handle(dut, "rinc").value = 1
            await wait_rclk(dut, 1)
            require_handle(dut, "rinc").value = 0
            await ReadOnly()
            observed_after_first_cycle = resolve_signal_value(dut, "rdata")

            await wait_rclk(dut, 1)
            await ReadOnly()
            observed_after_second_cycle = resolve_signal_value(dut, "rdata")

            assert observed_after_first_cycle != expected_data, (
                "OUT_REG standard mode should not produce the read data after only one read-clock cycle"
            )
            assert observed_after_second_cycle == expected_data, (
                "OUT_REG standard mode should produce the read data after two read-clock cycles"
            )

            await wait_rclk(dut, SYNC_STAGES + 3)
            assert resolve_signal_value(dut, "rempty") == 1, "OUT_REG FIFO should be empty after the single read completes"
        finally:
            self.drop_objection()
