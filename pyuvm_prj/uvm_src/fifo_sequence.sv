`ifndef FIFO_SEQUENCE_SV
`define FIFO_SEQUENCE_SV

// =============================================================================
// 1. 基础写入序列
// =============================================================================
class fifo_write_sequence #(parameter int WIDTH = 16) extends uvm_sequence #(fifo_seq_item #(WIDTH));
    `uvm_object_param_utils(fifo_write_sequence #(WIDTH))

    int unsigned      num_items   = 10;
    int               fixed_delay = -1; // 若为非负数，则强行覆盖随机延迟为固定值

    function new(string name = "fifo_write_sequence");
        super.new(name);
    endfunction

    virtual task body();
        repeat(num_items) begin
            req = fifo_seq_item#(WIDTH)::type_id::create("req");
            start_item(req);
            
            // 约束为写操作
            if (!req.randomize() with {
                is_write == 1'b1;
                if (fixed_delay >= 0) { delay == fixed_delay; }
            }) begin
                `uvm_fatal("SEQ_RAND_FAIL", "Randomization failed in write sequence!")
            end
            
            finish_item(req);
        end
    endtask
endclass : fifo_write_sequence


// =============================================================================
// 2. 基础读取序列
// =============================================================================
class fifo_read_sequence #(parameter int WIDTH = 16) extends uvm_sequence #(fifo_seq_item #(WIDTH));
    `uvm_object_param_utils(fifo_read_sequence #(WIDTH))

    int unsigned      num_items   = 10;
    int               fixed_delay = -1;

    function new(string name = "fifo_read_sequence");
        super.new(name);
    endfunction

    virtual task body();
        repeat(num_items) begin
            req = fifo_seq_item#(WIDTH)::type_id::create("req");
            start_item(req);
            
            // 约束为读操作
            if (!req.randomize() with {
                is_write == 1'b0;
                if (fixed_delay >= 0) { delay == fixed_delay; }
            }) begin
                `uvm_fatal("SEQ_RAND_FAIL", "Randomization failed in read sequence!")
            end
            
            finish_item(req);
        end
    endtask
endclass : fifo_read_sequence


// =============================================================================
// 3. 顶层虚拟序列基类 (用于协调写/读 Sequencer)
// =============================================================================
class fifo_vseq_base #(parameter int WIDTH = 16) extends uvm_sequence #(uvm_sequence_item);
    `uvm_object_param_utils(fifo_vseq_base #(WIDTH))

    // 句柄指向具体的物理 Sequencer
    uvm_sequencer #(fifo_seq_item #(WIDTH)) w_sqr;
    uvm_sequencer #(fifo_seq_item #(WIDTH)) r_sqr;

    function new(string name = "fifo_vseq_base");
        super.new(name);
    endfunction
endclass : fifo_vseq_base


// =============================================================================
// 4. 场景一：随机数据写满再读空序列
// =============================================================================
class fifo_full_empty_vseq #(
    parameter int WIDTH = 16,
    parameter int DEPTH = 64
) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_full_empty_vseq #(WIDTH, DEPTH))

    function new(string name = "fifo_full_empty_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) write_seq;
        fifo_read_sequence  #(WIDTH) read_seq;

        `uvm_info("VSEQ_FULL_EMPTY", "Starting Full-Then-Empty Scenario...", UVM_LOW)

        // Step 1: 连续写入直至写满 (写入深度+2的数据，不带延迟，触发 wfull)
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = DEPTH + 2;
        write_seq.fixed_delay = 0; // 无延迟，最大背靠背写入
        write_seq.start(w_sqr);

        // 稍微等待几个写/读时钟同步周期
        #100ns;

        // Step 2: 连续读取直至读空 (读取深度+2的数据，不带延迟，触发 rempty)
        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = DEPTH + 2;
        read_seq.fixed_delay = 0;
        read_seq.start(r_sqr);

        #100ns;
        `uvm_info("VSEQ_FULL_EMPTY", "Finished Full-Then-Empty Scenario.", UVM_LOW)
    endtask
endclass : fifo_full_empty_vseq


// =============================================================================
// 5. 场景二：2000组随机并发读写序列
// =============================================================================
class fifo_random_mixed_vseq #(parameter int WIDTH = 16) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_random_mixed_vseq #(WIDTH))

    function new(string name = "fifo_random_mixed_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) write_seq;
        fifo_read_sequence  #(WIDTH) read_seq;

        `uvm_info("VSEQ_MIXED", "Starting 2000-packet Random Parallel Read/Write Scenario...", UVM_LOW)

        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = 1000; // 1000组写
        write_seq.fixed_delay = -1;   // 启用随机延迟

        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = 1000; // 1000组读
        read_seq.fixed_delay = -1;   // 启用随机延迟

        // 并发执行写和读动作，利用时钟域驱动
        fork
            write_seq.start(w_sqr);
            read_seq.start(r_sqr);
        join

        #200ns;
        `uvm_info("VSEQ_MIXED", "Finished 2000-packet Random Parallel Read/Write Scenario.", UVM_LOW)
    endtask
endclass : fifo_random_mixed_vseq


// =============================================================================
// 6. 场景三：极限边界溢出/下溢测试序列（写满再写，读空再读）
// =============================================================================
class fifo_extreme_boundary_vseq #(
    parameter int WIDTH = 16,
    parameter int DEPTH = 64
) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_extreme_boundary_vseq #(WIDTH, DEPTH))

    function new(string name = "fifo_extreme_boundary_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) write_seq;
        fifo_read_sequence  #(WIDTH) read_seq;

        `uvm_info("VSEQ_BOUNDARY", "Starting Extreme Boundary Scenario (Overflow and Underflow)...", UVM_LOW)

        // 1. 先写到满
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = DEPTH;
        write_seq.fixed_delay = 0;
        write_seq.start(w_sqr);
        #50ns;

        // 2. 满状态下强行再执行 10 次写入，测试 wfull 是否保持拉高，DUT 内部指针不溢出
        write_seq.num_items   = 10;
        write_seq.fixed_delay = 1; // 带点间隙写入
        write_seq.start(w_sqr);
        #100ns;

        // 3. 将 FIFO 完全清空
        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = DEPTH;
        read_seq.fixed_delay = 0;
        read_seq.start(r_sqr);
        #50ns;

        // 4. 空状态下强行再执行 10 次读取，测试 rempty 是否保持拉高，且 Scoreboard 能够过滤非法读取
        read_seq.num_items   = 10;
        read_seq.fixed_delay = 1;
        read_seq.start(r_sqr);
        #100ns;

        `uvm_info("VSEQ_BOUNDARY", "Finished Extreme Boundary Scenario.", UVM_LOW)
    endtask
endclass : fifo_extreme_boundary_vseq


// =============================================================================
// 7. 场景四：满信号/空信号切换测试序列
// 验证：满信号拉高→写入停止→读出数据→满信号下降
//      空信号拉高→读取停止→写入数据→空信号下降
// =============================================================================
class fifo_full_empty_toggle_vseq #(
    parameter int WIDTH = 16,
    parameter int DEPTH = 64
) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_full_empty_toggle_vseq #(WIDTH, DEPTH))

    function new(string name = "fifo_full_empty_toggle_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) write_seq;
        fifo_read_sequence  #(WIDTH) read_seq;

        `uvm_info("VSEQ_TOGGLE", "Starting Full/Empty Toggle Test Scenario...", UVM_LOW)

        // 循环3轮：充满->清空->充满->清空...
        repeat(3) begin
            // 第一步：连续写入直到 FIFO 满
            `uvm_info("VSEQ_TOGGLE", "Phase 1: Writing until FULL...", UVM_LOW)
            write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
            write_seq.num_items   = DEPTH;
            write_seq.fixed_delay = 0;
            write_seq.start(w_sqr);
            #200ns;

            // 第二步：FIFO 满状态下停止写入，开始读出数据，验证满信号下降
            `uvm_info("VSEQ_TOGGLE", "Phase 2: Reading from FULL FIFO, verifying FULL signal drops...", UVM_LOW)
            read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
            read_seq.num_items   = DEPTH / 2;  // 只读出一半
            read_seq.fixed_delay = 0;
            read_seq.start(r_sqr);
            #100ns;

            // 第三步：清空剩余数据，验证空信号拉高
            `uvm_info("VSEQ_TOGGLE", "Phase 3: Reading until EMPTY, verifying EMPTY signal raises...", UVM_LOW)
            read_seq.num_items   = DEPTH;
            read_seq.fixed_delay = 0;
            read_seq.start(r_sqr);
            #200ns;

            // 第四步：FIFO 空状态下停止读取，写入数据，验证空信号下降
            `uvm_info("VSEQ_TOGGLE", "Phase 4: Writing to EMPTY FIFO, verifying EMPTY signal drops...", UVM_LOW)
            write_seq.num_items   = DEPTH / 2;
            write_seq.fixed_delay = 0;
            write_seq.start(w_sqr);
            #100ns;
        end

        `uvm_info("VSEQ_TOGGLE", "Finished Full/Empty Toggle Test Scenario.", UVM_LOW)
    endtask
endclass : fifo_full_empty_toggle_vseq


// =============================================================================
// 8. 场景五：压力测试序列 - 高频率并发读写
// 持续进行频繁的读写操作，测试 FIFO 在极限条件下的稳定性和数据完整性
// =============================================================================
class fifo_stress_test_vseq #(parameter int WIDTH = 16) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_stress_test_vseq #(WIDTH))

    function new(string name = "fifo_stress_test_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) write_seq;
        fifo_read_sequence  #(WIDTH) read_seq;

        `uvm_info("VSEQ_STRESS", "Starting Stress Test - High Frequency Parallel Read/Write...", UVM_LOW)

        // 进行5轮高强度读写混合，每轮都是背靠背的操作
        repeat(5) begin
            write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
            write_seq.num_items   = 2000;  // 大量写入
            write_seq.fixed_delay = 0;     // 无延迟，背靠背

            read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
            read_seq.num_items   = 2000;   // 大量读出
            read_seq.fixed_delay = 0;      // 无延迟，背靠背

            // 并发执行，施加最大压力
            fork
                write_seq.start(w_sqr);
                read_seq.start(r_sqr);
            join

            #500ns;
        end

        `uvm_info("VSEQ_STRESS", "Finished Stress Test.", UVM_LOW)
    endtask
endclass : fifo_stress_test_vseq


// =============================================================================
// 9. 场景六：延迟行为测试序列
// 测试不同延迟配置下的 FIFO 行为：零延迟、固定延迟、随机延迟
// =============================================================================
class fifo_delay_behavior_vseq #(
    parameter int WIDTH = 16,
    parameter int DEPTH = 64
) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_delay_behavior_vseq #(WIDTH, DEPTH))

    function new(string name = "fifo_delay_behavior_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) write_seq;
        fifo_read_sequence  #(WIDTH) read_seq;

        `uvm_info("VSEQ_DELAY", "Starting Delay Behavior Test Scenario...", UVM_LOW)

        // 测试 1：零延迟快速读写
        `uvm_info("VSEQ_DELAY", "Test 1: Zero-delay back-to-back read/write...", UVM_LOW)
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = 500;
        write_seq.fixed_delay = 0;
        
        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = 500;
        read_seq.fixed_delay = 0;

        fork
            write_seq.start(w_sqr);
            read_seq.start(r_sqr);
        join
        #100ns;

        // 测试 2：固定延迟读写
        `uvm_info("VSEQ_DELAY", "Test 2: Fixed-delay read/write (delay=5)...", UVM_LOW)
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = 500;
        write_seq.fixed_delay = 5;
        
        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = 500;
        read_seq.fixed_delay = 5;

        fork
            write_seq.start(w_sqr);
            read_seq.start(r_sqr);
        join
        #100ns;

        // 测试 3：随机延迟读写
        `uvm_info("VSEQ_DELAY", "Test 3: Random-delay read/write...", UVM_LOW)
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = 500;
        write_seq.fixed_delay = -1;  // 启用随机延迟
        
        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = 500;
        read_seq.fixed_delay = -1;   // 启用随机延迟

        fork
            write_seq.start(w_sqr);
            read_seq.start(r_sqr);
        join
        #100ns;

        `uvm_info("VSEQ_DELAY", "Finished Delay Behavior Test Scenario.", UVM_LOW)
    endtask
endclass : fifo_delay_behavior_vseq


// =============================================================================
// 10. 场景七：将近满/近空信号对齐测试序列
// 验证 almost_full/almost_empty 信号与实际 FIFO 占用情况的对齐关系
// =============================================================================
class fifo_almost_full_empty_vseq #(
    parameter int WIDTH = 16,
    parameter int DEPTH = 64,
    parameter int ALMOST_FULL_THR = 4,
    parameter int ALMOST_EMPTY_THR = 4
) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_almost_full_empty_vseq #(WIDTH, DEPTH, ALMOST_FULL_THR, ALMOST_EMPTY_THR))

    function new(string name = "fifo_almost_full_empty_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) write_seq;
        fifo_read_sequence  #(WIDTH) read_seq;

        `uvm_info("VSEQ_ALMOST", $sformatf("Starting Almost Full/Empty Alignment Test (THR_F=%0d, THR_E=%0d)...", 
                                           ALMOST_FULL_THR, ALMOST_EMPTY_THR), UVM_LOW)

        // 阶段 1：精确控制 FIFO 填充, 验证 almost_full 信号
        // 写入 (DEPTH - ALMOST_FULL_THR - 1) 个数据，此时 almost_full 应该还未拉高
        `uvm_info("VSEQ_ALMOST", "Phase 1: Writing to near-FULL threshold (almost_full should not raise yet)...", UVM_LOW)
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = DEPTH - ALMOST_FULL_THR - 1;
        write_seq.fixed_delay = 1;
        write_seq.start(w_sqr);
        #100ns;

        // 阶段 2：继续写入 ALMOST_FULL_THR 个数据，此时 almost_full 应该拉高
        `uvm_info("VSEQ_ALMOST", "Phase 2: Writing to trigger almost_full signal...", UVM_LOW)
        write_seq.num_items   = ALMOST_FULL_THR + 2;
        write_seq.fixed_delay = 1;
        write_seq.start(w_sqr);
        #100ns;

        // 阶段 3：读出所有数据，验证 almost_empty 信号
        // 读出 ALMOST_EMPTY_THR + 1 个数据，此时 almost_empty 应该还未拉高
        `uvm_info("VSEQ_ALMOST", "Phase 3: Reading to near-EMPTY threshold (almost_empty should not raise yet)...", UVM_LOW)
        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = DEPTH - ALMOST_EMPTY_THR - 1;
        read_seq.fixed_delay = 1;
        read_seq.start(r_sqr);
        #100ns;

        // 阶段 4：继续读取 ALMOST_EMPTY_THR 个数据，此时 almost_empty 应该拉高
        `uvm_info("VSEQ_ALMOST", "Phase 4: Reading to trigger almost_empty signal...", UVM_LOW)
        read_seq.num_items   = ALMOST_EMPTY_THR + 2;
        read_seq.fixed_delay = 1;
        read_seq.start(r_sqr);
        #100ns;

        `uvm_info("VSEQ_ALMOST", "Finished Almost Full/Empty Alignment Test Scenario.", UVM_LOW)
    endtask
endclass : fifo_almost_full_empty_vseq


// =============================================================================
// 11. 场景八：Skid Buffer 覆盖测试序列 (FWFT + OUT_REG 模式专用)
// 覆盖 FWFT 模式下 rdata_valid/skid_valid 的所有状态组合
// 确保条件表达式 (!rdata_valid || rinc || !skid_valid) 的100%覆盖
// =============================================================================
class fifo_skid_buffer_coverage_vseq #(
    parameter int WIDTH = 16,
    parameter int DEPTH = 32
) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_skid_buffer_coverage_vseq #(WIDTH, DEPTH))

    function new(string name = "fifo_skid_buffer_coverage_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) write_seq;
        fifo_read_sequence  #(WIDTH) read_seq;

        `uvm_info("VSEQ_SKID", "Starting Skid Buffer Coverage Test (FWFT+REG mode)...", UVM_LOW)

        // 测试场景设计：覆盖 skid buffer 的所有状态
        // 目标状态：
        //   rdata_valid=0, skid_valid=0  <- 输出寄存器和 skid 都空
        //   rdata_valid=0, skid_valid=1  <- 只有 skid 有数据
        //   rdata_valid=1, skid_valid=0  <- 只有输出寄存器有数据
        //   rdata_valid=1, skid_valid=1  <- 都有数据

        // 阶段 1：初始状态（都空）+ 填充数据
        `uvm_info("VSEQ_SKID", "Phase 1: Fill FIFO to populate registers...", UVM_LOW)
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = DEPTH / 2;
        write_seq.fixed_delay = 2;
        write_seq.start(w_sqr);
        #100ns;

        // 阶段 2：快速读出，用不同的读延迟激发 skid buffer 状态切换
        // 目标：让 rdata_valid 从 0 变为 1，然后可能 skid_valid 也变为 1
        `uvm_info("VSEQ_SKID", "Phase 2: Read with intermittent delays to trigger skid transitions...", UVM_LOW)
        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = DEPTH / 2;
        read_seq.fixed_delay = 1;  // 短延迟，让 skid 有机会存储数据
        read_seq.start(r_sqr);
        #200ns;

        // 阶段 3：随机读写混合，进一步激发状态转移
        `uvm_info("VSEQ_SKID", "Phase 3: Random mixed read/write to trigger all skid states...", UVM_LOW)
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = 500;
        write_seq.fixed_delay = -1;  // 随机延迟

        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = 500;
        read_seq.fixed_delay = -1;   // 随机延迟

        fork
            write_seq.start(w_sqr);
            read_seq.start(r_sqr);
        join
        #200ns;

        // 阶段 4：背靠背快速操作，压力激发
        `uvm_info("VSEQ_SKID", "Phase 4: Back-to-back operations to stress skid buffer transitions...", UVM_LOW)
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = 800;
        write_seq.fixed_delay = 0;

        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = 800;
        read_seq.fixed_delay = 0;

        fork
            write_seq.start(w_sqr);
            read_seq.start(r_sqr);
        join
        #200ns;

        `uvm_info("VSEQ_SKID", "Finished Skid Buffer Coverage Test.", UVM_LOW)
    endtask
endclass : fifo_skid_buffer_coverage_vseq


// =============================================================================
// 12. 场景九：复位周期测试序列
// 测试复位信号在多个周期内的完整切换（0→1→0→1...）
// 确保 wrst/rrst 的翻转覆盖达到100% (包括 1→0 的翻转)
// =============================================================================
class fifo_reset_cycle_vseq #(parameter int WIDTH = 16) extends fifo_vseq_base #(WIDTH);
    `uvm_object_param_utils(fifo_reset_cycle_vseq #(WIDTH))

    function new(string name = "fifo_reset_cycle_vseq");
        super.new(name);
    endfunction

    virtual task body();
        fifo_write_sequence #(WIDTH) write_seq;
        fifo_read_sequence  #(WIDTH) read_seq;
        virtual fifo_if vif;
        
        if (!uvm_config_db#(virtual fifo_if)::get(null, "", "vif", vif)) begin
            `uvm_fatal("VIF_MISSING", "Could not get virtual interface for reset control")
        end

        `uvm_info("VSEQ_RST", "Starting Reset Cycle Test (0→1→0→1 transitions)...", UVM_LOW)

        // 第一个周期：正常工作
        `uvm_info("VSEQ_RST", "Cycle 1: Normal operation (wrst=1, rrst=1)...", UVM_LOW)
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = 100;
        write_seq.fixed_delay = 0;

        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = 100;
        read_seq.fixed_delay = 0;

        fork
            write_seq.start(w_sqr);
            read_seq.start(r_sqr);
        join
        #100ns;

        // 第二个周期：拉低复位（1→0 翻转，这是缺失的覆盖）
        `uvm_info("VSEQ_RST", "Cycle 2: Assert reset (wrst=0, rrst=0) - 1→0 transition...", UVM_LOW)
        vif.wrst = 1'b0;
        vif.rrst = 1'b0;
        #200ns;  // 保持复位 200ns，确保所有内部状态被复位

        // 第三个周期：释放复位（0→1 翻转）
        `uvm_info("VSEQ_RST", "Cycle 3: Release reset (wrst=1, rrst=1) - 0→1 transition...", UVM_LOW)
        vif.wrst = 1'b1;
        vif.rrst = 1'b1;
        #200ns;  // 等待同步稳定

        // 第四个周期：再次正常工作
        `uvm_info("VSEQ_RST", "Cycle 4: Resume normal operation...", UVM_LOW)
        write_seq = fifo_write_sequence#(WIDTH)::type_id::create("write_seq");
        write_seq.num_items   = 100;
        write_seq.fixed_delay = 0;

        read_seq = fifo_read_sequence#(WIDTH)::type_id::create("read_seq");
        read_seq.num_items   = 100;
        read_seq.fixed_delay = 0;

        fork
            write_seq.start(w_sqr);
            read_seq.start(r_sqr);
        join
        #100ns;

        // 第五个周期：再次拉低复位（再现 1→0）
        `uvm_info("VSEQ_RST", "Cycle 5: Assert reset again (wrst=0, rrst=0) - 1→0 transition #2...", UVM_LOW)
        vif.wrst = 1'b0;
        vif.rrst = 1'b0;
        #200ns;

        // 第六个周期：再次释放复位（再现 0→1）
        `uvm_info("VSEQ_RST", "Cycle 6: Release reset again (wrst=1, rrst=1) - 0→1 transition #2...", UVM_LOW)
        vif.wrst = 1'b1;
        vif.rrst = 1'b1;
        #200ns;

        `uvm_info("VSEQ_RST", "Finished Reset Cycle Test.", UVM_LOW)
    endtask
endclass : fifo_reset_cycle_vseq

`endif // FIFO_SEQUENCE_SV