# 如何运行仿真并查看波形/覆盖率

本指南介绍如何在终端的 `uvm_work` 路径下，使用 Makefile 完整运行编译、仿真、波形调试、覆盖率收集以及豁免（Waiver）流程。

---

## A. 全自动回归测试
在命令行中执行以下命令，将一键自动完成所有模式（标准模式、头优先直通模式、带寄存器 FWFT 模式）下所有测试用例的编译与仿真：

```bash
make run_all
```

运行结束后，所有的仿真日志将被记录在 `sim_*.log` 中，覆盖率数据库将合并并保存在 `./simv.vdb` 中。

---

## B. 启动 Verdi 调试硬件波形
仿真运行完毕后，会自动在 `uvm_work` 路径下生成波形文件 `tb_top.fsdb`。键入以下指令即可一键启动 Verdi：

```bash
make verdi
```

> ⚠️ **注意（重要限制）**：由于多个测试用例在回归测试中串行运行，且共用同一个顶层波形输出路径，**`tb_top.fsdb` 仅保存最后一次运行的测试用例（即 `fifo_reset_cycle_test` 且 `DEPTH=128, FWFT=1, OUT_REG=1`）的波形。** 
> 
> 如果需要调试其他特定测试用例（例如 `fifo_random_test`）在特定配置下的波形，请先单步运行对应的仿真，例如：
> ```bash
> make compile DEPTH=64 FWFT=0 OUT_REG=0
> make sim TESTNAME=fifo_random_test DEPTH=64 FWFT=0 OUT_REG=0
> make verdi
> ```

---

## C. 覆盖率收敛与豁免 (Waiver) 指南

由于带寄存器的 FWFT 模式（Skid Buffer 架构）存在硬件状态机的物理互斥，条件覆盖率中会存在一个**无法达到的死区（Dead Logic）**。为了使覆盖率报告达到 100% 收敛，必须进行手动豁免。

### 1. 手把手创建豁免文件（仅需一次）
1. 启动 DVE 查看当前的覆盖率视图：
   ```bash
   make cov
   ```
2. 在 DVE 层次结构树中找到并双击 `async_fifo_top`(`tb_top.dut`)。
3. 定位到第 **253 行** 的子表达式条件表：
   `(((!g_fwft_reg_mode.rdata_valid)) || rinc || ((!g_fwft_reg_mode.skid_valid)))`
4. 找到状态为 `Not Covered` 的行（即 `[-1-, -2-, -3-] = [1, 0, 0]`）。
5. **右键**该行 $\rightarrow$ 选择 **Exclude**（排除）
6. 点击 DVE 菜单栏：**File** $\rightarrow$ **Save Exclusion...**，将文件保存为 **`cov_waives.el`**，存放在与 `Makefile` 相同的路径下。

---

### 2. 严格的豁免理由说明（Sign-off 归档标准）
在进行项目验收（Sign-off）时，请将以下推导理由写入文档或 DVE 豁免属性中：

```text
================================================================================
[Waiver ID]     : COV_WAIVE_FIFO_SKID_01
[Target Line]   : async_fifo_top.sv, Line 253
[Target Term]   : Cond [1, 0, 0] -> (!rdata_valid) && (!rinc) && (skid_valid)
[Classification]: Physically Unreachable State (Logical Mutual Exclusivity)
================================================================================
[Mathematical & Logical Proof]:
Let the state vector of the Skid Buffer be S = (rdata_valid, skid_valid).

1. Reset State: 
   During reset, both registers are cleared: S = (0, 0).
   
2. State Transition analysis from S = (0, 0):
   - To assert 'skid_valid' to 1, the following conditional block must be executed:
     "if (rdata_valid && !rinc) begin skid_valid <= 1'b1; end"
     This requires 'rdata_valid' to be already 1.
   - Therefore, S can transition from (0, 0) -> (1, 0) -> (1, 1). 
   - S can NEVER transition directly from (0, 0) to (0, 1).

3. State Transition analysis from S = (1, 1):
   - To clear 'rdata_valid' to 0, the logic must execute the "else if (rinc)" block.
   - Inside this block, since 'skid_valid' is 1, it executes:
     "if (skid_valid) begin rdata_valid <= 1'b1; skid_valid <= 1'b0; end"
     This clears 'skid_valid' to 0 while keeping 'rdata_valid' as 1.
   - Therefore, S can only transition from (1, 1) -> (1, 0).
   - There is NO physical pathway to transition from (1, 1) to (0, 1).

[Conclusion]:
The state S = (0, 1) (i.e., rdata_valid == 0 && skid_valid == 1) is mathematically
and logically unreachable in this Skid Buffer design.
Since the term under test [1, 0, 0] requires (!rdata_valid == 1) and (!skid_valid == 0),
which equivalent to (rdata_valid == 0) and (skid_valid == 1), this condition can
never be triggered in any simulation. This hole is safely waived.
================================================================================

================================================================================
[豁免 ID]       : COV_WAIVE_FIFO_SKID_01
[目标行]        : async_fifo_top.sv, 第 253 行
[目标条件项]    : Cond [1, 0, 0] -> (!rdata_valid) && (!rinc) && (skid_valid)
[分类]          : 物理不可达状态（逻辑互斥）
================================================================================
[数学与逻辑证明]:
设 Skid Buffer（滑行缓冲区）的状态向量为 S = (rdata_valid, skid_valid)。

1. 复位状态：
   在复位期间，两个寄存器都被清零：S = (0, 0)。
   
2. 从 S = (0, 0) 开始的状态转移分析：
   - 若要将 'skid_valid' 置 1，必须执行以下条件分支：
     "if (rdata_valid && !rinc) begin skid_valid <= 1'b1; end"
     这要求 'rdata_valid' 必须已经为 1。
   - 因此，S 的转移路径为 (0, 0) -> (1, 0) -> (1, 1)。
   - S 绝不可能直接从 (0, 0) 转移到 (0, 1)。

3. 从 S = (1, 1) 开始的状态转移分析：
   - 若要将 'rdata_valid' 清零（置 0），逻辑必须执行 "else if (rinc)" 分支。
   - 在该分支内部，由于 'skid_valid' 为 1，它会执行：
     "if (skid_valid) begin rdata_valid <= 1'b1; skid_valid <= 1'b0; end"
     这会将 'skid_valid' 清零（置 0），同时保持 'rdata_valid' 为 1。
   - 因此，S 只能从 (1, 1) 转移到 (1, 0)。
   - 没有任何物理路径可以实现从 (1, 1) 到 (0, 1) 的转移。

[结论]:
在该 Skid Buffer 设计中，状态 S = (0, 1)（即 rdata_valid == 0 且 skid_valid == 1）在数学和逻辑上都是不可达的。
由于待测条件项 [1, 0, 0] 要求 (!rdata_valid == 1) 且 (!skid_valid == 0)，这等价于 (rdata_valid == 0) 且 (skid_valid == 1)，因此该条件在任何仿真中都绝不可能被触发。该覆盖率漏洞可以安全地予以豁免（Waived）。
================================================================================
```
---

### 3. 生成加载了豁免的网页报告
当 `cov_waives.el` 文件存在于当前目录下时，运行以下命令：

```bash
make html_cov
```

该命令会自动将豁免規則应用到覆盖率合并数据库中。打开生成的网页报告，会发现第 253 行的条件覆盖率已被标记为 **100% Covered (Excluded)**。

---

## D. 清理重置工程
当仿真运行产生的大量临时文件占用磁盘空间时，可以执行清理。

```bash
make clean
```

> ⚠️ **非常重要（防误删说明）**：
> `make clean` 会安全地清除编译生成的临时 C 文件、可执行仿真文件 `simv`、所有的 `.log` 日志和波形文件。
> 
> 在 `uvm_work` 目录下，**以下文件是核心文件，绝对不能删除**：
> 1. **`Makefile`** （编译和控制脚本）
> 2. **`filelist`** （指示仿真源文件路径的文件列表）
> 3. **`cov_waives.el`** （手动生成的覆盖率豁免文件！一旦删除，必须重新通过 GUI 界面进行第 C 节的操作。）