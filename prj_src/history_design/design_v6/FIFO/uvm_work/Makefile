#==============================================================================
# Makefile with Multi-Config Regression & Functional Coverage Support (Fixed)
#==============================================================================

UVM_HOME    = /home/synopsys/vcs/O-2018.09-SP2/etc/uvm-1.2
VERDI_HOME  = /home/synopsys/verdi/Verdi_O-2018.09-SP2
EL_FILE     = cov_waives.el

# 默认模式定义 (可以在调用 make 时覆盖)
DEPTH       ?= 64
WIDTH       ?= 16
FWFT        ?= 0
OUT_REG     ?= 0

# 拼装编译宏
VCS_DEFINES = +define+CFG_DEPTH=$(DEPTH) \
              +define+CFG_WIDTH=$(WIDTH) \
              +define+CFG_FWFT_EN=$(FWFT) \
              +define+CFG_OUT_REG_EN=$(OUT_REG)

# 编译参数：使用推荐的调试选项，并带上 64位 DVE 修复
VCS_OPTS    = -full64 -sverilog -timescale=1ns/1ps \
              -debug_access+r+w+nomemcbk -debug_region+cell -kdb -lca \
              +incdir+$(UVM_HOME)/src \
              $(UVM_HOME)/src/uvm_pkg.sv \
              $(UVM_HOME)/src/dpi/uvm_dpi.cc \
              -P $(VERDI_HOME)/share/PLI/VCS/LINUXAMD64/novas.tab $(VERDI_HOME)/share/PLI/VCS/LINUXAMD64/pli.a \
              -CFLAGS -DVCS \
              $(VCS_DEFINES) \
              -f ./filelist

# 覆盖率收集参数 (修正：去除 targ)
COV_OPTS    = -cm line+cond+fsm+tgl+branch -cm_dir ./simv.vdb

# 仿真参数
TESTNAME    ?= fifo_random_test
SIM_OPTS    = +UVM_TESTNAME=$(TESTNAME) \
              -l sim_$(TESTNAME)_dp$(DEPTH)_fwft$(FWFT)_reg$(OUT_REG).log \
              -cm line+cond+fsm+tgl+branch -cm_dir ./simv.vdb -cm_name $(TESTNAME)_dp$(DEPTH)_fwft$(FWFT)_reg$(OUT_REG)

.PHONY: compile sim verdi cov html_cov run_all clean

compile:
	vcs $(VCS_OPTS) $(COV_OPTS) -l compile.log

sim:
	./simv $(SIM_OPTS)

# 一键回归测试 (Regression)
run_all:
	@echo "====== 开始多配置回归测试 ======"

	@echo "--- 模式 1: 标准模式 (DEPTH=64, FWFT=0, OUT_REG=0) ---"
	$(MAKE) compile DEPTH=64 FWFT=0 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_random_test DEPTH=64 FWFT=0 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_boundary_test DEPTH=64 FWFT=0 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_full_empty_toggle_test DEPTH=64 FWFT=0 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_stress_test DEPTH=64 FWFT=0 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_delay_behavior_test DEPTH=64 FWFT=0 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_almost_full_empty_test DEPTH=64 FWFT=0 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_reset_cycle_test DEPTH=64 FWFT=0 OUT_REG=0

	@echo "--- 模式 2: 头优先直通模式 (DEPTH=32, FWFT=1, OUT_REG=0) ---"
	$(MAKE) compile DEPTH=32 FWFT=1 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_random_test DEPTH=32 FWFT=1 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_boundary_test DEPTH=32 FWFT=1 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_full_empty_toggle_test DEPTH=32 FWFT=1 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_stress_test DEPTH=32 FWFT=1 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_delay_behavior_test DEPTH=32 FWFT=1 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_almost_full_empty_test DEPTH=32 FWFT=1 OUT_REG=0
	$(MAKE) sim TESTNAME=fifo_reset_cycle_test DEPTH=32 FWFT=1 OUT_REG=0

	@echo "--- 模式 3: 高性能带寄存器FWFT模式 (DEPTH=128, FWFT=1, OUT_REG=1) ---"
	$(MAKE) compile DEPTH=128 FWFT=1 OUT_REG=1
	$(MAKE) sim TESTNAME=fifo_random_test DEPTH=128 FWFT=1 OUT_REG=1
	$(MAKE) sim TESTNAME=fifo_boundary_test DEPTH=128 FWFT=1 OUT_REG=1
	$(MAKE) sim TESTNAME=fifo_full_empty_toggle_test DEPTH=128 FWFT=1 OUT_REG=1
	$(MAKE) sim TESTNAME=fifo_stress_test DEPTH=128 FWFT=1 OUT_REG=1
	$(MAKE) sim TESTNAME=fifo_delay_behavior_test DEPTH=128 FWFT=1 OUT_REG=1
	$(MAKE) sim TESTNAME=fifo_almost_full_empty_test DEPTH=128 FWFT=1 OUT_REG=1
	$(MAKE) sim TESTNAME=fifo_fwft_skid_buffer_test DEPTH=128 FWFT=1 OUT_REG=1
	$(MAKE) sim TESTNAME=fifo_reset_cycle_test DEPTH=128 FWFT=1 OUT_REG=1

	@echo "====== 回归测试已全部完成，覆盖率数据库已自动合并！ ======"

# 使用 DVE 64位图形界面查看覆盖率
cov:
	dve -full64 -covdir ./simv.vdb -elfile $(EL_FILE) &

html_cov:
	urg -dir ./simv.vdb -elfile $(EL_FILE) -format both
	@echo "网页报告生成在: $(shell pwd)/urgReport/dashboard.html"

verdi:
	verdi -dbdir ./simv.daidir -ssf ./tb_top.fsdb &

clean:
	rm -rf csrc simv* ucli.key urgReport compile.log *.log *.fsdb verdiLog novas.*