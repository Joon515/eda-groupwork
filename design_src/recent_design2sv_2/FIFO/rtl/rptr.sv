module rptr #(
    parameter int ADDR_WIDTH = 6,
)(
    input  logic                  rclk,
    input  logic                  rrst_n,
    input  logic                  rinc,
    input  logic [PTR_WIDTH-1:0]  wgray_sync,
    output logic [ADDR_WIDTH-1:0] raddr,
    output logic [PTR_WIDTH-1:0]  rgray,
    output logic                  rempty
    );

/*======================== Parameter and Internal Signal =========================*/
    localparam int PTR_WIDTH = ADDR_WIDTH + 1

    logic [PTR_WIDTH-1:0] rbin;
    logic [PTR_WIDTH-1:0] rbin_next;
    logic [PTR_WIDTH-1:0] rgray_next;


/*================================== Main Code ===================================*/
    assign rbin_next  = rbin + (rinc && !rempty);
    assign rgray_next = (rbin_next >> 1) ^ rbin_next;
    
    // 内存读取地址
    assign raddr = rbin[ADDR_WIDTH-1:0];

    // 空标志判断逻辑：读格雷码等于同步过来的写格雷码
    wire rempty_val = (rgray_next == wgray_sync);

    always_ff @(posedge rclk or negedge rrst_n) begin
        if (!rrst_n) begin
            rbin   <= '0;
            rgray  <= '0;
            rempty <= 1'b1; // 复位时为空
        end else begin
            rbin   <= rbin_next;
            rgray  <= rgray_next;
            rempty <= rempty_val;
        end
    end

/*================================================================================*/

endmodule
