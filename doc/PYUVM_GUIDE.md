# pyuvm/cocotb 异步 FIFO 验证平台学习指南

## 文档概述

本文档以本项目已经构建完成的 `prj_src/design_rv1_tv7/FIFO/pyuvm_work/` 为例，说明如何从现有异步 FIFO RTL 出发，搭建一个基于 **cocotb + pyuvm + Verilator** 的 Python 验证平台。本文重点解释平台结构、构建方法、Python `assert` 判断方式和常用运行命令，便于学习和复现。

这套平台是对原有 SystemVerilog UVM 平台的补充，不替代 `uvm_src/` 和 `uvm_work/`。原 UVM 平台仍然保留；新平台用于演示老师建议的 pyuvm/cocotb 验证方式，并且所有 pass/fail 判断都由 Python `assert` 完成。

---

## 为什么引入 pyuvm/cocotb

原项目已经有完整的 SystemVerilog UVM 验证环境，包括 interface、driver、monitor、sequence、scoreboard 和 test。该环境适合商业仿真器和传统 UVM 学习，但本机当前没有 VCS/Verdi 等商业工具，因此新增 pyuvm/cocotb 平台有两个目的：

1. **使用开源工具运行验证**：cocotb 可以配合 OSS CAD Suite 中的 Verilator 运行，不依赖商业仿真器。
2. **用 Python 表达验证逻辑**：pyuvm 提供类似 UVM 的 test/component 概念，scoreboard 和断言可以用 Python 编写，更适合快速学习和调试。

在本项目中，pyuvm 平台仍然验证同一个 RTL 顶层 `async_fifo_top`。它只编译 RTL 文件，不编译 `uvm_src/` 中的 SystemVerilog UVM 文件；这样可以避免 UVM class/interface 对 Verilator/cocotb 流程造成不必要的依赖。

---

## 环境准备

pyuvm 平台的环境文件位于：

```text
prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml
```

当前内容定义了一个新的 conda 环境：

```yaml
name: eda-pyuvm-fifo
channels:
  - conda-forge
dependencies:
  - python=3.11
  - pip
  - make
  - pip:
      - cocotb==2.0.1
      - pyuvm==4.0.1
```

创建环境：

```bash
conda env create -f prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml
```

激活环境：

```bash
conda activate eda-pyuvm-fifo
```

检查 Python 包和 `assert` 是否启用：

```bash
conda run -n eda-pyuvm-fifo python -c "import sys; assert not sys.flags.optimize; import cocotb, pyuvm; print(cocotb.__version__)"
```

期望输出中包含：

```text
2.0.1
```

注意：Verilator 不由 conda 安装，而是由 OSS CAD Suite 提供，并且需要已经在 shell 的 `PATH` 中。可用下面命令检查：

```bash
verilator --version
```

---

## 目录结构

新增的 pyuvm 工作目录为：

```text
prj_src/design_rv1_tv7/FIFO/pyuvm_work/
├── environment.yml
├── Makefile
├── test_async_fifo.py
└── pyuvm_fifo/
    ├── __init__.py
    ├── fifo_bfm.py
    ├── fifo_env.py
    ├── fifo_scoreboard.py
    └── fifo_transaction.py
```

各文件作用如下：

| 文件 | 作用 |
| :--- | :--- |
| `environment.yml` | 定义 conda 环境 `eda-pyuvm-fifo`，安装 Python、make、cocotb 和 pyuvm。 |
| `Makefile` | cocotb/Verilator 构建入口，指定 RTL 文件、参数覆盖、测试筛选和回归目标。 |
| `test_async_fifo.py` | pyuvm 测试入口，包含所有 `@pyuvm.test()` 测试类。 |
| `pyuvm_fifo/fifo_bfm.py` | Python BFM/helper，负责启动写时钟/读时钟、复位、写一个数据、读一个数据。 |
| `pyuvm_fifo/fifo_scoreboard.py` | Python scoreboard，用队列保存期望数据，用 `assert` 比较读出数据和标志位。 |
| `pyuvm_fifo/fifo_transaction.py` | 简单 transaction 数据结构，保存数据、读写方向和延迟。 |
| `pyuvm_fifo/fifo_env.py` | 精简 pyuvm 环境骨架，保留 driver/monitor/env 的 UVM 概念映射。 |
| `pyuvm_fifo/__init__.py` | 包导出入口，便于测试文件直接导入 BFM、scoreboard 和 transaction。 |

---

## Makefile 构建方法

pyuvm 工作目录中的 Makefile 默认使用 Verilator：

```makefile
SIM ?= verilator
TOPLEVEL_LANG ?= verilog
TOPLEVEL ?= async_fifo_top
MODULE ?= test_async_fifo
TESTCASE ?= FifoSmokeTest
```

含义如下：

| 变量 | 含义 |
| :--- | :--- |
| `SIM` | cocotb 使用的仿真器，默认 `verilator`。 |
| `TOPLEVEL_LANG` | 顶层语言，当前 RTL 是 SystemVerilog/Verilog 风格，设置为 `verilog`。 |
| `TOPLEVEL` | DUT 顶层模块名，本项目是 `async_fifo_top`。 |
| `MODULE` | cocotb Python 测试模块名，本项目是 `test_async_fifo`。 |
| `TESTCASE` | 用户友好的测试类选择变量，例如 `FifoSmokeTest`。 |

### 编译的 RTL 文件

cocotb/Verilator 流程只编译下面六个 RTL 文件，并按此顺序传入：

```makefile
../rtl_src/fifo_cfg_pkg.sv
../rtl_src/sync_gray.sv
../rtl_src/dual_port_ram.sv
../rtl_src/wptr.sv
../rtl_src/rptr.sv
../rtl_src/async_fifo_top.sv
```

其中 `fifo_cfg_pkg.sv` 必须先编译，因为后续 RTL 会 import 该 package。

本流程明确不编译这些 SV UVM 文件：

```text
../uvm_src/fifo_if.sv
../uvm_src/tb_top.sv
../uvm_src/*.sv UVM class 文件
```

这样做的原因是 cocotb 直接通过 VPI 访问 RTL 顶层端口，不需要 SystemVerilog interface 和 UVM class testbench。

### 参数覆盖

Makefile 中提供了 FIFO 参数变量：

```makefile
DEPTH ?= 16
WIDTH ?= 16
FWFT_EN ?= 0
OUT_REG_EN ?= 0
SYNC_STAGES ?= 2
ALMOST_FULL_EN ?= 0
ALMOST_FULL_VAL ?= 4
ALMOST_EMPTY_EN ?= 0
ALMOST_EMPTY_VAL ?= 4
```

这些变量通过 Verilator 的 `-G` 参数传给 RTL，例如：

```makefile
EXTRA_ARGS += -GDEPTH=$(DEPTH)
EXTRA_ARGS += -GWIDTH=$(WIDTH)
EXTRA_ARGS += -GFWFT_EN=$(FWFT_EN)
```

因此可以在命令行覆盖参数，例如：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoAlmostFlagsTest DEPTH=8 ALMOST_FULL_EN=1 ALMOST_FULL_VAL=2 ALMOST_EMPTY_EN=1 ALMOST_EMPTY_VAL=2
```

### 为什么使用 testcase-specific results 文件

Makefile 中的 `run` 目标会把每个测试的结果文件设置为：

```makefile
results-$(TESTCASE).xml
```

这样做是为了避免连续回归时所有测试共用 `results.xml`，导致 make 误判目标已经最新、跳过某些测试。

### 为什么使用 parameter-specific SIM_BUILD

Makefile 会把参数组合编码到 `SIM_BUILD` 路径中：

```makefile
sim_build/$(SIM)-d$(DEPTH)-w$(WIDTH)-fw$(FWFT_EN)-out$(OUT_REG_EN)-sync$(SYNC_STAGES)-af$(ALMOST_FULL_EN)-afv$(ALMOST_FULL_VAL)-ae$(ALMOST_EMPTY_EN)-aev$(ALMOST_EMPTY_VAL)
```

这样做是为了防止 Verilator 在不同参数配置之间复用旧的可执行文件。例如 `FWFT_EN=1`、`OUT_REG_EN=1`、`ALMOST_FULL_EN=1` 都会改变 RTL generate 分支，如果复用旧 build，就可能运行了错误配置。

---

## pyuvm 平台结构

本平台保留了 UVM 的核心思想，但用 Python 实现。

| SV UVM 概念 | pyuvm/cocotb 中的实现 |
| :--- | :--- |
| transaction | `FifoTransaction`，保存数据、方向和延迟。 |
| driver/BFM | `fifo_bfm.py` 中的 `write_word()`、`read_word()`、`reset_fifo()`。 |
| monitor | 当前平台用 BFM 和 scoreboard 直接检查核心行为，`FifoMonitor` 是保留的结构骨架。 |
| scoreboard | `FifoScoreboard`，维护期望队列并比较读出数据。 |
| test | `test_async_fifo.py` 中的 `@pyuvm.test()` 类。 |

### BFM

`fifo_bfm.py` 中的核心函数：

```python
start_clocks(dut, w_period_ns=10, r_period_ns=14)
reset_fifo(dut)
write_word(dut, data, delay=0)
read_word(dut, delay=0, latency=1)
```

本项目使用不同周期的写时钟和读时钟，默认写时钟 10ns、读时钟 14ns，用于体现异步 FIFO 的跨时钟特性。复位为低有效：`wrst=0`、`rrst=0` 表示复位有效；释放后为 `wrst=1`、`rrst=1`。

### Scoreboard

`FifoScoreboard` 用 `deque` 保存写入的期望数据：

```python
push_write(data)
pop_and_check(actual)
assert_empty()
check_flags(dut)
```

写入时 scoreboard 把数据 mask 到当前 `WIDTH`；读取时弹出队首期望值并与 `actual` 比较。若数据顺序错误、读多了、最后还有未读数据，都会触发 Python `assert`。

### 测试类

`test_async_fifo.py` 中已经实现的测试包括：

| 测试类 | 目的 |
| :--- | :--- |
| `FifoSmokeTest` | 最小冒烟测试，确认 DUT 句柄存在并完成复位。 |
| `FifoResetTest` | 检查复位释放后空/满及控制信号状态。 |
| `FifoSingleWriteReadTest` | 写入一个数据并读回。 |
| `FifoDelayBehaviorTest` | 带不同写读延迟的数据顺序测试。 |
| `FifoOrderPreservationTest` | 多数据写入后按 FIFO 顺序读出。 |
| `FifoMultiItemDrainTest` | 写入半深度数据后全部 drain，并检查最终空状态。 |
| `FifoFullEmptyBoundaryTest` | `DEPTH=8` 下写满、阻止溢出写、再读空。 |
| `FifoEmptyReadProtectionTest` | 空 FIFO 上读脉冲不应产生非法数据。 |
| `FifoAlmostFlagsTest` | 近满/近空标志在稳定后正确断言。 |
| `FifoAsyncSimultaneousReadWriteTest` | 独立读写协程并发运行，检查无数据破坏。 |
| `FifoRandomRegressionTest` | 固定 seed `0xEDA2026` 的 200 次随机操作。 |
| `FifoStressTest` | 固定 seed `0xF1F0` 的 1000 次有界压力操作。 |
| `FifoFwftDirectTest` | `FWFT_EN=1 OUT_REG_EN=0` 下检查首字直通行为。 |
| `FifoOutRegLatencyTest` | `OUT_REG_EN=1` 下检查标准模式两拍读延迟。 |

---

## assert 判断方法

本平台只使用 Python `assert` 作为 pass/fail 判断方式，没有新增 SystemVerilog assertion。

例如，复位状态检查：

```python
assert resolve_signal_value(dut, "rempty") == 1, "FIFO should be empty after reset"
assert resolve_signal_value(dut, "wfull") == 0, "FIFO should not be full after reset"
```

数据比较检查：

```python
assert observed == expected, (
    f"FIFO data mismatch: expected 0x{expected:04X}, got 0x{observed:04X}"
)
```

最终状态检查：

```python
scoreboard.assert_empty()
```

必须注意：Python 的 `assert` 在优化模式下会被关闭。如果使用 `python -O`，这些判断不会执行。因此测试文件开头会检查：

```python
assert not sys.flags.optimize, "Python asserts must remain enabled"
```

运行平台时不要使用 `python -O`，也不要设置会让 Python 进入优化模式的环境变量。

---

## 运行命令

以下命令均从仓库根目录执行。

### 单个 smoke test

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoSmokeTest
```

### 基础回归

包含 smoke、reset、单次写读、延迟行为测试：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator regression-basic
```

### 核心数据顺序回归

包含基础测试和 scoreboard/order 测试：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator regression-core
```

### 边界与近满/近空回归

包含 full/empty、empty read protection、almost flag 测试：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator regression-boundary
```

### 高级回归

包含异步并发、随机、压力、FWFT 和 OUT_REG 模式测试：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator regression-advanced
```

### 完整 pyuvm 回归

完整回归会依次运行 smoke、basic、core、boundary 和 advanced：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator regression
```

### 清理生成物

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work clean
```

该命令会删除 `sim_build/`、`results.xml`、`results-*.xml`、`*.vcd`、`*.fst`、`__pycache__` 和 `.pytest_cache`。

---

## 常见问题

### 1. `verilator: command not found`

说明 OSS CAD Suite 没有正确加入 `PATH`。需要先进入或 source OSS CAD Suite 环境，再执行：

```bash
verilator --version
```

确认可见后再运行 cocotb/pyuvm 测试。

### 2. `conda run -n eda-pyuvm-fifo ...` 找不到环境

说明环境还没有创建，先运行：

```bash
conda env create -f prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml
```

### 3. Python assert 没有效果

检查是否误用了 `python -O`。本平台依赖 Python `assert` 判断数据和标志位，优化模式会关闭断言，因此禁止使用。

### 4. cocotb 找不到测试模块

确认 Makefile 中 `MODULE ?= test_async_fifo`，并且命令从仓库根目录使用 `make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work ...` 执行。不要把 `MODULE` 改成文件路径。

### 5. 参数模式不对或测试结果像是旧配置

本 Makefile 已经把参数组合编码进 `SIM_BUILD`，正常情况下不同参数会生成不同 build 目录。如果手动修改了 Makefile 或直接复用旧可执行文件，建议先执行：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work clean
```

再重新运行测试。

### 6. 某些标志位不能在同一拍立即判断

异步 FIFO 的满/空/近满/近空标志依赖跨时钟同步，测试中会等待额外的写时钟或读时钟后再严格断言。这不是放宽检查，而是避免在 CDC 传播尚未稳定时做错误判断。

---

## 与原 UVM 平台对比

| 对比项 | 原 SV UVM 平台 | 新 pyuvm/cocotb 平台 |
| :--- | :--- | :--- |
| 仿真入口 | `uvm_work/Makefile` | `pyuvm_work/Makefile` |
| 主要语言 | SystemVerilog/UVM | Python + pyuvm + cocotb |
| 默认工具链 | 原流程偏商业仿真器 | OSS CAD Suite Verilator |
| DUT 连接方式 | SV interface + UVM agent | cocotb 通过 DUT 端口句柄直接访问 |
| 激励方式 | sequence/driver | Python BFM/helper + pyuvm test |
| 数据检查 | SV scoreboard | Python `FifoScoreboard` |
| pass/fail 判断 | UVM report/scoreboard | Python `assert` |
| 覆盖率目标 | 原 UVM 平台更适合覆盖率闭合 | 本平台主要演示功能验证和断言判断 |

两套平台验证的是同一个异步 FIFO RTL。学习时可以先用 pyuvm/cocotb 理解基本测试结构和数据检查，再对照原 UVM 平台理解完整的 UVM 组件划分、coverage 和 sequence 机制。

---

## 建议学习顺序

1. 先阅读 `environment.yml` 和 Makefile，确认环境与构建入口。
2. 运行 `FifoSmokeTest`，确认 Verilator/cocotb/pyuvm 能启动。
3. 阅读 `fifo_bfm.py`，理解 Python 如何驱动 `wclk/rclk/winc/rinc/wdata`。
4. 阅读 `fifo_scoreboard.py`，理解期望队列和数据比较。
5. 阅读 `test_async_fifo.py` 中的测试类，从 `FifoSingleWriteReadTest` 逐步看到 random/stress/FWFT/OUT_REG。
6. 最后运行完整 `regression`，确认所有 Python assert 检查都通过。
