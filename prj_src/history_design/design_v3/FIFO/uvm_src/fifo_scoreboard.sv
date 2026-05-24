`ifndef FIFO_SCOREBOARD_SV
`define FIFO_SCOREBOARD_SV

// 声明两个独立的分析端口导入宏，用于分别接收写 Monitor 和读 Monitor 的数据
`uvm_analysis_imp_decl(_write)
`uvm_analysis_imp_decl(_read)

class fifo_scoreboard #(
    parameter int WIDTH            = 16,
    parameter int DEPTH            = 64,
    parameter int ALMOST_FULL_VAL  = 4,
    parameter int ALMOST_EMPTY_VAL = 4
) extends uvm_scoreboard;

    `uvm_component_param_utils(fifo_scoreboard #(WIDTH, DEPTH, ALMOST_FULL_VAL, ALMOST_EMPTY_VAL))

    // 声明两个 imp 端口
    uvm_analysis_imp_write #(fifo_seq_item #(WIDTH), fifo_scoreboard #(WIDTH, DEPTH, ALMOST_FULL_VAL, ALMOST_EMPTY_VAL)) write_imp;
    uvm_analysis_imp_read  #(fifo_seq_item #(WIDTH), fifo_scoreboard #(WIDTH, DEPTH, ALMOST_FULL_VAL, ALMOST_EMPTY_VAL)) read_imp;

    // 虚拟接口（用于直接监测 DUT 上的控制信号状态，以便实时校验控制信号）
    virtual fifo_if vif;

    // Golden Model 核心：数据存储队列
    protected logic [WIDTH-1:0] expected_queue[$];

    // 用于统计的计数器
    int write_count = 0;
    int read_count  = 0;
    int error_count = 0;

    function new(string name = "fifo_scoreboard", uvm_component parent = null);
        super.new(name, parent);
        write_imp = new("write_imp", this);
        read_imp  = new("read_imp", this);
    endfunction : new

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        if (!uvm_config_db#(virtual fifo_if)::get(this, "", "vif", vif)) begin
            `uvm_fatal("NCOVIF", "Could not get virtual interface 'vif' from config_db")
        end
    endfunction : build_phase

    // ==========================================
    // 写入流接收回调函数 (来自 write_monitor)
    // ==========================================
    virtual function void write_write(fifo_seq_item #(WIDTH) item);
        write_count++;
        expected_queue.push_back(item.data);
        `uvm_info("SCB_WRITE", $sformatf("Recv Write: Data=16'h%4h | FIFO Current Depth = %0d", item.data, expected_queue.size()), UVM_HIGH)
        
        // 实时控制信号校验：写满校验
        check_control_signals();
    endfunction : write_write

    // ==========================================
    // 读取流接收回调函数 (来自 read_monitor)
    // ==========================================
    virtual function void write_read(fifo_seq_item #(WIDTH) item);
        logic [WIDTH-1:0] expected_data;
        read_count++;

        if (expected_queue.size() == 0) begin
            `uvm_error("SCB_UNDERFLOW", $sformatf("Underflow Error! DUT read out data 16'h%4h, but Golden Model is EMPTY!", item.data))
            error_count++;
            return;
        end

        expected_data = expected_queue.pop_front();
        `uvm_info("SCB_READ", $sformatf("Recv Read: Data=16'h%4h (Expected=16'h%4h) | FIFO Remaining = %0d", 
                  item.data, expected_data, expected_queue.size()), UVM_HIGH)

        // 比对读出数据是否正确 (FIFO 核心功能)
        if (item.data !== expected_data) begin
            `uvm_error("SCB_DATA_MISMATCH", $sformatf("Data Mismatch! DUT=16'h%4h, Exp=16'h%4h", item.data, expected_data))
            error_count++;
        end

        // 实时控制信号校验：读空校验
        check_control_signals();
    endfunction : write_read

    // ==========================================
    // 控制信号校验逻辑（支持异步时钟同步延迟分析）
    // ==========================================
    virtual function void check_control_signals();
        int current_depth = expected_queue.size();

        // 1. 校验写满信号 (wfull) 的 assertion 行为
        // 当 Golden Model 实际深度达到 DEPTH 时，写时钟域的 wfull 应该立刻拉高
        if (current_depth >= DEPTH && vif.wfull !== 1'b1) begin
            `uvm_error("SCB_CTRL_ERR", $sformatf("Full flag error! Size=%0d, but wfull is LOW!", current_depth))
            error_count++;
        end

        // 2. 校验读空信号 (rempty) 的 assertion 行为
        // 当 Golden Model 实际深度为 0 时，读时钟域的 rempty 应该立刻拉高
        if (current_depth == 0 && vif.rempty !== 1'b1) begin
            `uvm_error("SCB_CTRL_ERR", $sformatf("Empty flag error! Size=%0d, but rempty is LOW!", current_depth))
            error_count++;
        end

        // 3. 校验将近满信号 (walmost_full)
        // 设计要求：当剩余空间 <= ALMOST_FULL_VAL 时，将近满信号拉高
        if (ALMOST_FULL_VAL > 0) begin
            if ((DEPTH - current_depth) <= ALMOST_FULL_VAL) begin
                // 由于同步延迟，在写时钟域检测 walmost_full 允许有一拍到两拍的悲观延迟（即可能稍微晚一点拉高，但绝不能不拉高）
                if (vif.walmost_full !== 1'b1 && (DEPTH - current_depth) == 0) begin
                    `uvm_error("SCB_CTRL_ERR", $sformatf("Almost Full flag error! Remaining space=%0d, but walmost_full is LOW!", DEPTH - current_depth))
                    error_count++;
                end
            end
        end

        // 4. 校验将近空信号 (ralmost_empty)
        // 设计要求：当数据量 <= ALMOST_EMPTY_VAL 时，将近空信号拉高
        if (ALMOST_EMPTY_VAL > 0) begin
            if (current_depth <= ALMOST_EMPTY_VAL) begin
                if (vif.ralmost_empty !== 1'b1 && current_depth == 0) begin
                    `uvm_error("SCB_CTRL_ERR", $sformatf("Almost Empty flag error! Remaining items=%0d, but ralmost_empty is LOW!", current_depth))
                    error_count++;
                end
            end
        end
    endfunction : check_control_signals

    // ==========================================
    // 仿真结束检查 (Report Phase)
    // ==========================================
    virtual function void report_phase(uvm_phase phase);
        super.report_phase(phase);
        `uvm_info("SCB_REPORT", $sformatf("\n====== FIFO SCOREBOARD REPORT ======\n Writes Monitored: %0d\n Reads Monitored : %0d\n Unread Data Left: %0d\n Total Errors     : %0d\n====================================", 
                  write_count, read_count, expected_queue.size(), error_count), UVM_LOW)
        
        if (error_count == 0 && expected_queue.size() == 0) begin
            `uvm_info("SCB_STATUS", "STATUS: TEST PASSED SUCCESSFULLY!", UVM_LOW)
        end else begin
            `uvm_error("SCB_STATUS", "STATUS: TEST FAILED! Please check logs for details.", UVM_LOW)
        end
    endfunction : report_phase

endclass : fifo_scoreboard

`endif // FIFO_SCOREBOARD_SV