module tb_top;

    import uvm_pkg::*;
    `include "uvm_macros.svh"

    // 1. 定义时钟周期 (单位: ns)
    // 写时钟: 50MHz (周期 = 20ns)
    // 读时钟: 150MHz (周期 = 6.666ns, 采用 3.333ns 半周期以实现 3倍频关系)
    real WRITE_CLK_HALF_PERIOD = 10.000;
    real READ_CLK_HALF_PERIOD  = 3.333;

    logic wclk = 0;
    logic rclk = 0;
    logic wrst;
    logic rrst;

    // 2. 产生时钟信号
    always #WRITE_CLK_HALF_PERIOD wclk = ~wclk;
    always #READ_CLK_HALF_PERIOD  rclk = ~rclk;

    // 3. 实例化接口
    fifo_if #(.WIDTH(16)) intf();

    // 将外部产生的时钟连接至接口
    assign intf.wclk = wclk;
    assign intf.rclk = rclk;
    assign intf.wrst = wrst;
    assign intf.rrst = rrst;

    // 4. 实例化 DUT (配置深度 64，宽度 16)
    async_fifo_top #(
        .DEPTH(64),
        .WIDTH(16),
        .FWFT_EN(1'b0),          // 默认先验证标准模式
        .OUT_REG_EN(1'b0),       // 默认直通
        .RST_TYPE(fifo_cfg_pkg::ASYNC_SYNC_RELEASE), // 采用最安全的异步复位同步释放
        .RST_POLARITY(fifo_cfg_pkg::ACTIVE_LOW),      // 低电平有效
        .ALMOST_FULL_EN(1'b1),   // 开启将近满
        .ALMOST_FULL_VAL(4),
        .ALMOST_EMPTY_EN(1'b1),  // 开启将近空
        .ALMOST_EMPTY_VAL(4)
    ) dut (
        .wclk(intf.wclk),
        .wrst(intf.wrst),
        .winc(intf.winc),
        .wdata(intf.wdata),
        .wfull(intf.wfull),
        .walmost_full(intf.walmost_full),

        .rclk(intf.rclk),
        .rrst(intf.rrst),
        .rinc(intf.rinc),
        .rdata(intf.rdata),
        .rempty(intf.rempty),
        .ralmost_empty(intf.ralmost_empty)
    );

    // 5. 复位产生逻辑与 UVM 启动
    initial begin
        wrst = 1'b0; // 初始低电平复位
        rrst = 1'b0;
        
        // 维持 100ns 异步复位
        #100;
        wrst = 1'b1;
        rrst = 1'b1;
    end

    initial begin
        // 将接口注册进 uvm_config_db
        uvm_config_db#(virtual fifo_if)::set(null, "*", "vif", intf);
        
        // 启动 UVM 运行环境
        run_test();
    end

    // 6. 导出 FSDB 波形给 Verdi
    initial begin
        $fsdbDumpfile("tb_top.fsdb");
        $fsdbDumpvars(0, tb_top);
        $fsdbDumpMDA(); // 转储二维数组/RAM内部值
    end

endmodule