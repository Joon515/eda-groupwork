module async_fifo 
#(
    parameter DATA_WIDTH = 'd8,
    parameter DATA_DEPTH = 'd256
)
(
    input  wire                         sys_rst_n,
    //wr                        
    input  wire                         clk_wr,
    input  wire                         wr_en,
    input  wire     [DATA_WIDTH-1:0]    wr_data,
    //rd        
    input  wire                         clk_rd,
    input  wire                         rd_en,
    output wire     [DATA_WIDTH-1:0]    rd_data,
    //flag      
    output wire                         full,
    output wire                         empty
);

/*===计算指针位宽===*/
function integer clogb2(input integer num);
    for (clogb2 = 0; num > 0; clogb2 = clogb2 + 1) begin
        num = num >> 1;
    end
    
endfunction

/*===读写指针===*/
// 宽度要加一，用于空满判断
reg [clogb2(DATA_DEPTH-1):0] wr_ptr;
reg [clogb2(DATA_DEPTH-1):0] rd_ptr;

// 地址的有效的宽度不包括第一位
wire [clogb2(DATA_DEPTH-1)-1:0] wr_addr;
wire [clogb2(DATA_DEPTH-1)-1:0] rd_addr;

assign wr_addr = wr_ptr[clogb2(DATA_DEPTH-1)-1:0];
assign rd_addr = rd_ptr[clogb2(DATA_DEPTH-1)-1:0];

/*===读写指针移动===*/
// wr
always @(posedge clk_wr or negedge sys_rst_n) begin
    if (!sys_rst_n) begin
        wr_ptr <= 'b0;
    end
    else if((wr_en) && (!full)) begin
        wr_ptr <= wr_ptr + 'b1;
    end
    else
        wr_ptr <= wr_ptr;
end

// rd
always @(posedge clk_rd or negedge sys_rst_n) begin
    if (!sys_rst_n) begin
        rd_ptr <= 'b0;
    end
    else if((rd_en) && (!empty)) begin
        rd_ptr <= rd_ptr + 'b1;
    end
    else
        rd_ptr <= rd_ptr;
end

/*===将地址信号转化为格雷码===*/
wire [clogb2(DATA_DEPTH-1):0]  wr_ptr_gray;
wire [clogb2(DATA_DEPTH-1):0]  rd_ptr_gray;

assign wr_ptr_gray = wr_ptr^(wr_ptr >> 'b1); // wr
assign rd_ptr_gray = rd_ptr^(rd_ptr >> 'b1); // rd

/*===跨时钟传输指针信号===*/
// wr2rd
reg [clogb2(DATA_DEPTH-1):0]  wr_ptr_gray_reg1;
reg [clogb2(DATA_DEPTH-1):0]  wr_ptr_gray_reg2;

(* altera_attribute = "-name SYNCHRONIZER_IDENTIFICATION FORCED_IF_ASYNCHRONOUS" *)
always @(posedge clk_rd or negedge sys_rst_n) begin
    if (!sys_rst_n) begin
        wr_ptr_gray_reg1 <= 'b0;
        wr_ptr_gray_reg2 <= 'b0;
    end
    else begin
        wr_ptr_gray_reg1 <= wr_ptr_gray;
        wr_ptr_gray_reg2 <= wr_ptr_gray_reg1;
    end
end

// rd2wr
reg [clogb2(DATA_DEPTH-1):0]  rd_ptr_gray_reg1;
reg [clogb2(DATA_DEPTH-1):0]  rd_ptr_gray_reg2;

(* altera_attribute = "-name SYNCHRONIZER_IDENTIFICATION FORCED_IF_ASYNCHRONOUS" *)
always @(posedge clk_wr or negedge sys_rst_n) begin
    if (!sys_rst_n) begin
        rd_ptr_gray_reg1 <= 'b0;
        rd_ptr_gray_reg2 <= 'b0;
    end
    else begin
        rd_ptr_gray_reg1 <= rd_ptr_gray;
        rd_ptr_gray_reg2 <= rd_ptr_gray_reg1;
    end
end

/*===空满信号的判断===*/
// 使用读时钟域信号
assign empty = (rd_ptr_gray == wr_ptr_gray_reg2);
// 使用写时钟域信号
assign full = (wr_ptr_gray == {~rd_ptr_gray_reg2[clogb2(DATA_DEPTH-1)
                                                :clogb2(DATA_DEPTH-1)-1]
                                ,rd_ptr_gray_reg2[clogb2(DATA_DEPTH-1)-2
                                                :0]});

/*===ram_inst===*/
mem_ram # (
    .DATA_WIDTH(DATA_WIDTH),
    .DATA_DEPTH(DATA_DEPTH)
)
mem_ram_inst (
    .clk_wr(clk_wr),
    .wr_en(wr_en),
    .wr_addr(wr_addr),
    .wr_data(wr_data),
    .clk_rd(clk_rd),
    .rd_en(rd_en),
    .rd_addr(rd_addr),
    .rd_data(rd_data)
);




endmodule //async_fifo