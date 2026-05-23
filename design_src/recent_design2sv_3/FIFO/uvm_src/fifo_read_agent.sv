`ifndef FIFO_READ_AGENT_SV
`define FIFO_READ_AGENT_SV

class fifo_read_agent #(
    parameter int WIDTH      = 16,
    parameter bit FWFT_EN    = 1'b0,
    parameter bit OUT_REG_EN = 1'b0
) extends uvm_agent;

    `uvm_component_param_utils(fifo_read_agent #(WIDTH, FWFT_EN, OUT_REG_EN))

    uvm_sequencer #(fifo_seq_item #(WIDTH)) sqr;
    fifo_read_driver #(WIDTH)               drv;
    fifo_read_monitor #(WIDTH, FWFT_EN, OUT_REG_EN) mon;

    uvm_analysis_port #(fifo_seq_item #(WIDTH)) ap;

    function new(string name = "fifo_read_agent", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        
        ap = new("ap", this);
        mon = fifo_read_monitor#(WIDTH, FWFT_EN, OUT_REG_EN)::type_id::create("mon", this);
        
        if (get_is_active() == UVM_ACTIVE) begin
            sqr = uvm_sequencer#(fifo_seq_item#(WIDTH))::type_id::create("sqr", this);
            drv = fifo_read_driver#(WIDTH)::type_id::create("drv", this);
        end
    endfunction : build_phase

    virtual function void connect_phase(uvm_phase phase);
        super.connect_phase(phase);
        
        mon.ap.connect(this.ap);

        if (get_is_active() == UVM_ACTIVE) begin
            drv.seq_item_port.connect(sqr.seq_item_export);
        end
    endfunction : connect_phase

endclass : fifo_read_agent

`endif // FIFO_READ_AGENT_SV