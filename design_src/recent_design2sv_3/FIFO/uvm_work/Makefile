#==============================================================================
# Makefile for Async FIFO UVM Testbench
#==============================================================================

# 路径定义
UVM_HOME    = /home/synopsys/vcs/O-2018.09-SP2/etc/uvm-1.2
VERDI_HOME  = /home/synopsys/verdi/Verdi_O-2018.09-SP2

# 编译参数
VCS_OPTS    = -full64 -sverilog -timescale=1ns/1ps \
              +acc +vpi -debug_access+all -kdb -lca \
              +incdir+$(UVM_HOME)/src \
              $(UVM_HOME)/src/uvm_pkg.sv \
              $(UVM_HOME)/src/dpi/uvm_dpi.cc \
              -P $(VERDI_HOME)/share/PLI/VCS/LINUXAMD64/novas.tab $(VERDI_HOME)/share/PLI/VCS/LINUXAMD64/pli.a \
              -CFLAGS -DVCS \
              -f ./filelist

# 覆盖率参数
COV_OPTS    = -cm line+cond+fsm+tgl+branch -cm_dir ./simv.vdb

# 仿真运行参数
SIM_OPTS    = +UVM_TESTNAME=$(TESTNAME) \
              -l sim_$(TESTNAME).log \
              -cm line+cond+fsm+tgl+branch -cm_dir ./simv.vdb -cm_name $(TESTNAME)

# 默认测试用例
TESTNAME    = fifo_random_test

.PHONY: compile sim verdi cov clean Help

Help:
	@echo "================================================================="
	@echo " 使用说明:"
	@echo " make compile             : 编译工程"
	@echo " make sim TESTNAME=xxx    : 运行指定的测试用例 (默认: fifo_random_test)"
	@echo " make verdi               : 启动 Verdi 查看波形"
	@echo " make cov                 : 使用 DVE/Verdi 查看覆盖率"
	@echo " make clean               : 清理所有编译生成文件"
	@echo "================================================================="

compile:
	vcs $(VCS_OPTS) $(COV_OPTS) -l compile.log

sim:
	./simv $(SIM_OPTS)

verdi:
	verdi -dbdir ./simv.daidir -ssf ./tb_top.fsdb &

cov:
	dve -covdir ./simv.vdb &

clean:
	rm -rf csrc simv simv.daidir simv.vdb ucli.key
	rm -rf compile.log sim_*.log *.fsdb verdiLog novas.*