`ifndef FIFO_ENV_PKG_SV
`define FIFO_ENV_PKG_SV

package fifo_env_pkg;

    import uvm_pkg::*;
    import fifo_cfg_pkg::*;

    `include "../uvm_src/uvm_macros.svh"

    // 1. 数据事务
    `include "../uvm_src/fifo_seq_item.sv"

    // 2. 写入时钟域组件
    `include "../uvm_src/fifo_write_driver.sv"
    `include "../uvm_src/fifo_write_monitor.sv"
    `include "../uvm_src/fifo_write_agent.sv"

    // 3. 读取时钟域组件
    `include "../uvm_src/fifo_read_monitor.sv"
    `include "../uvm_src/fifo_read_driver.sv"
    `include "../uvm_src/fifo_read_agent.sv"

    // 4. 环境分析器与系统看板
    `include "../uvm_src/fifo_scoreboard.sv"
    `include "../uvm_src/fifo_env.sv"

    // 5. 驱动场景序列
    `include "../uvm_src/fifo_sequence.sv"

    // 6. 测试用例定义
    `include "../uvm_src/fifo_test.sv"

endpackage : fifo_env_pkg

`endif // FIFO_ENV_PKG_SV