module dual_port_ram #(
    parameter int WIDTH = 16,
    parameter int DEPTH = 64,
    
)(
    input  logic                  wclk,
    input  logic [ADDR_WIDTH-1:0] waddr,
    input  logic                  winc,
    input  logic [WIDTH-1:0]      wdata,

    input  logic [ADDR_WIDTH-1:0] raddr,
    output logic [WIDTH-1:0]      rdata
    );

/*======================== Parameter and Internal Signal =========================*/
	localparam int ADDR_WIDTH = (DEPTH>1)?$clog2(DEPTH):1;

    logic [WIDTH-1:0] mem [0:DEPTH-1];

/*================================== Main Code ===================================*/
    always_ff @(posedge wclk) begin
        if (winc) begin
            mem[waddr] <= wdata;
        end
    end

    // 修改：改为异步读（组合逻辑输出）
    assign rdata = mem[raddr];

/*================================================================================*/

endmodule
