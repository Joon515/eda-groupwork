module mem_ram 
#(
    parameter DATA_WIDTH = 'd8,
    parameter DATA_DEPTH = 'd256
)
(
    input  wire                                clk_wr,
    input  wire                                wr_en,
    input  wire   [clogb2(DATA_DEPTH-1)-1:0]   wr_addr,
    input  wire   [DATA_WIDTH-1:0]             wr_data,

    input  wire                                clk_rd,
    input  wire                                rd_en,
    input  wire   [clogb2(DATA_DEPTH-1)-1:0]   rd_addr,
    output reg    [DATA_WIDTH-1:0]             rd_data
);

/*===计算指针位宽===*/
function integer clogb2(input integer num);
    for (clogb2 = 0; num > 0; clogb2 = clogb2 + 1) begin
        num = num >> 1;
    end
    
endfunction

/*===例化一个ram===*/
reg [DATA_WIDTH-1:0] dual_ram [0:DATA_DEPTH-1];

/*===数据写入===*/
always @(posedge clk_wr) begin
    if (wr_en) begin
        dual_ram[wr_addr] <= wr_data;
    end
end

/*===数据读出===*/
always @(posedge clk_rd) begin
    if (rd_en) begin
        rd_data <= dual_ram[rd_addr];
    end
end

endmodule //mem_ram