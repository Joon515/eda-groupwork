`ifndef FIFO_WRITE_AGENT_SV
`define FIFO_WRITE_AGENT_SV

class fifo_write_agent #(parameter int WIDTH = 16) extends uvm_agent;

    `uvm_component_param_utils(fifo_write_agent #(WIDTH))

    uvm_sequencer #(fifo_seq_item #(WIDTH)) sqr;
    fifo_write_driver #(WIDTH)              drv;
    fifo_write_monitor #(WIDTH)             mon;

    uvm_analysis_port #(fifo_seq_item #(WIDTH)) ap;

    function new(string name = "fifo_write_agent", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        
        ap = new("ap", this);
        mon = fifo_write_monitor#(WIDTH)::type_id::create("mon", this);
        
        if (get_is_active() == UVM_ACTIVE) begin
            sqr = uvm_sequencer#(fifo_seq_item#(WIDTH))::type_id::create("sqr", this);
            drv = fifo_write_driver#(WIDTH)::type_id::create("drv", this);
        end
    endfunction : build_phase

    virtual function void connect_phase(uvm_phase phase);
        super.connect_phase(phase);
        
        // 外部连接 Monitor 的分析端口
        mon.ap.connect(this.ap);

        if (get_is_active() == UVM_ACTIVE) begin
            drv.seq_item_port.connect(sqr.seq_item_export);
        end
    endfunction : connect_phase

endclass : fifo_write_agent

`endif // FIFO_WRITE_AGENT_SV