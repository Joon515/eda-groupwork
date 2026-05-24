# FIFO 覆盖率修补测试指南

## 概述

本文档详细说明了为解决特定覆盖率缺陷而设计的两个修补测试。这些测试经过精心设计，只需集成到现有的回归测试中，即可将覆盖率从 **98.51%** 提升至 **99%+**。

---

## 问题 1: 条件覆盖率不满 - 90% → 100%

### 根本原因分析

**位置**: `async_fifo_top.sv` 中 FWFT+OUT_REG 模式 (g_fwft_reg_mode)

**关键代码**:
```systemverilog
// 在 g_fwft_reg_mode generate 块内
assign rinc_internal = !rempty_raw && (!rdata_valid || rinc || !skid_valid);
```

**问题**:
- 这是一个三项 OR 表达式：`(!rdata_valid) || (rinc) || (!skid_valid)`
- 为了达到 100% 条件覆盖率，需要所有 8 种真假组合都出现过
- 当前测试只覆盖了其中大部分，但缺少某些特定的组合

### Skid Buffer 架构背景

FWFT 模式 + 输出寄存器采用经典的 Skid Buffer 架构：

```
     RAM 输出 (ram_rdata)
            |
            v
    ┌───────────────┐
    │  rdata_reg    │  <- 主输出寄存器 (rdata_valid 标记有效)
    └───────────────┘
            ^
            |
       ┌────┴────┐
       │          │
    (读取)    (缓存不读取的数据)
       │          │
       └────┬────┘
            |
    ┌───────────────┐
    │  skid_reg     │  <- 临时 skid 缓冲区 (skid_valid 标记有效)
    └───────────────┘
```

**控制逻辑**:
- 当外部不读 (`rinc=0`) 但内部可以读 (`!rempty_raw=1`)：
  - 如果 `rdata_valid=1`（主寄存器有数据），则数据进入 skid 缓冲区
  - 否则数据直接进入主寄存器
- `rinc_internal` 决定内部是否向 RAM 要新数据

### 修补方案: fifo_skid_buffer_coverage_vseq

**设计思路**:
- 在 FWFT=1, OUT_REG=1 配置下专门运行
- 通过精心设计的读写延迟组合，激发所有的状态转移
- 确保所有 (rdata_valid, rinc, skid_valid) 的组合都出现过

**四个阶段**:

#### 阶段 1: 初始填充 (delay=2)
```
目标状态: rdata_valid=?, skid_valid=?
- 写入 DEPTH/2 个数据，固定延迟=2
- 让内部逐渐从空状态填充数据
- rdata_valid 从 0 变为 1（首次有数据）
```

#### 阶段 2: 短延迟读出 (delay=1)
```
目标状态: 各种组合
- 读出 DEPTH/2 个数据，固定延迟=1
- 短延迟使得读取速率较慢
- rinc 在 0 和 1 之间切换
- 给 skid 缓冲区足够的机会填充和清空
- 激发 (rdata_valid=1, skid_valid=1) 的情况
```

#### 阶段 3: 随机混合读写 (delay=-1)
```
目标状态: 随机激发所有组合
- 并发写 500 条 + 读 500 条，都启用随机延迟
- FIFO 饱和度在 0-DEPTH 之间随机波动
- 激发更多的状态转移机会
```

#### 阶段 4: 背靠背高速操作 (delay=0)
```
目标状态: 极限压力激发
- 并发写 800 条 + 读 800 条，无延迟
- 最大频率切换 rdata_valid 和 skid_valid
- 确保即使在极高频下也能覆盖所有组合
```

### 验证覆盖的条件组合

经过这四个阶段，应该能覆盖以下所有 8 种组合：

| rdata_valid | skid_valid | rinc | rinc_internal 值 | 说明 |
|-----------|-----------|------|-----------------|------|
| 0 | 0 | 0 | 1 | 都没数据，可以读 |
| 0 | 0 | 1 | 1 | 都没数据，外部读 |
| 0 | 1 | 0 | 1 | skid有，可以读 |
| 0 | 1 | 1 | 1 | skid有，外部读 |
| 1 | 0 | 0 | 0 | 主有数据，外部不读 |
| 1 | 0 | 1 | 1 | 主有数据，外部读 |
| 1 | 1 | 0 | 0 | 都有数据，外部不读 |
| 1 | 1 | 1 | 1 | 都有数据，外部读 |

---

## 问题 2: 翻转覆盖率不满 - 97.51% → 99%+

### 根本原因分析

**受影响信号**: `wrst`, `rrst` (异步复位)

**信号特性** (ACTIVE_LOW):
- 正常工作: `wrst=1, rrst=1`
- 复位激活: `wrst=0, rrst=0`

**翻转类型**:
- **0→1**: 从复位状态释放到正常工作（✓ 已覆盖）
- **1→0**: 从正常工作回到复位状态（✗ 缺失）

**当前测试流程** (tb_top.sv):
```systemverilog
initial begin
    wrst = 1'b0;  // 初始化为 0 (复位激活)
    rrst = 1'b0;
    #100;         // 保持 100ns
    wrst = 1'b1;  // 释放到 1 (复位释放) ← 0→1 翻转
    rrst = 1'b1;
    // 之后就一直保持 1，没有再次拉低
end
```

**缺失的 1→0 翻转**:
- 没有任何点使得 `wrst/rrst` 从 1 变回 0
- 因此翻转覆盖率无法达到 100%

### 修补方案: fifo_reset_cycle_vseq

**设计思路**:
- 在测试运行过程中，手动控制 VIF 来切换复位信号
- 实现多个完整的复位周期
- 每个周期都包含 0→1 和 1→0 的翻转

**多周期复位序列**:

```
时间轴:
│
│  周期1: 初始工作状态
│  ├─ wrst=1, rrst=1 (来自 tb_top 初始化)
│  ├─ 执行读写 100 条
│  └─ 验证正常功能
│
├─ 周期2: 拉低复位 ← 1→0 翻转（缺失的覆盖！）
│  ├─ vif.wrst = 0, vif.rrst = 0
│  ├─ 保持 200ns 确保同步
│  └─ 所有内部状态被复位
│
├─ 周期3: 释放复位 ← 0→1 翻转
│  ├─ vif.wrst = 1, vif.rrst = 1
│  ├─ 等待 200ns 同步稳定
│  └─ 格雷码同步器输出稳定
│
├─ 周期4: 再次工作
│  ├─ 执行读写 100 条
│  └─ 验证复位后功能恢复
│
├─ 周期5: 再次拉低复位 ← 再现 1→0 翻转
│  ├─ vif.wrst = 0, vif.rrst = 0
│  └─ 保持 200ns
│
└─ 周期6: 再次释放复位 ← 再现 0→1 翻转
   ├─ vif.wrst = 1, vif.rrst = 1
   └─ 等待 200ns
```

### 关键实现细节

#### 1. VIF 访问

```systemverilog
virtual fifo_if vif;

if (!uvm_config_db#(virtual fifo_if)::get(null, "", "vif", vif)) begin
    `uvm_fatal("VIF_MISSING", "Could not get virtual interface for reset control")
end

// 直接操作 VIF 中的复位信号
vif.wrst = 1'b0;  // 拉低
vif.rrst = 1'b0;
#200ns;

vif.wrst = 1'b1;  // 拉高
vif.rrst = 1'b1;
#200ns;
```

#### 2. 复位时的状态检查

复位期间，需要验证所有相关信号都被复位：
- `wfull` 应该变为 0
- `rempty` 应该变为 1
- 内部指针应该回到初始值
- Scoreboard 应该被清空

#### 3. 复位释放后的恢复验证

```systemverilog
// 释放后立即进行读写操作
write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
write_seq.num_items = 100;
write_seq.fixed_delay = 0;

read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
read_seq.num_items = 100;
read_seq.fixed_delay = 0;

fork
    write_seq.start(w_sqr);
    read_seq.start(r_sqr);
join

// 验证数据完整性
```

---

## 运行这些修补测试

### 仅运行修补测试

```bash
# 仅运行条件覆盖修补 (需要 FWFT=1, OUT_REG=1)
make compile DEPTH=128 FWFT=1 OUT_REG=1
make sim TESTNAME=fifo_fwft_skid_buffer_test DEPTH=128 FWFT=1 OUT_REG=1

# 仅运行翻转覆盖修补 (可在任何配置)
make compile DEPTH=64 FWFT=0 OUT_REG=0
make sim TESTNAME=fifo_reset_cycle_test DEPTH=64 FWFT=0 OUT_REG=0
```

### 完整回归测试（包括修补）

```bash
# 在 uvm_work 目录
make run_all

# 查看覆盖率报告
make html_cov
```

### 检查覆盖率改进

```bash
# 编译时启用覆盖率收集
make compile

# 运行修补测试
make sim TESTNAME=fifo_fwft_skid_buffer_test TESTNAME=fifo_reset_cycle_test ...

# 合并覆盖率数据库
urg -dir ./simv.vdb -format both

# 打开 HTML 报告
open urgReport/dashboard.html
```

---

## 预期覆盖率提升

运行这两个修补测试后，预期覆盖率变化：

```
修补前:
├─ 代码行覆盖率:    100%
├─ 分支覆盖率:      100%
├─ 功能覆盖率:      100%
├─ 条件覆盖率:       90% ← 缺失
└─ 翻转覆盖率:    97.51% ← 缺失

修补后:
├─ 代码行覆盖率:    100%
├─ 分支覆盖率:      100%
├─ 功能覆盖率:      100%
├─ 条件覆盖率:      100% ← 修补完成 ✓
└─ 翻转覆盖率:      99%+ ← 修补完成 ✓

总体覆盖率: 98.51% → 99.5%+
```

---

## 故障排除

### 问题: 修补测试超时

**症状**: 测试在运行时挂起或超时

**解决方案**:
1. 检查 fifo_reset_cycle_vseq 中的延迟时间（应为 200ns）
2. 确认 VIF 访问正确
3. 查看 simv.log 找出具体卡在哪个阶段

### 问题: Skid Buffer 测试的数据不匹配

**症状**: Scoreboard 报告数据不匹配

**解决方案**:
1. 确认测试在 FWFT=1, OUT_REG=1 配置下运行
2. 检查数据宽度和深度设置是否正确
3. 在 Verdi 中查看 rdata_valid 和 skid_valid 的时序

### 问题: 翻转覆盖率仍未达到 100%

**症状**: 仍有少量翻转未被覆盖

**解决方案**:
1. 增加 fifo_reset_cycle_vseq 中的复位周期数（目前 3 次）
2. 在不同的操作状态下执行复位（当前已覆盖：空、有数据、满）
3. 检查 VIF 中是否还有其他复位相关的信号需要处理

---

## 参考资源

- RTL 设计: [async_fifo_top.sv](../rtl_src/async_fifo_top.sv)
- 序列定义: [fifo_sequence.sv](../uvm_src/fifo_sequence.sv)
- 测试定义: [fifo_test.sv](../uvm_src/fifo_test.sv)
- 完整文档: [TEST_SUITE.md](TEST_SUITE.md)

---

**最后更新**: 2026 年 5 月  
**版本**: 1.0

