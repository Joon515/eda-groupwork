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

`endif // FIFO_SEQUENCE_SV