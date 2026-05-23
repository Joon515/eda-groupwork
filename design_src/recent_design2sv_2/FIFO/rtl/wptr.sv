module wptr #(
    parameter int ADDR_WIDTH = 6,
    parameter int PTR_WIDTH = ADDR_WIDTH + 1
)(
    input  logic                 wclk,
    input  logic                 wrst_n,
    input  logic                 winc,
    input  logic [PTR_WIDTH-1:0]  rgray_sync,
    output logic [ADDR_WIDTH-1:0] waddr,
    output logic [PTR_WIDTH-1:0]  wgray,
    output logic                 wfull
    );

    logic [PTR_WIDTH-1:0] wbin;
    logic [PTR_WIDTH-1:0] wbin_next;
    logic [PTR_WIDTH-1:0] wgray_next;

    // 计算下一个二进制地址和格雷码
    assign wbin_next  = wbin + (winc && !wfull);
    assign wgray_next = (wbin_next >> 1) ^ wbin_next;
    
    // 内存写入地址使用当前的二进制地址
    assign waddr = wbin[ADDR_WIDTH-1:0];

    // 满标志判断逻辑：最高位和次高位不同，其余位相同
    wire wfull_val = (wgray_next == {~rgray_sync[PTR_WIDTH-1:PTR_WIDTH-2], rgray_sync[PTR_WIDTH-3:0]});

    always_ff @(posedge wclk or negedge wrst_n) begin
        if (!wrst_n) begin
            wbin  <= '0;
            wgray <= '0;
            wfull <= 1'b0;
        end else begin
            wbin  <= wbin_next;
            wgray <= wgray_next;
            wfull <= wfull_val;
        end
    end

endmodule
