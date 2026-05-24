`ifndef FIFO_WRITE_MONITOR_SV
`define FIFO_WRITE_MONITOR_SV

class fifo_write_monitor #(parameter int WIDTH = 16) extends uvm_monitor;

    `uvm_component_param_utils(fifo_write_monitor #(WIDTH))

    virtual fifo_if vif;
    
    // 广播采样数据的分析端口
    uvm_analysis_port #(fifo_seq_item #(WIDTH)) ap;

    function new(string name = "fifo_write_monitor", uvm_component parent = null);
        super.new(name, parent);
        ap = new("ap", this);
    endfunction : new

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        if (!uvm_config_db#(virtual fifo_if)::get(this, "", "vif", vif)) begin
            `uvm_fatal("NCOVIF", "Could not get virtual interface 'vif' from config_db")
        end
    endfunction : build_phase

    virtual task run_phase(uvm_phase phase);
        fifo_seq_item #(WIDTH) item;

        // 等待复位释放
        @(posedge vif.wclk);
        while (vif.wrst === 1'b0) begin
            @(posedge vif.wclk);
        end

        forever begin
            @(vif.w_cb);
            // 只有当 winc=1 且未满时，写入才算成功进入 FIFO
            if (vif.w_cb.winc === 1'b1 && vif.w_cb.wfull === 1'b0) begin
                item = fifo_seq_item#(WIDTH)::type_id::create("item");
                item.data     = vif.w_cb.wdata;
                item.is_write = 1'b1;
                item.delay    = 0; // Monitor不关心延迟，填0
                
                `uvm_info("MON_WRITE", $sformatf("Monitored Write Data: 16'h%4h", item.data), UVM_HIGH)
                ap.write(item);
            end
        end
    endtask : run_phase

endclass : fifo_write_monitor

`endif // FIFO_WRITE_MONITOR_SV