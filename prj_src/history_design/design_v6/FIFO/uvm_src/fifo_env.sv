`ifndef FIFO_ENV_SV
`define FIFO_ENV_SV

class fifo_env #(
    parameter int WIDTH            = 16,
    parameter int DEPTH            = 64,
    parameter bit FWFT_EN          = 1'b0,
    parameter bit OUT_REG_EN       = 1'b0,
    parameter int ALMOST_FULL_VAL  = 4,
    parameter int ALMOST_EMPTY_VAL = 4
) extends uvm_env;

    `uvm_component_param_utils(fifo_env #(WIDTH, DEPTH, FWFT_EN, OUT_REG_EN, ALMOST_FULL_VAL, ALMOST_EMPTY_VAL))

    // 实例化写入侧和读取侧 Agent
    fifo_write_agent #(WIDTH)                                                   w_agent;
    fifo_read_agent  #(WIDTH, FWFT_EN, OUT_REG_EN)                              r_agent;
    
    // 实例化 Scoreboard
    fifo_scoreboard  #(WIDTH, DEPTH, ALMOST_FULL_VAL, ALMOST_EMPTY_VAL)          scb;

    // 覆盖率收集器
    fifo_cov_listener                                                  cov_listener;
    function new(string name = "fifo_env", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);

        w_agent = fifo_write_agent#(WIDTH)::type_id::create("w_agent", this);
        r_agent = fifo_read_agent#(WIDTH, FWFT_EN, OUT_REG_EN)::type_id::create("r_agent", this);
        
        scb = fifo_scoreboard#(WIDTH, DEPTH, ALMOST_FULL_VAL, ALMOST_EMPTY_VAL)::type_id::create("scb", this);
        // 创建覆盖率监听器
        cov_listener = fifo_cov_listener::type_id::create("cov_listener", this);
    endfunction : build_phase

    virtual function void connect_phase(uvm_phase phase);
        super.connect_phase(phase);

        // 将 Write Monitor 和 Read Monitor 的 TLM 广播端口分别与 Scoreboard 对应的导入端口相连
        w_agent.ap.connect(scb.write_imp);
        r_agent.ap.connect(scb.read_imp);
        // 将写 Agent 的数据流引入覆盖率模块进行辅助分析（主要通过 VIF 采样，此处连接保留作为标准流）
        w_agent.ap.connect(cov_listener.analysis_export);
    endfunction : connect_phase

endclass : fifo_env

`endif // FIFO_ENV_SV