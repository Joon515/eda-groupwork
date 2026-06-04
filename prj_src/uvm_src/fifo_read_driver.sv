`ifndef FIFO_READ_DRIVER_SV
`define FIFO_READ_DRIVER_SV

class fifo_read_driver #(parameter int WIDTH = 16) extends uvm_driver #(fifo_seq_item #(WIDTH));

    `uvm_component_param_utils(fifo_read_driver #(WIDTH))

    virtual fifo_if vif;

    function new(string name = "fifo_read_driver", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        if (!uvm_config_db#(virtual fifo_if)::get(this, "", "vif", vif)) begin
            `uvm_fatal("NCOVIF", "Could not get virtual interface 'vif' from config_db")
        end
    endfunction : build_phase

    virtual task run_phase(uvm_phase phase);
        vif.r_cb.rinc <= 1'b0;

        @(posedge vif.rclk);
        while (vif.rrst === 1'b0) begin
            @(posedge vif.rclk);
        end

        forever begin
            seq_item_port.get_next_item(req);

            // 1. 处理延迟
            repeat(req.delay) begin
                vif.r_cb.rinc <= 1'b0;
                @(vif.r_cb);
            end

            // 2. 执行读取操作
            if (!req.is_write) begin
                // 即使 FIFO 为空也驱动 rinc，用以测试下溢(Underflow)极值场景下 FIFO 控制信号行为
                vif.r_cb.rinc <= 1'b1;
                `uvm_info("DRV_READ", $sformatf("Driving Read delay=%0d", req.delay), UVM_HIGH)
                @(vif.r_cb);
                
                vif.r_cb.rinc <= 1'b0;
            end else begin
                vif.r_cb.rinc <= 1'b0;
                @(vif.r_cb);
            end

            seq_item_port.item_done();
        end
    endtask : run_phase

endclass : fifo_read_driver

`endif // FIFO_READ_DRIVER_SV