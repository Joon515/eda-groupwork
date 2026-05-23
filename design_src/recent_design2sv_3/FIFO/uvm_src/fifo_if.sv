interface fifo_if;

    // 宽度与深度参数通过外部传递（此处默认值与DUT匹配）
    parameter int WIDTH = 16;

    // 写入时钟域
    logic                 wclk;
    logic                 wrst;
    logic                 winc;
    logic [WIDTH-1:0]     wdata;
    logic                 wfull;
    logic                 walmost_full;

    // 读取时钟域
    logic                 rclk;
    logic                 rrst;
    logic                 rinc;
    logic [WIDTH-1:0]     rdata;
    logic                 rempty;
    logic                 ralmost_empty;

    // ==========================================
    // 写入域 Clocking Block (用于 Driver/Monitor)
    // ==========================================
    clocking w_cb @(posedge wclk);
        default input #1ns output #1ns;
        output winc;
        output wdata;
        input  wfull;
        input  walmost_full;
        input  wrst;
    endclocking

    // ==========================================
    // 读取域 Clocking Block (用于 Driver/Monitor)
    // ==========================================
    clocking r_cb @(posedge rclk);
        default input #1ns output #1ns;
        output rinc;
        input  rdata;
        input  rempty;
        input  ralmost_empty;
        input  rrst;
    endclocking

    // 定义对应的 Modport
    modport w_mp (clocking w_cb, input wclk, input wrst);
    modport r_mp (clocking r_cb, input rclk, input rrst);

endinterface : fifo_if