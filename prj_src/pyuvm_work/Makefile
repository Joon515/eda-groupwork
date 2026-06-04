SIM ?= verilator
TOPLEVEL_LANG ?= verilog
TOPLEVEL ?= async_fifo_top
MODULE ?= test_async_fifo
TESTCASE ?= FifoSmokeTest
WAVES ?= 1

.DEFAULT_GOAL := run

DEPTH ?= 16
WIDTH ?= 16
FWFT_EN ?= 0
OUT_REG_EN ?= 0
SYNC_STAGES ?= 2
ALMOST_FULL_EN ?= 0
ALMOST_FULL_VAL ?= 4
ALMOST_EMPTY_EN ?= 0
ALMOST_EMPTY_VAL ?= 4

PYTHON_VERSION_TAG := $(shell python -c 'import sys; print("py" + str(sys.version_info.major) + str(sys.version_info.minor))')
COCOTB_VERSION_TAG := $(shell python -c 'import cocotb; print(cocotb.__version__)' | tr . _)
PYTHON_ENV_TAG := $(PYTHON_VERSION_TAG)-cocotb$(COCOTB_VERSION_TAG)
PARAM_SIM_BUILD = sim_build/$(SIM)-$(PYTHON_ENV_TAG)-d$(DEPTH)-w$(WIDTH)-fw$(FWFT_EN)-out$(OUT_REG_EN)-sync$(SYNC_STAGES)-af$(ALMOST_FULL_EN)-afv$(ALMOST_FULL_VAL)-ae$(ALMOST_EMPTY_EN)-aev$(ALMOST_EMPTY_VAL)
SIM_BUILD ?= $(PARAM_SIM_BUILD)

export DEPTH WIDTH FWFT_EN OUT_REG_EN SYNC_STAGES ALMOST_FULL_EN ALMOST_FULL_VAL ALMOST_EMPTY_EN ALMOST_EMPTY_VAL

VERILOG_SOURCES = \
	../rtl_src/fifo_cfg_pkg.sv \
	../rtl_src/sync_gray.sv \
	../rtl_src/dual_port_ram.sv \
	../rtl_src/wptr.sv \
	../rtl_src/rptr.sv \
	../rtl_src/async_fifo_top.sv

COCOTB_TEST_MODULES ?= $(MODULE)
COCOTB_RESULTS_FILE ?= results.xml
TEST_RESULTS_FILE = results-$(TESTCASE).xml
SIM_CMD_PREFIX ?= env -u PYTHONHOME

EXTRA_ARGS += --timing --trace
COMPILE_ARGS += -Wno-WIDTHEXPAND
EXTRA_ARGS += -GDEPTH=$(DEPTH)
EXTRA_ARGS += -GWIDTH=$(WIDTH)
EXTRA_ARGS += -GFWFT_EN=$(FWFT_EN)
EXTRA_ARGS += -GOUT_REG_EN=$(OUT_REG_EN)
EXTRA_ARGS += -GSYNC_STAGES=$(SYNC_STAGES)
EXTRA_ARGS += -GALMOST_FULL_EN=$(ALMOST_FULL_EN)
EXTRA_ARGS += -GALMOST_FULL_VAL=$(ALMOST_FULL_VAL)
EXTRA_ARGS += -GALMOST_EMPTY_EN=$(ALMOST_EMPTY_EN)
EXTRA_ARGS += -GALMOST_EMPTY_VAL=$(ALMOST_EMPTY_VAL)
CUSTOM_COMPILE_DEPS += Makefile

.PHONY: run regression regression-basic regression-core regression-boundary regression-advanced clean

BASIC_TESTS := FifoSmokeTest FifoResetTest FifoSingleWriteReadTest FifoDelayBehaviorTest
SCOREBOARD_TESTS := FifoOrderPreservationTest FifoMultiItemDrainTest
BOUNDARY_TESTS := FifoFullEmptyBoundaryTest FifoEmptyReadProtectionTest FifoAlmostFlagsTest
ADVANCED_TESTS := FifoAsyncSimultaneousReadWriteTest FifoRandomRegressionTest FifoStressTest
CORE_TESTS := $(BASIC_TESTS) $(SCOREBOARD_TESTS)

##run:
##	$(MAKE) sim MODULE= TESTCASE= SIM_BUILD="$(PARAM_SIM_BUILD)" COCOTB_TEST_MODULES="$(MODULE)" COCOTB_TEST_FILTER="$(TESTCASE)$$" COCOTB_RESULTS_FILE="$(TEST_RESULTS_FILE)"

run:
	$(MAKE) sim \
		MODULE= \
		TESTCASE= \
		SIM_BUILD="$(PARAM_SIM_BUILD)" \
		COCOTB_TEST_MODULES="$(MODULE)" \
		COCOTB_TEST_FILTER="$(TESTCASE)$$" \
		COCOTB_RESULTS_FILE="$(TEST_RESULTS_FILE)"

regression:
	$(MAKE) run TESTCASE=FifoSmokeTest
	$(MAKE) regression-basic
	$(MAKE) regression-core
	$(MAKE) regression-boundary
	$(MAKE) regression-advanced

regression-basic:
	@for testcase in $(BASIC_TESTS); do \
		$(MAKE) run TESTCASE=$$testcase || exit $$?; \
	done

regression-core:
	@for testcase in $(CORE_TESTS); do \
		$(MAKE) run TESTCASE=$$testcase || exit $$?; \
	done

regression-boundary:
	$(MAKE) run TESTCASE=FifoFullEmptyBoundaryTest DEPTH=8
	$(MAKE) run TESTCASE=FifoEmptyReadProtectionTest
	$(MAKE) run TESTCASE=FifoAlmostFlagsTest DEPTH=8 ALMOST_FULL_EN=1 ALMOST_FULL_VAL=2 ALMOST_EMPTY_EN=1 ALMOST_EMPTY_VAL=2

regression-advanced:
	@for testcase in $(ADVANCED_TESTS); do \
		$(MAKE) run TESTCASE=$$testcase || exit $$?; \
	done
	$(MAKE) run TESTCASE=FifoFwftDirectTest FWFT_EN=1 OUT_REG_EN=0
	$(MAKE) run TESTCASE=FifoOutRegLatencyTest FWFT_EN=0 OUT_REG_EN=1

clean::
	rm -rf sim_build results.xml results-*.xml *.vcd *.fst __pycache__ .pytest_cache

include $(shell cocotb-config --makefiles)/Makefile.sim
