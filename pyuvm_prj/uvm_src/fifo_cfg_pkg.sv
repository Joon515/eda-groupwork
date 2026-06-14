`ifndef FIFO_CFG_PKG_SV
`define FIFO_CFG_PKG_SV

package fifo_cfg_pkg;
    
    // ==========================================================================
    // FIFO配置参数与类型定义
    // ==========================================================================

    // 复位类型定义
    typedef enum bit [1:0] {
        ASYNC_RST,              // 异步复位
        SYNC_RST,               // 同步复位
        ASYNC_SYNC_RELEASE      // 异步复位 + 同步释放
    } rst_type_e;

    // 复位极性定义
    typedef enum bit {
        ACTIVE_LOW,             // 低电平有效
        ACTIVE_HIGH             // 高电平有效
    } rst_pol_e;

    // 默认配置参数
    parameter int DEFAULT_DEPTH       = 64;
    parameter int DEFAULT_WIDTH       = 16;
    parameter int DEFAULT_FWFT_EN     = 1'b0;
    parameter int DEFAULT_OUT_REG_EN  = 1'b0;
    parameter int DEFAULT_ALMOST_FULL = 4;
    parameter int DEFAULT_ALMOST_EMPTY= 4;
    parameter int DEFAULT_SYNC_STAGES = 2;

endpackage : fifo_cfg_pkg

`endif // FIFO_CFG_PKG_SV
