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

### 与 SystemVerilog UVM 的对应关系

| UVM 概念 | 本项目 pyuvm 实现 | 学习要点 |
| :--- | :--- | :--- |
| `uvm_test` | `test_async_fifo.py` 中的 `FifoEnvTestBase` 和派生测试类 | 测试类负责创建配置、启动时钟/复位、选择并启动 sequence。 |
| `uvm_env` | `pyuvm_fifo/fifo_env.py::FifoEnv` | env 只做组件构建和 TLM 连接，不直接写 DUT pin。 |
| `uvm_agent` | `FifoWriteAgent` / `FifoReadAgent` | 按写/读两个 clock domain 拆分 agent；active agent 构建 sequencer + driver + monitor。 |
| `uvm_sequencer` | `FifoWriteSequencer` / `FifoReadSequencer` | sequence item 的调度通道，连接 driver 的 `seq_item_port`。 |
| `uvm_driver` | `FifoWriteDriver` / `FifoReadDriver` | 把抽象 command 转成 `winc/wdata` 或 `rinc` 引脚时序。 |
| `uvm_monitor` | `FifoWriteMonitor` / `FifoReadMonitor` | 只观察 DUT，在 clock edge 后采样稳定信号并发出 observation。 |
| `uvm_sequence_item` | `FifoCommandItem` | 表示“写一个数据”或“读一次”的抽象命令。 |
| analysis port/export | `analysis_port`、`write_export`、`read_export` | monitor 将 observation 广播给 scoreboard 和 coverage。 |
| scoreboard | `FifoScoreboard` / `FifoReferenceModel` | 使用独立参考队列检查读写顺序、溢出/下溢和数据一致性。 |
| functional coverage | `FifoCoverage` | 用 `cocotb-coverage` 统计操作、数据模式、占用区间、flag 与 cross。 |

---

## pyuvm 实现学习讲解

这一节按“从测试入口到检查结果”的数据流讲解当前实现，适合第一次学习 pyuvm 时对照源码阅读。

### 1. 测试入口：`test_async_fifo.py`

`FifoEnvTestBase` 继承 `pyuvm.uvm_test`，它完成所有测试共享的启动逻辑：

1. `build_phase()` 中获取 `cocotb.top`，通过 `FifoConfig.from_env(self.dut)` 读取 Makefile 导出的 `DEPTH/WIDTH/FWFT_EN/...` 参数。
2. 使用 `set_fifo_config(self, self.cfg)` 将配置写入 pyuvm `ConfigDB`，使 env、agent、driver、monitor、scoreboard 都能读取同一份配置。
3. 创建 `FifoEnv("env", self)`。
4. `run_phase()` 中先 `raise_objection()`，启动 clock/reset，然后运行派生测试类实现的 `run_fifo_sequence()`。
5. sequence 完成后等待跨时钟域状态稳定，最后调用 scoreboard 检查是否有错误。

派生测试类只关心“场景是什么”。例如 `FifoSingleWriteReadTest` 创建一个 `WriteBurstSeq` 和一个 `ReadBurstSeq`，然后分别启动在 write/read sequencer 上。这样测试类不直接操作 `winc`、`rinc`、`wdata`，避免把测试写成 pin-level 脚本。

### 2. 配置传递：`fifo_config.py`

`FifoConfig` 是一个集中配置对象，保存：

- RTL 参数：`width`、`depth`、`fwft_en`、`out_reg_en`、`sync_stages`、almost flag 参数；
- 仿真参数：写/读时钟周期、复位周期、超时周期；
- DUT handle：`dut`。

`read_latency` 是一个很重要的派生属性：

- `FWFT_EN=1` 时读延迟为 0，因为首个字可以直接出现在读口；
- 普通模式读延迟为 1 个 `rclk`；
- `OUT_REG_EN=1` 时读延迟为 2 个 `rclk`。

这使 read monitor 不需要硬编码某一种 FIFO 模式，而是根据配置决定何时采样 `rdata`。

### 3. transaction 建模：`fifo_item.py`

当前平台刻意区分两类 item：

1. **Command item**：`FifoCommandItem`，由 sequence 产生、driver 消费。它表达“我要写/读、数据是什么、延迟几拍、是否允许尝试满写/空读”。
2. **Observation item**：`FifoWriteObservation` / `FifoReadObservation`，由 monitor 产生、scoreboard 和 coverage 消费。它表达“DUT 实际发生了什么”。

这个区分非常关键：scoreboard 不应直接相信 sequence 的意图。只有 monitor 观察到一次写被 DUT 接受（`attempted && !wfull`），参考模型才入队；只有 monitor 观察到一次读被 DUT 接受（`attempted && !rempty`），参考模型才出队并比较数据。

### 4. sequence：`fifo_sequences.py`

sequence 负责生成可复用的命令流：

- `WriteBurstSeq`：生成固定数量写命令，可选择随机、递增、全 0、全 1、交替、walking bit、boundary 等数据模式；
- `ReadBurstSeq`：生成固定数量读命令；
- `FillFifoSeq` / `DrainFifoSeq`：用于构造满/空边界；
- `AlternatingPatternSeq`、`FwftSingleWordSeq`、`OutRegLatencySeq`：用于特定功能模式；
- `ConcurrentRandomVirtualSeq`、`StressVirtualSeq`：同时调度读写 sequence，模拟并发压力。

`FifoCommandSequence.body()` 的核心很简单：遍历 command list，依次 `start_item(item)` 和 `finish_item(item)`。这正是 UVM sequence 的典型写法：sequence 不知道 DUT pin，只把抽象 transaction 交给 sequencer/driver。

### 5. driver：`fifo_agent.py`

写 driver 和读 driver 分别在自己的 clock domain 工作：

- `FifoWriteDriver` 从 write sequencer 获取 `FifoCommandItem`，按 `delay` 等待若干 `wclk`，然后驱动 `wdata` 和单拍 `winc`；
- `FifoReadDriver` 从 read sequencer 获取 command，按 `delay` 等待若干 `rclk`，然后驱动单拍 `rinc`；
- `allow_when_full` / `allow_when_empty` 用于边界测试，让 driver 等到满/空状态后仍尝试一次非法方向操作，以验证 DUT 正确阻塞。

driver 的职责是“忠实驱动命令”，不是判断测试是否通过。判断交给 monitor-driven scoreboard。

### 6. monitor：`fifo_agent.py`

monitor 是该平台最值得学习的部分之一：

- write monitor 在 `wclk` 上升沿后进入 `ReadOnly()` 阶段采样，检测 `winc` 上升为一次 attempted write，并根据 `wfull` 判断是否 accepted；
- read monitor 在 `rclk` 上升沿后采样，检测 `rinc` 上升为一次 attempted read，并根据 `rempty` 判断是否 accepted；
- 对有读延迟的模式，read monitor 用 `_publish_accepted_read()` 延后 `read_latency` 个 `rclk` 再采样 `rdata`。

使用 `ReadOnly()` 的原因是：在 cocotb 中它表示当前仿真时间步信号已经稳定，monitor 在这个阶段读信号更接近硬件观察者，而不是和 driver 抢同一时刻写信号。

### 7. env 连接：`fifo_env.py`

`FifoEnv` 的职责很克制：

1. `build_phase()` 创建 write agent、read agent、scoreboard、coverage；
2. `connect_phase()` 把 write/read monitor 的 analysis port 同时连接到 scoreboard 和 coverage；
3. `check_phase()` 调用 scoreboard 做最终检查；
4. `report_phase()` 输出 scoreboard/coverage 报告。

这符合 UVM 的分层原则：env 只负责装配，不直接知道某个测试要写多少数据，也不直接碰 DUT pin。

### 8. scoreboard：`fifo_scoreboard.py`

`FifoReferenceModel` 内部用 `deque` 保存期望读出的 FIFO 数据：

- 观察到 accepted write：把 `wdata` mask 到当前 `WIDTH` 后入队；
- 观察到 blocked write 且 `wfull=1`：计数为 overflow attempt，但不入队；
- 观察到 accepted read：从队首弹出并与 `rdata` 比较；
- 观察到 blocked read 且 `rempty=1`：计数为 underflow attempt，但不出队；
- 如果出现满模型仍 accepted write、空模型仍 accepted read、或读出数据不匹配，就记录结构化错误。

这个 scoreboard 是 monitor-driven 的：它只基于 DUT 公开端口观察结果更新模型，不基于 driver command 更新模型。因此如果 driver 发出了写命令但 DUT 因 `wfull` 阻塞，参考模型不会错误入队。

### 9. coverage：`fifo_coverage.py`

`FifoCoverage` 同样消费 monitor observation，并统计：

- operation：write/read；
- attempted/accepted：是否尝试、是否被接受；
- data pattern：zero、all ones、alternating、other；
- occupancy region：empty、one、low、mid、almost-full region、full；
- public flags：`wfull`、`rempty`、`walmost_full`、`ralmost_empty`；
- operation/attempt/accept 与 flag cross。

覆盖率报告导出到：

```text
prj_src/pyuvm_work/coverage/fifo_coverage.xml
prj_src/pyuvm_work/coverage/fifo_coverage.yml
```

覆盖率的学习重点是：测试通过只说明已执行场景没有发现错误；覆盖率用于回答“我们是否真的刺激到了关键状态和组合”。

### 10. 为什么保留 `fifo_bfm.py`？

`fifo_bfm.py` 主要保留 clock/reset 等底层 helper。当前标准平台不建议测试直接调用低层 `write_word()` / `read_word()` 式操作，因为那会绕过 sequence、driver、monitor、scoreboard 的 UVM-style 数据流。对于学习来说，可以把 BFM 理解为最低层工具，而不是验证场景的主要组织方式。

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
