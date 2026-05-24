# 覆盖率修补测试 - 快速参考

## 🎯 目标

通过两个专项修补测试，将覆盖率从 **98.51%** 提升至 **99%+**

## 📊 覆盖率现状

| 指标 | 当前 | 问题 | 修补 |
|------|------|------|------|
| 代码行覆盖 | 100% | ✓ | - |
| 分支覆盖 | 100% | ✓ | - |
| 功能覆盖 | 100% | ✓ | - |
| **条件覆盖** | **90%** | ❌ async_fifo_top FWFT | `fifo_fwft_skid_buffer_test` |
| **翻转覆盖** | **97.51%** | ❌ wrst/rrst 1→0 | `fifo_reset_cycle_test` |

## 🛠️ 两个修补测试

### 1️⃣ Skid Buffer 覆盖测试 - 条件覆盖率修补

| 项 | 值 |
|---|---|
| **测试名** | `fifo_fwft_skid_buffer_test` |
| **序列名** | `fifo_skid_buffer_coverage_vseq` |
| **配置** | **必须**: FWFT=1, OUT_REG=1 |
| **推荐深度** | DEPTH=32 或 128 |
| **运行模式** | Mode 3 专用 |
| **修补内容** | 覆盖 `(!rdata_valid \|\| rinc \|\| !skid_valid)` 的所有8种组合 |
| **运行时间** | ~600ns |

**快速运行**:
```bash
make compile DEPTH=128 FWFT=1 OUT_REG=1
make sim TESTNAME=fifo_fwft_skid_buffer_test DEPTH=128 FWFT=1 OUT_REG=1
```

---

### 2️⃣ 复位周期测试 - 翻转覆盖率修补

| 项 | 值 |
|---|---|
| **测试名** | `fifo_reset_cycle_test` |
| **序列名** | `fifo_reset_cycle_vseq` |
| **配置** | 任意（所有模式都运行） |
| **修补内容** | 覆盖 wrst/rrst 的 **1→0 翻转** (缺失部分) |
| **周期数** | 3 个完整的复位周期（6次翻转：0→1→0→1→0→1） |
| **运行时间** | ~1µs |

**快速运行**:
```bash
make compile DEPTH=64 FWFT=0 OUT_REG=0
make sim TESTNAME=fifo_reset_cycle_test DEPTH=64 FWFT=0 OUT_REG=0
```

---

## 🚀 集成方式

### 方式 A: 自动集成（推荐）

```bash
cd uvm_work
make run_all
```

这会自动运行所有配置模式的所有测试，包括两个修补测试：
- Mode1: 7个测试 (包含 fifo_reset_cycle_test)
- Mode2: 7个测试 (包含 fifo_reset_cycle_test)
- Mode3: 8个测试 (包含 fifo_fwft_skid_buffer_test + fifo_reset_cycle_test)

### 方式 B: 单独运行修补测试

```bash
# 仅条件覆盖修补
make compile DEPTH=128 FWFT=1 OUT_REG=1
make sim TESTNAME=fifo_fwft_skid_buffer_test DEPTH=128 FWFT=1 OUT_REG=1

# 仅翻转覆盖修补
make compile DEPTH=64 FWFT=0 OUT_REG=0
make sim TESTNAME=fifo_reset_cycle_test DEPTH=64 FWFT=0 OUT_REG=0
```

---

## 📈 预期覆盖率改进

运行修补测试后：

```
修补前          修补后
────────────    ────────────
代码行: 100%    代码行: 100%
分支: 100%      分支: 100%
功能: 100%      功能: 100%
条件: 90%   →   条件: 100% ✓
翻转: 97.51% →  翻转: 99%+  ✓
────────────    ────────────
总体: 98.51%    总体: 99%+
```

---

## 🔍 验证修补成功

### 查看覆盖率报告

```bash
# 合并所有覆盖率数据
make html_cov

# 打开 HTML 报告
open urgReport/dashboard.html
# 或
firefox urgReport/dashboard.html
```

### 查看日志

```bash
# 查看Skid Buffer测试日志
less sim_fifo_fwft_skid_buffer_test_dp128_fwft1_reg1.log
# 搜索: "VSEQ_SKID" 看各个阶段

# 查看复位测试日志
less sim_fifo_reset_cycle_test_dp64_fwft0_reg0.log
# 搜索: "VSEQ_RST" 看各个周期
```

### 在波形中验证

```bash
# 打开 Verdi 查看波形
make verdi

# 在 Verdi 中搜索:
# 1. fifo_fwft_skid_buffer_test: rdata_valid, skid_valid, rinc_internal 的转移
# 2. fifo_reset_cycle_test: wrst, rrst 的 1→0 翻转
```

---

## ❓ 常见问题

### Q: 修补测试需要修改 RTL 吗？
**A**: 不需要。修补测试仅通过测试激发现有 RTL 的不同代码路径。

### Q: 两个修补测试可以并行运行吗？
**A**: 可以。它们互不干扰，可以在 `run_all` 中自动并行处理（取决于 Makefile）。

### Q: Skid Buffer 测试必须在 FWFT=1, OUT_REG=1 下运行吗？
**A**: 是的。Skid Buffer 架构只在这个配置下使用。其他配置会使用不同的输出逻辑。

### Q: 翻转覆盖率为什么要在所有模式都运行复位测试？
**A**: 虽然 wrst/rrst 信号相同，但在不同配置下的 DUT 内部处理可能不同，因此需要在所有配置下都验证。

### Q: 如果修补后仍未达到 100%，怎么办？
**A**: 
1. 检查是否所有测试都正确运行（查看日志）
2. 在波形工具中手动验证覆盖的条件组合
3. 参考 COVERAGE_PATCH.md 了解详细的实现原理
4. 可能需要微调延迟参数或增加测试周期

---

## 📚 详细参考

完整的实现细节和原理请参考: [COVERAGE_PATCH.md](COVERAGE_PATCH.md)

---

## 📝 修改记录

| 日期 | 版本 | 变更 |
|------|------|------|
| 2026-05 | 1.0 | 初始创建 - 两个覆盖率修补测试 |

