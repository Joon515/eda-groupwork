module async_fifo_top #(
    parameter int DEPTH = 64,
    parameter int WIDTH = 16
)(
    input  logic                 wclk,
    input  logic                 wrst_n,
    input  logic                 winc,
    input  logic [WIDTH-1:0]     wdata,
    output logic                 wfull,

    input  logic                 rclk,
    input  logic                 rrst_n,
    input  logic                 rinc,
    output logic [WIDTH-1:0]     rdata,
    output logic                 rempty
    );


    localparam int ADDR_WIDTH = $clog2(DEPTH);
    localparam int PTR_WIDTH  = ADDR_WIDTH + 1;
    localparam int MEM_DEPTH  = 1 << ADDR_WIDTH;

    logic [PTR_WIDTH-1:0] wptr_gray;

    logic [PTR_WIDTH-1:0] rptr_gray;

    logic [PTR_WIDTH-1:0] rptr_gray_sync_w2;
    logic [PTR_WIDTH-1:0] wptr_gray_sync_r2;
    logic [ADDR_WIDTH-1:0] waddr;
    logic [ADDR_WIDTH-1:0] raddr;

    sync_gray #(.WIDTH(PTR_WIDTH)) u_sync_r2w (
        .clk(wclk),
        .rst_n(wrst_n),
        .din(rptr_gray),
        .dout(rptr_gray_sync_w2)
    );

    sync_gray #(.WIDTH(PTR_WIDTH)) u_sync_w2r (
        .clk(rclk),
        .rst_n(rrst_n),
        .din(wptr_gray),
        .dout(wptr_gray_sync_r2)
    );

    wptr #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .PTR_WIDTH(PTR_WIDTH)
    ) u_write_pointer (
        .wclk(wclk),
        .wrst_n(wrst_n),
        .winc(winc),
        .rgray_sync(rptr_gray_sync_w2),
        .waddr(waddr),
        .wgray(wptr_gray),
        .wfull(wfull)
    );

    rptr #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .PTR_WIDTH(PTR_WIDTH)
    ) u_read_pointer (
        .rclk(rclk),
        .rrst_n(rrst_n),
        .rinc(rinc),
        .wgray_sync(wptr_gray_sync_r2),
        .raddr(raddr),
        .rgray(rptr_gray),
        .rempty(rempty)
    );

    dual_port_ram #(
        .WIDTH(WIDTH),
        .DEPTH(MEM_DEPTH)
    ) u_dual_port_ram (
        .wclk(wclk),
        .waddr(waddr),
        .winc(winc && !wfull),
        .wdata(wdata),
        .rclk(rclk),
        .raddr(raddr),
        .rinc(rinc && !rempty),
        .rdata(rdata)
    );

endmodule
