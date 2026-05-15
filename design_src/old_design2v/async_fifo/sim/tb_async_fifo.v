`timescale 1ns/1ns
module tb_async_fifo;

// Parameters
localparam  DATA_WIDTH = 'd4;
localparam  DATA_DEPTH = 'd16;

//Ports
reg                         sys_rst_n;
reg                         clk_wr;
reg                         wr_en;
reg     [DATA_WIDTH-1:0]    wr_data;
reg                         clk_rd;
reg                         rd_en;
wire    [DATA_WIDTH-1:0]    rd_data;
wire                        full;
wire                        empty;

/*===initial===*/
initial begin
    clk_wr = 1'b1;
    clk_rd = 1'b1;

    sys_rst_n <= 1'b0;
    wr_en <= 1'b0;
    wr_data <= 4'b0;
    rd_en <= 1'b0;

    #20
    sys_rst_n <= 1'b1;

    #20
    wr_en <= 1'b1;
    #200
    wr_en <= 1'b0;
    rd_en <= 1'b1;
    #400
    rd_en <= 1'b0;
    #40
    rd_en <= 1'b1;
    wr_en <= 1'b1;
    #200
    rd_en <= 1'b1;
    wr_en <= 1'b0;
    #200
    rd_en <= 1'b0;
end

/*===clk===*/
always #5  clk_wr = ~clk_wr;
always #10 clk_rd = ~clk_rd;

/*===input_sig===*/
always @(posedge clk_wr or negedge sys_rst_n) begin
    if (!sys_rst_n) begin
        wr_data <= 4'b0;
    end
    else if((wr_data == 4'b1111) && (wr_en) && (!full)) begin
        wr_data <= 4'b0;
    end
    else if((wr_en) && (!full)) begin
        wr_data <= wr_data + 4'b1;
    end
    else
        wr_data <= wr_data;
end

/*===module_inst===*/
async_fifo # (
    .DATA_WIDTH(DATA_WIDTH),
    .DATA_DEPTH(DATA_DEPTH)
)
async_fifo_inst (
    .sys_rst_n(sys_rst_n),
    .clk_wr(clk_wr),
    .wr_en(wr_en),
    .wr_data(wr_data),
    .clk_rd(clk_rd),
    .rd_en(rd_en),
    .rd_data(rd_data),
    .full(full),
    .empty(empty)
);

endmodule