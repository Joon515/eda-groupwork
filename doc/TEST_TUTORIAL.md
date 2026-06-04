# UVM验证框架中添加/修改测试 - 保姆级教学

## 📖 本文档定位

这是一份**完整的、零基础友好的**教程，手把手教你如何：

1. ✅ 添加**新的测试用例**
2. ✅ 创建**自定义序列**
3. ✅ **修改现有测试参数**
4. ✅ **扩展验证功能**

---

## 第一部分：了解当前框架

### 1.1 现有测试列表

当前项目中已有的测试用例：

| 测试名称 | 文件 | 功能 |
|---------|------|------|
| `fifo_random_test` | fifo_test.sv | 2000+随机并发读写 |
| `fifo_boundary_test` | fifo_test.sv | 满/空边界测试 |

### 1.2 现有序列列表

| 序列名称 | 文件 | 功能 |
|---------|------|------|
| `fifo_write_sequence` | fifo_sequence.sv | 随机写操作 |
| `fifo_read_sequence` | fifo_sequence.sv | 随机读操作 |
| `fifo_vseq_base` | fifo_sequence.sv | 虚拟序列基类 |

### 1.3 测试与序列的关系

```
┌────────────────┐
│  fifo_test     │ (继承 uvm_test)
├────────────────┤
│ run_phase()    │
│    ↓           │
│ 创建 vseq      │ (虚拟序列实例)
│    ↓           │
│ 挂载 Sequencer │
│    ↓           │
│ vseq.start()   │ → 启动序列
└────────────────┘
       │
       ├─→ 写序列(写Sequencer上运行)
       │      │
       │      └─→ Driver驱动硬件
       │
       └─→ 读序列(读Sequencer上运行)
              │
              └─→ Driver驱动硬件
```

---

## 第二部分：快速上手 - 修改参数

### 场景1：修改现有测试的FIFO深度

**目标**：将`fifo_random_test`的FIFO深度从64改为256。

#### 方法1：通过Makefile参数传递（推荐）

```bash
cd uvm_work/
make compile DEPTH=256
make sim TESTNAME=fifo_random_test DEPTH=256
```

**原理**：Makefile中的宏定义会覆盖tb_top.sv中的默认值：
```makefile
VCS_DEFINES = +define+CFG_DEPTH=$(DEPTH) ...
```

#### 方法2：直接修改代码（不推荐，会污染版本控制）

如果必须修改，编辑 [tb_top.sv](tb_top.sv#L21-L27)：

```systemverilog
`ifndef CFG_DEPTH
    `define CFG_DEPTH 256  ← 改为256
`endif
```

---

### 场景2：启用FWFT模式进行测试

**目标**：用FWFT模式运行现有的随机测试。

```bash
make compile FWFT=1 OUT_REG=0
make sim TESTNAME=fifo_random_test FWFT=1 OUT_REG=0
```

**效果**：DUT会使用0拍延迟的FWFT直通模式。

---

## 第三部分：创建自定义序列

### 场景3：创建"先写满再读空"的序列

**目标**：新建一个序列，该序列先往FIFO写满所有数据，再全部读出。

#### 步骤1：打开fifo_sequence.sv，在末尾添加新序列

在文件末尾（`endclass : fifo_vseq_base` 之后）添加：

```systemverilog
// =============================================================================
// 新增：写满再读空序列
// =============================================================================
class fifo_fill_then_drain_vseq #(parameter int WIDTH = 16) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_fill_then_drain_vseq #(WIDTH))

    int fifo_depth = 64;  // 需要和DUT的DEPTH一致（稍后会配置）

    function new(string name = "fifo_fill_then_drain_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) w_seq;
        fifo_read_sequence #(WIDTH)  r_seq;

        `uvm_info("VSEQ", "Starting fill_then_drain sequence", UVM_LOW)

        // ===== 阶段1：填满FIFO =====
        `uvm_info("VSEQ", "Phase 1: Filling FIFO to FULL...", UVM_LOW)
        w_seq = fifo_write_sequence#(WIDTH)::type_id::create("w_seq");
        w_seq.num_items = fifo_depth;      // 写入fifo_depth个数据
        w_seq.fixed_delay = 0;              // 连续写，无间隔
        w_seq.start(w_sqr);                 // 在写Sequencer上启动

        // 等待一段时间让FIFO稳定
        repeat(10) @(posedge w_sqr.get_sequencer_vif().wclk);

        // ===== 阶段2：读空FIFO =====
        `uvm_info("VSEQ", "Phase 2: Draining FIFO to EMPTY...", UVM_LOW)
        r_seq = fifo_read_sequence#(WIDTH)::type_id::create("r_seq");
        r_seq.num_items = fifo_depth;      // 读出fifo_depth个数据
        r_seq.fixed_delay = 0;              // 连续读，无间隔
        r_seq.start(r_sqr);                 // 在读Sequencer上启动

        `uvm_info("VSEQ", "Phase 1 & 2 completed!", UVM_LOW)
    endtask
endclass : fifo_fill_then_drain_vseq
```

#### 步骤2：在fifo_test.sv中创建新的测试用例

打开 [fifo_test.sv](fifo_test.sv)，在末尾添加：

```systemverilog
// =============================================================================
// 新增测试用例：写满再读空测试
// =============================================================================
class fifo_fill_drain_test extends fifo_base_test;
    `uvm_component_utils(fifo_fill_drain_test)

    function new(string name = "fifo_fill_drain_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_fill_then_drain_vseq #(16) vseq;

        phase.raise_objection(this);
        `uvm_info("TEST_START", "Executing fifo_fill_drain_test...", UVM_LOW)

        // 创建序列
        vseq = fifo_fill_then_drain_vseq#(16)::type_id::create("vseq");
        
        // 设置FIFO深度（与编译宏同步）
        vseq.fifo_depth = `CFG_DEPTH;
        
        // 挂载Sequencer
        vseq.w_sqr = env.w_agent.sqr;
        vseq.r_sqr = env.r_agent.sqr;

        // 启动虚拟序列
        vseq.start(null);

        `uvm_info("TEST_END", "fifo_fill_drain_test completed.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_fill_drain_test
```

#### 步骤3：运行新的测试

```bash
cd uvm_work/
make compile
make sim TESTNAME=fifo_fill_drain_test
```

**期望输出**：
```
UVM_INFO ... VSEQ: Starting fill_then_drain sequence
UVM_INFO ... VSEQ: Phase 1: Filling FIFO to FULL...
UVM_INFO ... VSEQ: Phase 2: Draining FIFO to EMPTY...
UVM_INFO ... VSEQ: Phase 1 & 2 completed!
```

---

### 场景4：创建特定数据模式的序列

**目标**：创建一个序列，写入特定的数据模式（例：0x0000, 0xFFFF, 0xAAAA, 0x5555 循环）。

```systemverilog
// =============================================================================
// 新增：固定数据模式序列
// =============================================================================
class fifo_pattern_write_sequence #(parameter int WIDTH = 16) extends uvm_sequence #(fifo_seq_item #(WIDTH));
    `uvm_object_param_utils(fifo_pattern_write_sequence #(WIDTH))

    int unsigned num_patterns = 4;  // 4种数据模式
    int unsigned repeat_count = 10; // 每种模式重复10次

    function new(string name = "fifo_pattern_write_sequence");
        super.new(name);
    endfunction

    virtual task body();
        logic [WIDTH-1:0] patterns[$] = {16'h0000, 16'hFFFF, 16'hAAAA, 16'h5555};

        repeat(repeat_count) begin
            foreach(patterns[i]) begin
                req = fifo_seq_item#(WIDTH)::type_id::create("req");
                start_item(req);

                if (!req.randomize() with {
                    is_write == 1'b1;
                    data == patterns[i];
                    delay inside {[0:2]};
                }) begin
                    `uvm_fatal("RAND_FAIL", "Randomization failed");
                end

                `uvm_info("SEQ_PATTERN", $sformatf("Writing pattern: 16'h%04x", patterns[i]), UVM_HIGH)
                finish_item(req);
            end
        end
    endtask
endclass : fifo_pattern_write_sequence
```

---

## 第四部分：创建新的测试类型

### 场景5：创建"压力测试"

**目标**：长时间、高频率的并发读写，测试FIFO的稳定性。

#### 步骤1：添加虚拟序列

在 [fifo_sequence.sv](fifo_sequence.sv) 末尾添加：

```systemverilog
// =============================================================================
// 新增：压力测试虚拟序列
// =============================================================================
class fifo_stress_vseq #(parameter int WIDTH = 16) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_stress_vseq #(WIDTH))

    int stress_iterations = 100;  // 压力测试循环次数

    function new(string name = "fifo_stress_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) w_seq;
        fifo_read_sequence #(WIDTH)  r_seq;

        `uvm_info("STRESS", "Starting stress test with 100 iterations...", UVM_LOW)

        repeat(stress_iterations) begin
            // 并行运行写和读（通过fork实现）
            fork
                begin
                    w_seq = fifo_write_sequence#(WIDTH)::type_id::create("w_seq");
                    w_seq.num_items = 50;
                    w_seq.start(w_sqr);
                end
                begin
                    r_seq = fifo_read_sequence#(WIDTH)::type_id::create("r_seq");
                    r_seq.num_items = 50;
                    r_seq.start(r_sqr);
                end
            join

            `uvm_info("STRESS", $sformatf("Iteration completed"), UVM_HIGH)
        end

        `uvm_info("STRESS", "Stress test completed!", UVM_LOW)
    endtask
endclass : fifo_stress_vseq
```

#### 步骤2：添加测试类

在 [fifo_test.sv](fifo_test.sv) 末尾添加：

```systemverilog
// =============================================================================
// 新增测试：压力测试
// =============================================================================
class fifo_stress_test extends fifo_base_test;
    `uvm_component_utils(fifo_stress_test)

    function new(string name = "fifo_stress_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_stress_vseq #(16) vseq;

        phase.raise_objection(this);
        `uvm_info("TEST_START", "Executing fifo_stress_test...", UVM_LOW)

        vseq = fifo_stress_vseq#(16)::type_id::create("vseq");
        vseq.w_sqr = env.w_agent.sqr;
        vseq.r_sqr = env.r_agent.sqr;
        vseq.stress_iterations = 100;

        vseq.start(null);

        `uvm_info("TEST_END", "fifo_stress_test completed.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_stress_test
```

#### 步骤3：运行

```bash
make compile
make sim TESTNAME=fifo_stress_test
```

---

## 第五部分：修改现有序列的行为

### 场景6：修改序列的延迟分布

**目标**：修改 `fifo_write_sequence` 使其默认有更大的延迟。

打开 [fifo_sequence.sv](fifo_sequence.sv)，找到 `fifo_write_sequence`，修改约束条件：

```systemverilog
class fifo_write_sequence #(parameter int WIDTH = 16) extends uvm_sequence #(fifo_seq_item #(WIDTH));
    // ...
    
    virtual task body();
        repeat(num_items) begin
            req = fifo_seq_item#(WIDTH)::type_id::create("req");
            start_item(req);
            
            // 修改约束：增加更多的延迟
            if (!req.randomize() with {
                is_write == 1'b1;
                // 原来: delay dist { 0 := 70, [1:3] := 20, [4:10] := 10 };
                // 修改为: 更多的间隔
                delay dist { 
                    0     := 30,   // 30% 连续
                    [1:5] := 40,   // 40% 短延迟
                    [6:15]:= 30    // 30% 长延迟
                };
                if (fixed_delay >= 0) { delay == fixed_delay; }
            }) begin
                `uvm_fatal("SEQ_RAND_FAIL", "Randomization failed in write sequence!")
            end
            
            finish_item(req);
        end
    endtask
endclass : fifo_write_sequence
```

**效果**：写操作会有更多的间隔，可以观察FIFO在非连续写入情况下的表现。

---

## 第六部分：扩展验证功能

### 场景7：添加自定义的控制信号检查

**目标**：在记分板中添加新的检查逻辑，验证"将近满"信号的反应时间。

打开 [fifo_scoreboard.sv](fifo_scoreboard.sv)，在 `check_control_signals()` 函数中添加：

```systemverilog
virtual function void check_control_signals();
    int current_depth = expected_queue.size();

    // ... 原有的检查代码 ...

    // ===== 新增：将近满响应时间检查 =====
    // 当FIFO深度从足够→接近满时，walmost_full应立刻拉高
    // (允许1-2拍延迟用于同步)
    if (ALMOST_FULL_EN && ALMOST_FULL_VAL > 0) begin
        if ((DEPTH - current_depth) <= (ALMOST_FULL_VAL * 2)) begin
            if (vif.walmost_full !== 1'b1 && current_depth >= (DEPTH - ALMOST_FULL_VAL)) begin
                `uvm_warning("SCB_ALMOST_FULL_DELAY", 
                    $sformatf("Almost full took extra cycles to assert. Depth=%0d, Threshold=%0d", 
                    current_depth, DEPTH - ALMOST_FULL_VAL))
            end
        end
    end
endfunction : check_control_signals
```

---

## 第七部分：完整工作流示例

### 从零开始创建一个完整的新测试

**需求**：创建一个"交替读写"测试，即：
1. 写1个数据
2. 读1个数据
3. 重复50次

#### 步骤1：创建序列

编辑 [fifo_sequence.sv](fifo_sequence.sv)，添加：

```systemverilog
class fifo_alternating_vseq #(parameter int WIDTH = 16) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_alternating_vseq #(WIDTH))

    int transaction_pairs = 50;  // 50对读写

    function new(string name = "fifo_alternating_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_seq_item #(WIDTH) write_req, read_req;

        `uvm_info("ALT_SEQ", "Starting alternating read/write sequence", UVM_LOW)

        repeat(transaction_pairs) begin
            // 步骤1：创建并发送写事务
            write_req = fifo_seq_item#(WIDTH)::type_id::create("write_req");
            fork
                begin
                    w_sqr.start_item(write_req);
                    if (!write_req.randomize() with {
                        is_write == 1'b1;
                        delay == 0;
                    }) `uvm_fatal("RAND", "Write randomization failed");
                    w_sqr.finish_item(write_req);
                end
                begin
                    // 步骤2：等待一些周期后发送读事务
                    #(50ns);  // 等待50ns确保数据已写入
                    read_req = fifo_seq_item#(WIDTH)::type_id::create("read_req");
                    r_sqr.start_item(read_req);
                    if (!read_req.randomize() with {
                        is_write == 1'b0;
                        delay == 0;
                    }) `uvm_fatal("RAND", "Read randomization failed");
                    r_sqr.finish_item(read_req);
                end
            join
        end

        `uvm_info("ALT_SEQ", "Alternating sequence completed", UVM_LOW)
    endtask
endclass : fifo_alternating_vseq
```

#### 步骤2：创建测试类

编辑 [fifo_test.sv](fifo_test.sv)，添加：

```systemverilog
class fifo_alternating_test extends fifo_base_test;
    `uvm_component_utils(fifo_alternating_test)

    function new(string name = "fifo_alternating_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_alternating_vseq #(16) vseq;

        phase.raise_objection(this);
        `uvm_info("TEST_START", "Starting fifo_alternating_test...", UVM_LOW)

        vseq = fifo_alternating_vseq#(16)::type_id::create("vseq");
        vseq.w_sqr = env.w_agent.sqr;
        vseq.r_sqr = env.r_agent.sqr;
        vseq.transaction_pairs = 50;

        vseq.start(null);

        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_alternating_test
```

#### 步骤3：运行

```bash
cd uvm_work
make compile
make sim TESTNAME=fifo_alternating_test
```

#### 步骤4：查看结果

检查仿真日志：
```
UVM_INFO ... ALT_SEQ: Starting alternating read/write sequence
UVM_INFO ... MON_WRITE: Monitored Write Data: 16'hXXXX
UVM_INFO ... MON_READ: Monitored Read Data: 16'hXXXX
...
UVM_INFO ... ALT_SEQ: Alternating sequence completed
```

---

## 第八部分：调试与验证

### 修改后如何验证新测试是否正确？

#### 方法1：检查log输出

```bash
# 查看仿真日志中是否有你新增的UVM_INFO
grep "ALT_SEQ" sim_*.log
```

#### 方法2：查看波形

```bash
# Verdi查看波形
make verdi
```

在Verdi中查看：
- `winc`/`wfull` - 写端信号
- `rinc`/`rempty` - 读端信号
- `wdata`/`rdata` - 数据流

#### 方法3：检查记分板的错误计数

在fifo_scoreboard的report_phase输出中查看：
```
====== FIFO SCOREBOARD REPORT ======
 Writes Monitored: X
 Reads Monitored : Y
 Unread Data Left: 0  ← 应该是0
 Total Errors     : 0  ← 应该是0
```

---

## 第九部分：最佳实践与常见错误

### ✅ 最佳实践

| 实践 | 说明 |
|------|------|
| **模块化设计** | 每个序列专注一个功能 |
| **清晰的命名** | `fifo_xxx_sequence` / `fifo_xxx_test` |
| **约束条件** | 用`randomize() with {...}`实现特定行为 |
| **虚拟序列** | 用于协调多个Agent的并行工作 |
| **日志输出** | 用`uvm_info/uvm_warning/uvm_error`记录 |

### ❌ 常见错误

| 错误 | 原因 | 解决 |
|------|------|------|
| **编译失败** | 语法错误或缺少类定义 | 检查 `endclass` |
| **Sequencer句柄为空** | 忘记在run_phase中赋值 | `vseq.w_sqr = env.w_agent.sqr;` |
| **数据不匹配** | 序列产生的数据与期望不符 | 检查约束条件 |
| **FIFO死锁** | 长时间不完成 | 检查虚拟序列的fork/join逻辑 |
| **时钟不同步** | 读写延迟不当 | 使用`@(posedge clk)`同步 |

---

## 第十部分：集成新测试到Makefile

### 添加新测试到回归套件

编辑 [uvm_work/Makefile](uvm_work/Makefile)，在 `run_all` target中添加：

```makefile
run_all:
	@echo "====== 开始多配置回归测试 ======"

	@echo "--- 模式 1: 标准模式测试 ---"
	$(MAKE) compile DEPTH=64 FWFT=0 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_random_test DEPTH=64 FWFT=0 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_fill_drain_test DEPTH=64 FWFT=0 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_alternating_test DEPTH=64 FWFT=0 OUT_REG=0

	@echo "--- 模式 2: FWFT模式测试 ---"
	$(MAKE) compile DEPTH=64 FWFT=1 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_random_test DEPTH=64 FWFT=1 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_stress_test DEPTH=64 FWFT=1 OUT_REG=0

	@echo "====== 回归测试完成 ======"
```

然后运行：

```bash
make run_all
```

---

## 快速参考：常用操作手册

### 修改FIFO参数

```bash
make compile DEPTH=256 WIDTH=32 FWFT=1 OUT_REG=1
make sim TESTNAME=fifo_random_test DEPTH=256 WIDTH=32 FWFT=1 OUT_REG=1
```

### 运行特定测试

```bash
make sim TESTNAME=fifo_boundary_test
make sim TESTNAME=fifo_fill_drain_test
make sim TESTNAME=fifo_stress_test
```

### 查看波形

```bash
make verdi
```

### 生成覆盖率报告

```bash
make html_cov
# 打开 urgReport/dashboard.html 查看
```

### 清除临时文件

```bash
make clean
```

---

## 完整代码模板

### 新序列模板

```systemverilog
class fifo_my_sequence #(parameter int WIDTH = 16) 
    extends uvm_sequence #(fifo_seq_item #(WIDTH));
    
    `uvm_object_param_utils(fifo_my_sequence #(WIDTH))
    
    int unsigned num_items = 10;

    function new(string name = "fifo_my_sequence");
        super.new(name);
    endfunction

    virtual task body();
        repeat(num_items) begin
            req = fifo_seq_item#(WIDTH)::type_id::create("req");
            start_item(req);
            
            if (!req.randomize() with {
                // 添加你的约束条件
            }) begin
                `uvm_fatal("RAND_FAIL", "Randomization failed");
            end
            
            finish_item(req);
        end
    endtask
endclass : fifo_my_sequence
```

### 新虚拟序列模板

```systemverilog
class fifo_my_vseq #(parameter int WIDTH = 16) 
    extends fifo_vseq_base #(WIDTH);
    
    `uvm_object_param_utils(fifo_my_vseq #(WIDTH))

    function new(string name = "fifo_my_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) w_seq;
        fifo_read_sequence #(WIDTH)  r_seq;

        `uvm_info("MY_VSEQ", "Starting my virtual sequence", UVM_LOW)

        // 你的测试逻辑
        w_seq = fifo_write_sequence#(WIDTH)::type_id::create("w_seq");
        w_seq.num_items = 50;
        w_seq.start(w_sqr);

        `uvm_info("MY_VSEQ", "Completed", UVM_LOW)
    endtask
endclass : fifo_my_vseq
```

### 新测试类模板

```systemverilog
class fifo_my_test extends fifo_base_test;
    `uvm_component_utils(fifo_my_test)

    function new(string name = "fifo_my_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_my_vseq #(16) vseq;

        phase.raise_objection(this);
        `uvm_info("MY_TEST", "Starting my test...", UVM_LOW)

        vseq = fifo_my_vseq#(16)::type_id::create("vseq");
        vseq.w_sqr = env.w_agent.sqr;
        vseq.r_sqr = env.r_agent.sqr;
        vseq.start(null);

        `uvm_info("MY_TEST", "Test completed.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase
endclass : fifo_my_test
```

---

## 总结

| 任务 | 文件 | 步骤 |
|------|------|------|
| 修改参数 | Makefile | `make compile DEPTH=xxx` |
| 创建序列 | fifo_sequence.sv | 添加class + task body() |
| 创建测试 | fifo_test.sv | 添加class + run_phase() |
| 运行测试 | 命令行 | `make sim TESTNAME=xxx` |
| 查看波形 | 命令行 | `make verdi` |
| 覆盖率 | 命令行 | `make html_cov` |

**记住**：每次修改代码后，需要重新编译：`make compile`

祝你验证顺利！🎉

