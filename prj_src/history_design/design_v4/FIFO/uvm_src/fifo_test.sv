`ifndef FIFO_TEST_SV
`define FIFO_TEST_SV

// =============================================================================
// 1. 基础测试用例 (Base Test)
// =============================================================================
class fifo_base_test extends uvm_test;
    `uvm_component_utils(fifo_base_test)

    // 环境参数与 tb_top 的宏定义进行联动
    fifo_env #(
        .WIDTH(`CFG_WIDTH),
        .DEPTH(`CFG_DEPTH),
        .FWFT_EN(`CFG_FWFT_EN),
        .OUT_REG_EN(`CFG_OUT_REG_EN),
        .ALMOST_FULL_VAL(4),
        .ALMOST_EMPTY_VAL(4)
    ) env;

    virtual fifo_if vif;

    function new(string name = "fifo_base_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        
        // 例化时采用相同的宏定义
        env = fifo_env#(`CFG_WIDTH, `CFG_DEPTH, `CFG_FWFT_EN, `CFG_OUT_REG_EN, 4, 4)::type_id::create("env", this);

        if (!uvm_config_db#(virtual fifo_if)::get(this, "", "vif", vif)) begin
            `uvm_fatal("NCOVIF", "Could not get virtual interface 'vif' from config_db")
        end
    endfunction : build_phase

    // 调节仿真超时机制 (超时安全保护)
    virtual function void start_of_simulation_phase(uvm_phase phase);
        super.start_of_simulation_phase(phase);
        uvm_top.set_timeout(10ms); // 设置仿真最长执行 10ms，防止死锁挂起
    endfunction : start_of_simulation_phase

    virtual function void report_phase(uvm_phase phase);
        super.report_phase(phase);
        // 此处可用于获取全局测试状态
    endfunction : report_phase

endclass : fifo_base_test


// =============================================================================
// 2. 测试用例一：2000组随机并发读写混合测试 (fifo_random_test)
// =============================================================================
class fifo_random_test extends fifo_base_test;
    `uvm_component_utils(fifo_random_test)

    function new(string name = "fifo_random_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_random_mixed_vseq #(16) vseq;
        
        phase.raise_objection(this);
        `uvm_info("TEST_START", "Executing fifo_random_test...", UVM_LOW)

        // 实例化虚拟序列并挂载物理 Sequencer 句柄
        vseq = fifo_random_mixed_vseq#(16)::type_id::create("vseq");
        vseq.w_sqr = env.w_agent.sqr;
        vseq.r_sqr = env.r_agent.sqr;

        // 启动虚拟序列
        vseq.start(null);

        `uvm_info("TEST_END", "Finished fifo_random_test execution.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_random_test


// =============================================================================
// 3. 测试用例二：极限控制与溢出/下溢边界测试 (fifo_boundary_test)
// =============================================================================
class fifo_boundary_test extends fifo_base_test;
    `uvm_component_utils(fifo_boundary_test)

    function new(string name = "fifo_boundary_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_full_empty_vseq       #(16, 64) full_empty_vseq;
        fifo_extreme_boundary_vseq #(16, 64) boundary_vseq;

        phase.raise_objection(this);
        `uvm_info("TEST_START", "Executing fifo_boundary_test...", UVM_LOW)

        // ---------------------------------------------------------------------
        // 步骤 1: 执行随机数据写满再读空测试 (校验控制信号拉高/释放及时性)
        // ---------------------------------------------------------------------
        `uvm_info("TEST_STAGE1", "Running Full-to-Empty sequence...", UVM_LOW)
        full_empty_vseq = fifo_full_empty_vseq#(16, 64)::type_id::create("full_empty_vseq");
        full_empty_vseq.w_sqr = env.w_agent.sqr;
        full_empty_vseq.r_sqr = env.r_agent.sqr;
        full_empty_vseq.start(null);

        #500ns; // 时钟同步空隙稳定期

        // ---------------------------------------------------------------------
        // 步骤 2: 执行溢出与下溢极限操作测试 (校验满后写入、空后读取时的鲁棒性)
        // ---------------------------------------------------------------------
        `uvm_info("TEST_STAGE2", "Running Extreme Boundary Overflow/Underflow sequence...", UVM_LOW)
        boundary_vseq = fifo_extreme_boundary_vseq#(16, 64)::type_id::create("boundary_vseq");
        boundary_vseq.w_sqr = env.w_agent.sqr;
        boundary_vseq.r_sqr = env.r_agent.sqr;
        boundary_vseq.start(null);

        `uvm_info("TEST_END", "Finished fifo_boundary_test execution.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_boundary_test

`endif // FIFO_TEST_SV
