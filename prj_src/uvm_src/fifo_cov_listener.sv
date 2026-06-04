`ifndef FIFO_COV_LISTENER_SV
`define FIFO_COV_LISTENER_SV

class fifo_cov_listener extends uvm_subscriber #(fifo_seq_item #(16));
    `uvm_component_utils(fifo_cov_listener)

    virtual fifo_if vif;

    // ==========================================
    // 1. 写入域功能覆盖组 (在 wclk 采样)
    // ==========================================
    covergroup write_cov_cg @(posedge vif.wclk);
        option.per_instance = 1;
        option.name = "write_cov_cg";

        // 写使能
        cp_winc: coverpoint vif.winc {
            bins active   = {1'b1};
            bins inactive = {1'b0};
        }
        // 满信号状态
        cp_wfull: coverpoint vif.wfull {
            bins full     = {1'b1};
            bins not_full = {1'b0};
        }
        // 将近满信号状态
        cp_walmost_full: coverpoint vif.walmost_full {
            bins almost_full = {1'b1};
            bins normal      = {1'b0};
        }

        // 交叉覆盖率 1: 满状态下的写入企图（Overflow 测试）
        cross_write_at_full: cross cp_winc, cp_wfull {
            bins write_when_full = binsof(cp_winc.active) && binsof(cp_wfull.full);
        }

        // 交叉覆盖率 2: 将近满时的写入（逼近边界测试）
        cross_write_at_almost_full: cross cp_winc, cp_walmost_full {
            bins write_when_af = binsof(cp_winc.active) && binsof(cp_walmost_full.almost_full);
        }
    endgroup

    // ==========================================
    // 2. 读取域功能覆盖组 (在 rclk 采样)
    // ==========================================
    covergroup read_cov_cg @(posedge vif.rclk);
        option.per_instance = 1;
        option.name = "read_cov_cg";

        // 读使能
        cp_rinc: coverpoint vif.rinc {
            bins active   = {1'b1};
            bins inactive = {1'b0};
        }
        // 空信号状态
        cp_rempty: coverpoint vif.rempty {
            bins empty     = {1'b1};
            bins not_empty = {1'b0};
        }
        // 将近空信号状态
        cp_ralmost_empty: coverpoint vif.ralmost_empty {
            bins almost_empty = {1'b1};
            bins normal       = {1'b0};
        }

        // 交叉覆盖率 1: 空状态下的读取企图（Underflow 测试）
        cross_read_at_empty: cross cp_rinc, cp_rempty {
            bins read_when_empty = binsof(cp_rinc.active) && binsof(cp_rempty.empty);
        }

        // 交叉覆盖率 2: 将近空时的读取
        cross_read_at_almost_empty: cross cp_rinc, cp_ralmost_empty {
            bins read_when_ae = binsof(cp_rinc.active) && binsof(cp_ralmost_empty.almost_empty);
        }
    endgroup

    // ==========================================
    // 3. 同时读写覆盖组 (用于测试并发碰撞)
    // ==========================================
    covergroup concurrent_cg @(posedge vif.wclk);
        option.per_instance = 1;
        
        cp_winc_sync: coverpoint vif.winc;
        cp_rinc_sync: coverpoint vif.rinc; 

        cross_concurrent: cross cp_winc_sync, cp_rinc_sync {
            bins simultaneous_rw = binsof(cp_winc_sync) && binsof(cp_rinc_sync);
        }
    endgroup

    // ==========================================
    // 构造函数：在此处先行获取 vif 并安全实例化覆盖组
    // ==========================================
    function new(string name = "fifo_cov_listener", uvm_component parent = null);
        super.new(name, parent);
        
        // 1. 必须使用全局路径检索 vif，此时 parent 节点还未连接完成，使用 null + "*" 检索
        if (!uvm_config_db#(virtual fifo_if)::get(null, "*", "vif", vif)) begin
            `uvm_fatal("NCOVIF_COV", "Could not get virtual interface 'vif' from config_db inside constructor!")
        end

        // 2. 此时 vif 确保安全，在此调用 new() 符合编译规则
        write_cov_cg  = new();
        read_cov_cg   = new();
        concurrent_cg = new();
    endfunction : new

    // 已经移入构造函数，此处的 build_phase 可以保留或删去，推荐仅写 super
    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
    endfunction : build_phase

    virtual function void write(fifo_seq_item #(16) t);
        // 空函数留空
    endfunction : write

endclass : fifo_cov_listener

`endif // FIFO_COV_LISTENER_SV