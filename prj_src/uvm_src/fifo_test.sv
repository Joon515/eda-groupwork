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


// =============================================================================
// 4. 测试用例三：满信号/空信号切换测试 (fifo_full_empty_toggle_test)
// 验证满信号拉高→写入停止→读出数据→满信号下降
//      空信号拉高→读取停止→写入数据→空信号下降
// =============================================================================
class fifo_full_empty_toggle_test extends fifo_base_test;
    `uvm_component_utils(fifo_full_empty_toggle_test)

    function new(string name = "fifo_full_empty_toggle_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_full_empty_toggle_vseq #(16, 64) toggle_vseq;

        phase.raise_objection(this);
        `uvm_info("TEST_START", "Executing fifo_full_empty_toggle_test...", UVM_LOW)

        toggle_vseq = fifo_full_empty_toggle_vseq#(16, 64)::type_id::create("toggle_vseq");
        toggle_vseq.w_sqr = env.w_agent.sqr;
        toggle_vseq.r_sqr = env.r_agent.sqr;
        toggle_vseq.start(null);

        #500ns;
        `uvm_info("TEST_END", "Finished fifo_full_empty_toggle_test execution.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_full_empty_toggle_test


// =============================================================================
// 5. 测试用例四：压力测试 (fifo_stress_test)
// 持续进行频繁的读写操作，测试 FIFO 在极限条件下的稳定性和数据完整性
// =============================================================================
class fifo_stress_test extends fifo_base_test;
    `uvm_component_utils(fifo_stress_test)

    function new(string name = "fifo_stress_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_stress_test_vseq #(16) stress_vseq;

        phase.raise_objection(this);
        `uvm_info("TEST_START", "Executing fifo_stress_test...", UVM_LOW)

        stress_vseq = fifo_stress_test_vseq#(16)::type_id::create("stress_vseq");
        stress_vseq.w_sqr = env.w_agent.sqr;
        stress_vseq.r_sqr = env.r_agent.sqr;
        stress_vseq.start(null);

        #1us;  // 压力测试需要较长的仿真时间
        `uvm_info("TEST_END", "Finished fifo_stress_test execution.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_stress_test


// =============================================================================
// 6. 测试用例五：延迟行为测试 (fifo_delay_behavior_test)
// 测试不同延迟配置下的 FIFO 行为：零延迟、固定延迟、随机延迟
// =============================================================================
class fifo_delay_behavior_test extends fifo_base_test;
    `uvm_component_utils(fifo_delay_behavior_test)

    function new(string name = "fifo_delay_behavior_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_delay_behavior_vseq #(16, 64) delay_vseq;

        phase.raise_objection(this);
        `uvm_info("TEST_START", "Executing fifo_delay_behavior_test...", UVM_LOW)

        delay_vseq = fifo_delay_behavior_vseq#(16, 64)::type_id::create("delay_vseq");
        delay_vseq.w_sqr = env.w_agent.sqr;
        delay_vseq.r_sqr = env.r_agent.sqr;
        delay_vseq.start(null);

        #500ns;
        `uvm_info("TEST_END", "Finished fifo_delay_behavior_test execution.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_delay_behavior_test


// =============================================================================
// 7. 测试用例六：将近满/近空信号对齐测试 (fifo_almost_full_empty_test)
// 验证 almost_full/almost_empty 信号与实际 FIFO 占用情况的对齐关系
// =============================================================================
class fifo_almost_full_empty_test extends fifo_base_test;
    `uvm_component_utils(fifo_almost_full_empty_test)

    function new(string name = "fifo_almost_full_empty_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_almost_full_empty_vseq #(16, 64, 4, 4) almost_vseq;

        phase.raise_objection(this);
        `uvm_info("TEST_START", "Executing fifo_almost_full_empty_test...", UVM_LOW)

        almost_vseq = fifo_almost_full_empty_vseq#(16, 64, 4, 4)::type_id::create("almost_vseq");
        almost_vseq.w_sqr = env.w_agent.sqr;
        almost_vseq.r_sqr = env.r_agent.sqr;
        almost_vseq.start(null);

        #500ns;
        `uvm_info("TEST_END", "Finished fifo_almost_full_empty_test execution.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_almost_full_empty_test


// =============================================================================
// 8. 测试用例七：Skid Buffer 覆盖测试 (FWFT+OUT_REG 模式)
// 专门为 FWFT+OUT_REG 配置优化，确保条件表达式100%覆盖
// 需要在 FWFT_EN=1, OUT_REG_EN=1 配置下运行
// =============================================================================
class fifo_fwft_skid_buffer_test extends fifo_base_test;
    `uvm_component_utils(fifo_fwft_skid_buffer_test)

    function new(string name = "fifo_fwft_skid_buffer_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_skid_buffer_coverage_vseq #(16, 32) skid_vseq;

        phase.raise_objection(this);
        `uvm_info("TEST_START", "Executing fifo_fwft_skid_buffer_test (Skid Buffer Coverage)...", UVM_LOW)

        skid_vseq = fifo_skid_buffer_coverage_vseq#(16, 32)::type_id::create("skid_vseq");
        skid_vseq.w_sqr = env.w_agent.sqr;
        skid_vseq.r_sqr = env.r_agent.sqr;
        skid_vseq.start(null);

        #500ns;
        `uvm_info("TEST_END", "Finished fifo_fwft_skid_buffer_test execution.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_fwft_skid_buffer_test


// =============================================================================
// 9. 测试用例八：复位周期测试 (Reset Cycle Test)
// 测试多个复位周期，确保 wrst/rrst 的 1→0 翻转被覆盖
// 可在任何配置下运行，特别推荐在基础配置 (DEPTH=64, FWFT=0, OUT_REG=0) 下运行
// =============================================================================
class fifo_reset_cycle_test extends fifo_base_test;
    `uvm_component_utils(fifo_reset_cycle_test)

    function new(string name = "fifo_reset_cycle_test", uvm_component parent = null);
        super.new(name, parent);
    endfunction : new

    virtual task run_phase(uvm_phase phase);
        fifo_reset_cycle_vseq #(16) reset_vseq;

        phase.raise_objection(this);
        `uvm_info("TEST_START", "Executing fifo_reset_cycle_test (Reset Toggle Transitions)...", UVM_LOW)

        reset_vseq = fifo_reset_cycle_vseq#(16)::type_id::create("reset_vseq");
        reset_vseq.w_sqr = env.w_agent.sqr;
        reset_vseq.r_sqr = env.r_agent.sqr;
        reset_vseq.start(null);

        #500ns;
        `uvm_info("TEST_END", "Finished fifo_reset_cycle_test execution.", UVM_LOW)
        phase.drop_objection(this);
    endtask : run_phase

endclass : fifo_reset_cycle_test

`endif // FIFO_TEST_SV
