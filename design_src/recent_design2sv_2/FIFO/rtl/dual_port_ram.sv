module dual_port_ram #(
    parameter int WIDTH = 16,
    parameter int DEPTH = 64,
    localparam int ADDR_WIDTH = $clog2(DEPTH)
)(
    input  logic                 wclk,
    input  logic [ADDR_WIDTH-1:0] waddr,
    input  logic                 winc,
    input  logic [WIDTH-1:0]      wdata,
    input  logic                 rclk,
    input  logic [ADDR_WIDTH-1:0] raddr,
    input  logic                 rinc, // 虽然异步读，rinc 可保留用于逻辑门控或保持
    output logic [WIDTH-1:0]      rdata
    );

    logic [WIDTH-1:0] mem [0:DEPTH-1];

    always_ff @(posedge wclk) begin
        if (winc) begin
            mem[waddr] <= wdata;
        end
    end

    // 修改：改为异步读（组合逻辑输出）
    assign rdata = mem[raddr];

endmodule
