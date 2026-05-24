interface fifo_if;

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
    // 驱动专用时钟块 (Driver 只能写 output, 读 input)
    // ==========================================
    clocking w_cb @(posedge wclk);
        default input #1ns output #1ns;
        output winc;
        output wdata;
        input  wfull;
        input  walmost_full;
        input  wrst;
    endclocking

    clocking r_cb @(posedge rclk);
        default input #1ns output #1ns;
        output rinc;
        input  rdata;
        input  rempty;
        input  ralmost_empty;
        input  rrst;
    endclocking

    // ==========================================
    // 监视专用时钟块 (Monitor 只能读 input)
    // ==========================================
    clocking w_mon_cb @(posedge wclk);
        default input #1ns;
        input winc;
        input wdata;
        input wfull;
        input walmost_full;
        input wrst;
    endclocking

    clocking r_mon_cb @(posedge rclk);
        default input #1ns;
        input rinc;
        input rdata;
        input rempty;
        input ralmost_empty;
        input rrst;
    endclocking

    // 定义对应的 Modport (可选)
    modport w_mp (clocking w_cb, input wclk, input wrst);
    modport r_mp (clocking r_cb, input rclk, input rrst);

endinterface : fifo_if