`ifndef FIFO_READ_MONITOR_SV
`define FIFO_READ_MONITOR_SV

class fifo_read_monitor #(
    parameter int WIDTH      = 16,
    parameter bit FWFT_EN    = 1'b0,
    parameter bit OUT_REG_EN = 1'b0
) extends uvm_monitor;

    `uvm_component_param_utils(fifo_read_monitor #(WIDTH, FWFT_EN, OUT_REG_EN))

    virtual fifo_if vif;
    uvm_analysis_port #(fifo_seq_item #(WIDTH)) ap;

    function new(string name = "fifo_read_monitor", uvm_component parent = null);
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
        @(posedge vif.rclk);
        while (vif.rrst === 1'b0) begin
            @(posedge vif.rclk);
        end

        forever begin
            // 使用监视专用时钟块 r_mon_cb 采样
            @(vif.r_mon_cb);
            if (vif.r_mon_cb.rinc === 1'b1 && vif.r_mon_cb.rempty === 1'b0) begin
                
                fork
                    automatic logic [WIDTH-1:0] sampled_data;
                    begin
                        if (FWFT_EN) begin
                            sampled_data = vif.r_mon_cb.rdata;
                        end else if (!FWFT_EN && !OUT_REG_EN) begin
                            @(vif.r_mon_cb);
                            sampled_data = vif.r_mon_cb.rdata;
                        end else begin
                            @(vif.r_mon_cb);
                            @(vif.r_mon_cb);
                            sampled_data = vif.r_mon_cb.rdata;
                        end

                        item = fifo_seq_item#(WIDTH)::type_id::create("item");
                        item.data     = sampled_data;
                        item.is_write = 1'b0;
                        item.delay    = 0;
                        
                        `uvm_info("MON_READ", $sformatf("Monitored Read Data: 16'h%4h (FWFT=%0b, OUT_REG=%0b)", 
                                  item.data, FWFT_EN, OUT_REG_EN), UVM_HIGH)
                        ap.write(item);
                    end
                join_none
            end
        end
    endtask : run_phase

endclass : fifo_read_monitor

`endif // FIFO_READ_MONITOR_SV