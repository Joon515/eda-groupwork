# pyuvm/cocotb 异步 FIFO 验证平台指南

## 文档概述

本文档说明当前项目中的标准化 **pyuvm + cocotb + Verilator** 异步 FIFO 验证平台。当前平台位于：

```text
prj_src/pyuvm_work/
```

它验证同一个 RTL 顶层 `async_fifo_top`，只编译 `prj_src/rtl_src/` 下的 RTL 文件，不编译 `prj_src/uvm_src/` 中的 SystemVerilog UVM 平台。原 SV UVM 平台仍保留；pyuvm 平台用于开源工具链下的 Python/UVM-style 验证。

---

## 环境准备

环境文件：

```text
prj_src/pyuvm_work/environment.yml
```

创建或更新 conda 环境后，建议用下面命令检查依赖：

```bash
conda run -n eda-pyuvm-fifo python -c "import cocotb, pyuvm, cocotb_coverage; print('ok')"
```

Verilator 由 OSS CAD Suite 提供，不在 conda 环境中全局安装。运行前确认 `verilator --version` 可用。

---

## 当前目录结构

```text
prj_src/pyuvm_work/
├── Makefile
├── environment.yml
├── test_async_fifo.py
├── coverage/
│   ├── fifo_coverage.xml
│   └── fifo_coverage.yml
└── pyuvm_fifo/
    ├── __init__.py
    ├── fifo_agent.py
    ├── fifo_bfm.py
    ├── fifo_config.py
    ├── fifo_coverage.py
    ├── fifo_env.py
    ├── fifo_item.py
    ├── fifo_scoreboard.py
    └── fifo_sequences.py
```

| 文件 | 作用 |
| :--- | :--- |
| `Makefile` | cocotb/Verilator 构建入口；支持参数覆盖、单测试筛选和回归目标。 |
| `test_async_fifo.py` | pyuvm 测试入口；测试类通过环境和序列启动激励。 |
| `fifo_config.py` | `FifoConfig` 配置对象和 ConfigDB helper，集中管理 DUT 参数、时钟、复位和延迟配置。 |
| `fifo_item.py` | typed command/observation items；避免使用无类型 dict 作为 transaction。 |
| `fifo_sequences.py` | reusable write/read/virtual sequences，包括 burst、boundary、random、FWFT 和 OUT_REG 场景。 |
| `fifo_agent.py` | write/read sequencer、driver、monitor、agent；driver 从 sequencer 取 command，monitor 采样公开端口。 |
| `fifo_scoreboard.py` | monitor-driven reference model scoreboard；只根据 monitor observation 更新模型。 |
| `fifo_coverage.py` | `cocotb-coverage` functional/cross coverage collector，并导出 XML/YAML。 |
| `fifo_env.py` | 标准 pyuvm 环境装配层，连接 agents、scoreboard 和 coverage。 |
| `fifo_bfm.py` | 低层 clock/reset helper；不再用于场景激励的直接 `write_word()`/`read_word()` 操作。 |

---

## 验证平台结构

当前 pyuvm 平台是 env/sequence-driven，而不是旧的 direct-BFM scenario suite：

1. 测试类在 `test_async_fifo.py` 中创建 `FifoConfig`，启动时钟/复位，并构建 `FifoEnv`。
2. 场景激励通过 `fifo_sequences.py` 中的 sequence 发送到 write/read sequencer。
3. `FifoWriteDriver` 和 `FifoReadDriver` 从 sequencer 获取 typed command item，然后驱动 `winc/rinc/wdata`。
4. `FifoWriteMonitor` 和 `FifoReadMonitor` 在 clock edge 后使用 `ReadOnly()` 采样公开输出和控制信号，发布 observation item。
5. Scoreboard 和 coverage 只消费 monitor observation，不从 driver command 直接更新参考模型。

这种结构更接近标准 UVM：sequence 负责“要做什么”，driver 负责“怎样驱动 pin”，monitor/scoreboard/coverage 负责独立观察和检查。

---

## Makefile 运行命令

以下命令均从仓库根目录执行。

### 单个测试

默认测试为 `FifoEnvSmokeTest`：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/pyuvm_work run
```

指定测试类：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/pyuvm_work run TESTCASE=FifoResetTest
```

### 参数覆盖

Makefile 支持 RTL 参数覆盖，例如 DEPTH、WIDTH、FWFT、OUT_REG 和 almost flag 参数：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/pyuvm_work run \
  TESTCASE=FifoAlmostFlagsCoverageTest \
  DEPTH=8 ALMOST_FULL_EN=1 ALMOST_FULL_VAL=2 \
  ALMOST_EMPTY_EN=1 ALMOST_EMPTY_VAL=2
```

### 回归目标

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/pyuvm_work regression-basic
conda run -n eda-pyuvm-fifo make -C prj_src/pyuvm_work regression-boundary
conda run -n eda-pyuvm-fifo make -C prj_src/pyuvm_work regression-advanced
conda run -n eda-pyuvm-fifo make -C prj_src/pyuvm_work regression-modes
conda run -n eda-pyuvm-fifo make -C prj_src/pyuvm_work regression
```

`regression` 会覆盖 smoke/basic、boundary、advanced、FWFT 和 OUT_REG latency 模式测试。

---

## 当前测试类

| 测试类 | 目的 |
| :--- | :--- |
| `FifoEnvSmokeTest` | 环境构建和最小 smoke。 |
| `FifoAgentSmokeTest` | write/read agent、sequencer、driver、monitor 基本连通性。 |
| `FifoResetTest` | 复位后公开标志和控制状态。 |
| `FifoSingleWriteReadTest` | 单次 sequence-driven 写入和读出。 |
| `FifoBoundaryTest` | full/empty 边界以及 blocked overflow/underflow attempts。 |
| `FifoAlmostFlagsCoverageTest` | almost full/empty 参数模式下的覆盖采样。 |
| `FifoConcurrentReadWriteTest` | 并发读写虚拟序列 smoke。 |
| `FifoRandomRegressionTest` | 固定 seed 的随机回归 smoke。 |
| `FifoStressTest` | 保守压力场景 smoke。 |
| `FifoCoverageClosureTest` | 覆盖导出和边界覆盖场景。 |
| `FifoFwftTest` | `FWFT_EN=1` 模式检查。 |
| `FifoOutRegLatencyTest` | `OUT_REG_EN=1` 读延迟模式检查。 |

---

## 覆盖率报告

覆盖率由 `pyuvm_fifo/fifo_coverage.py` 使用 `cocotb-coverage` 收集，回归或单测结束后导出：

```text
prj_src/pyuvm_work/coverage/fifo_coverage.xml
prj_src/pyuvm_work/coverage/fifo_coverage.yml
```

报告包含 operation、attempted/accepted、data pattern、occupancy region、public flag，以及 operation/flag cross 等 coverpoints/crosses。不要把文件存在理解为 100% coverage；当前报告会明确列出 uncovered bins，例如未命中的 data pattern、full/almost flag 和部分 cross bins。

---

## 常见问题

### 1. `verilator: command not found`

说明 OSS CAD Suite 没有正确加入 `PATH`。先确认：

```bash
verilator --version
```

### 2. conda 环境不存在

使用项目环境文件创建环境：

```bash
conda env create -f prj_src/pyuvm_work/environment.yml
```

### 3. 参数模式像是旧配置

Makefile 会把参数组合编码到 `sim_build/` 路径中，避免不同参数复用同一个 Verilator 可执行文件。若怀疑缓存问题，可清理后重跑：

```bash
conda run -n eda-pyuvm-fifo make -C prj_src/pyuvm_work clean
```

### 4. 为什么测试不直接调用 `write_word()` / `read_word()`？

这些 helper 只适合低层 bootstrap 或早期 scaffold。当前标准平台要求场景激励经过 sequence、sequencer 和 driver，这样 monitor-driven scoreboard 才能独立验证 DUT 行为，而不是把测试意图直接当成通过依据。

---

## 建议学习顺序

1. 阅读 `Makefile` 和 `fifo_config.py`，理解参数如何进入 DUT 和 pyuvm ConfigDB。
2. 阅读 `fifo_item.py` 和 `fifo_sequences.py`，理解 command/observation item 与 sequence stimulus。
3. 阅读 `fifo_agent.py`，理解 driver/monitor 如何按不同 clock domain 工作。
4. 阅读 `fifo_scoreboard.py`，确认 reference model 只由 monitor observation 更新。
5. 阅读 `fifo_coverage.py`，查看 coverage bins 和 XML/YAML 导出。
6. 运行 `FifoAgentSmokeTest`，再运行完整 `regression`。
