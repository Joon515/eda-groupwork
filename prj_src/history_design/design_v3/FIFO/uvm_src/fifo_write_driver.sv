`ifndef FIFO_WRITE_DRIVER_SV
`define FIFO_WRITE_DRIVER_SV

class fifo_write_driver #(parameter int WIDTH = 16) extends uvm_driver #(fifo_seq_item #(WIDTH));

    `uvm_component_param_utils(fifo_write_driver #(WIDTH))

    // 虚拟接口，用于驱动硬件
    virtual fifo_if vif;

    function new(string name = "fifo_write_driver", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        if (!uvm_config_db#(virtual fifo_if)::get(this, "", "vif", vif)) begin
            `uvm_fatal("NCOVIF", "Could not get virtual interface 'vif' from config_db")
        end
    endfunction : build_phase

    virtual task run_phase(uvm_phase phase);
        // 初始化复位状态下的物理信号
        vif.w_cb.winc  <= 1'b0;
        vif.w_cb.wdata <= '0;

        // 等待复位释放后再开始驱动
        // 接口中 w_cb.wrst 对应当前的复位状态
        @(posedge vif.wclk);
        while (vif.wrst === 1'b0) begin
            @(posedge vif.wclk);
        end

        forever begin
            seq_item_port.get_next_item(req);
            
            // 1. 处理延迟周期
            repeat(req.delay) begin
                vif.w_cb.winc  <= 1'b0;
                @(vif.w_cb);
            end

            // 2. 执行写入操作
            if (req.is_write) begin
                // 如果 FIFO 满了，这里仍然执行驱动以测试溢出(Overflow)场景下控制信号的反应
                vif.w_cb.winc  <= 1'b1;
                vif.w_cb.wdata <= req.data;
                `uvm_info("DRV_WRITE", $sformatf("Driving Write: %s", req.convert2string()), UVM_HIGH)
                @(vif.w_cb);
                
                // 恢复写入使能，防止持续写入
                vif.w_cb.winc  <= 1'b0;
            end else begin
                // 如果抓到了非写 transaction，直接空跑一拍
                vif.w_cb.winc  <= 1'b0;
                @(vif.w_cb);
            end

            seq_item_port.item_done();
        end
    endtask : run_phase

endclass : fifo_write_driver

`endif // FIFO_WRITE_DRIVER_SV