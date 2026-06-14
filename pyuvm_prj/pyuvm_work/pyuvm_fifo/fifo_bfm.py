import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge


def start_clocks(dut, w_period_ns: int = 10, r_period_ns: int = 14):
    wclk_task = cocotb.start_soon(Clock(getattr(dut, "wclk"), w_period_ns, unit="ns").start())
    rclk_task = cocotb.start_soon(Clock(getattr(dut, "rclk"), r_period_ns, unit="ns").start())
    return wclk_task, rclk_task


async def wait_wclk(dut, cycles: int):
    for _ in range(cycles):
        await RisingEdge(getattr(dut, "wclk"))


async def wait_rclk(dut, cycles: int):
    for _ in range(cycles):
        await RisingEdge(getattr(dut, "rclk"))


async def reset_fifo(dut, cycles: int = 5):
    getattr(dut, "wrst").value = 0
    getattr(dut, "rrst").value = 0
    getattr(dut, "winc").value = 0
    getattr(dut, "rinc").value = 0
    getattr(dut, "wdata").value = 0

    await wait_wclk(dut, cycles)
    await wait_rclk(dut, cycles)

    getattr(dut, "wrst").value = 1
    getattr(dut, "rrst").value = 1

    await wait_wclk(dut, 3)
    await wait_rclk(dut, 3)


async def write_word(dut, data: int, delay: int = 0):
    if delay:
        await wait_wclk(dut, delay)

    getattr(dut, "wdata").value = int(data)
    getattr(dut, "winc").value = 1
    await wait_wclk(dut, 1)
    getattr(dut, "winc").value = 0


async def read_word(dut, delay: int = 0, latency: int = 1):
    if delay:
        await wait_rclk(dut, delay)

    getattr(dut, "rinc").value = 1
    await wait_rclk(dut, 1)
    getattr(dut, "rinc").value = 0

    await wait_rclk(dut, latency)
    rdata = getattr(dut, "rdata")
    assert rdata.value.is_resolvable, "rdata is not resolvable"
    return int(rdata.value)
