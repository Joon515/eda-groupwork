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

    // 默认宏定义，若 VCS 命令行未指定，则使用默认标准参数
    `ifndef CFG_DEPTH
        `define CFG_DEPTH 64
    `endif
    `ifndef CFG_WIDTH
        `define CFG_WIDTH 16
    `endif
    `ifndef CFG_FWFT_EN
        `define CFG_FWFT_EN 1'b0
    `endif
    `ifndef CFG_OUT_REG_EN
        `define CFG_OUT_REG_EN 1'b0
    `endif

    // 4. 实例化 DUT (参数完全由外部编译宏配置)
    async_fifo_top #(
        .DEPTH(`CFG_DEPTH),
        .WIDTH(`CFG_WIDTH),
        .FWFT_EN(`CFG_FWFT_EN),
        .OUT_REG_EN(`CFG_OUT_REG_EN),
        .RST_TYPE(fifo_cfg_pkg::ASYNC_SYNC_RELEASE), 
        .RST_POLARITY(fifo_cfg_pkg::ACTIVE_LOW),      
        .ALMOST_FULL_EN(1'b1),   
        .ALMOST_FULL_VAL(4),
        .ALMOST_EMPTY_EN(1'b1),  
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