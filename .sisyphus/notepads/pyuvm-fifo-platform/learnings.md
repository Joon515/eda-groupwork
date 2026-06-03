# Learnings: pyuvm-fifo-platform

## 2026-06-02 Start Work
- Plan path: `.sisyphus/plans/pyuvm-fifo-platform.md`.
- User decisions: OSS CAD Suite/Verilator, no commercial simulator, Python `assert` only, Chinese learning documentation.
- RTL compile order must be package first: `fifo_cfg_pkg.sv`, `sync_gray.sv`, `dual_port_ram.sv`, `wptr.sv`, `rptr.sv`, `async_fifo_top.sv`.
- cocotb flow must omit `uvm_src/fifo_if.sv`, `uvm_src/tb_top.sv`, and all SV UVM files.
- Task 1 manifest verified with `conda env create -f prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml`; env name `eda-pyuvm-fifo` resolved correctly.
- `cocotb==2.0.1` and `pyuvm==4.0.1` installed via pip section; `python -c 'import sys; assert not sys.flags.optimize; import cocotb, pyuvm'` succeeded inside the env.
- `verilator --version` is available from the shell PATH, confirming it is supplied outside conda.

## 2026-06-02 Task 2 Prep
- Local repo has no pre-existing Python, pyuvm, cocotb, or dependency manifest files outside the newly added `environment.yml`.
- `.gitignore` was empty before implementation; pyuvm/cocotb generated artifacts will need explicit ignore rules in Task 8.
- Existing docs/Makefile commands are VCS-centric (`make compile`, `make sim TESTNAME=...`, `make run_all`, `make verdi`, `make html_cov`); new `pyuvm_work/Makefile` should be independent.
- RTL/cocotb top must be `async_fifo_top`; package compile order is mandatory because every RTL module imports `fifo_cfg_pkg`.
- Default reset is ACTIVE_LOW: asserted `wrst=0, rrst=0`, normal `wrst=1, rrst=1`.
- Read latency expectations: standard=1 read clock, OUT_REG=2 read clocks, FWFT direct=visible without extra read latency, FWFT+skid is variable/buffered.
- `dual_port_ram` has async combinational read and no memory reset/init; cocotb tests must not compare `rdata` before a valid write/read path.
- Stabilization guidance from docs: wait roughly 2-3 sync clocks for pointer synchronization, 100ns for boundary sync waits, 200ns after reset release, 500ns for stress stability.
- Strong external async FIFO pyuvm/cocotb references found: `VLSI-Shubh/Asynchronous-FIFO`, `npatsiatzis/fifo_asynchronous`, pyuvm TinyALU scoreboard, `dpretet/async_fifo` FALLTHROUGH, `alexforencich/verilog-axis` async FIFO tests.
- pyuvm 4.0.1 `@pyuvm.test()` wraps cocotb tests and sets the cocotb test name to the class name on cocotb >= 2.0, so selecting `FifoSmokeTest` by class name is valid.
- pyuvm components/BFMs usually access the DUT through `cocotb.top` rather than a direct DUT argument.
- cocotb 2.0 preferred Makefile variable is `COCOTB_TEST_MODULES`; legacy `MODULE` still appears in older examples. For this plan, keep `MODULE ?= test_async_fifo` for compatibility but map it to `COCOTB_TEST_MODULES=$(MODULE)`.
- cocotb 2.0 prefers `COCOTB_TEST_FILTER`; `COCOTB_TESTCASE` is deprecated and exact-matched. For this plan, keep `TESTCASE ?= FifoSmokeTest` but map it internally to `COCOTB_TEST_FILTER=$(TESTCASE)$$` for class-name selection.
- Verilator generic/parameter override can be passed as explicit `-GNAME=$(VALUE)` in `EXTRA_ARGS`; cocotb runner also maps Python `parameters={}` to `-G`, but the plan uses Makefile flow.
- pyuvm.test() on cocotb 2.0+ sets the test name to the pyuvm class name, so TESTCASE/COCOTB_TESTCASE can select the class directly.
- pyuvm examples use cocotb.top for DUT access inside BFMs/components; no dut argument plumbing is needed in pyuvm tests.
- cocotb 2.0 prefers COCOTB_TEST_MODULES, COCOTB_TEST_FILTER, and COCOTB_RESULTS_FILE; TESTCASE is deprecated but still maps to exact-name regexes.
- For Verilator in cocotb runner API, parameters are emitted as -Gname=value.
- COCOTB_REDUCED_LOG_FMT defaults to true; COCOTB_LOG_PREFIX overrides formatting and disables the reduced format.
- Task 2 implementation in `pyuvm_work/Makefile` works with the exact command `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoSmokeTest` by using a wrapper `run` target that clears legacy `TESTCASE`/`MODULE` before invoking cocotb's `sim` target with `COCOTB_TEST_FILTER` and `COCOTB_TEST_MODULES`.
- cocotb's included makefiles define `clean::`; local cleanup extensions in this workspace must also use double-colon rules to avoid `target file 'clean' has both : and :: entries` failures.

## 2026-06-02 Task 3 BFMs and reset smoke
- Added `pyuvm_work/pyuvm_fifo/` as the reusable package root; `import pyuvm_fifo` works from repo root when `prj_src/design_rv1_tv7/FIFO/pyuvm_work` is inserted onto `sys.path`.
- `fifo_bfm.py` now provides independent write/read clocks (`10ns` and `14ns` defaults), active-low reset sequencing, and one-cycle write/read pulse helpers that are safe for later functional tests.
- For reset stabilization on this FIFO, waiting five cycles in each domain while reset is asserted and three cycles in each domain after release was sufficient for `FifoSmokeTest` to observe `rempty=1`, `wfull=0`, `winc=0`, and `rinc=0` under Verilator.
- Python LSP reports warnings for untyped pyuvm/cocotb objects, but changed files can be kept error-free by suppressing only the local-package false positive on `from pyuvm_fifo.fifo_bfm import ...` and using dynamic DUT handle access where needed.

## 2026-06-02 Task 4 basic pyuvm read/write tests
- `test_async_fifo.py` now centralizes the assert-enabled check, DUT handle validation, and reset/clock bring-up in shared helpers so every `@pyuvm.test()` class starts from the same known-good state.
- Under default standard mode (`FWFT_EN=0`, `OUT_REG_EN=0`), the current helper flow matched RTL expectations: after one valid read pulse and one extra read-clock latency, `FifoSingleWriteReadTest` reliably read back `0x1234` at `224ns` in Verilator.
- Deterministic delayed traffic with write/read delays `[0, 1, 3, 5]` preserved FIFO order for `[0x1111, 0x1234, 0xABCD, 0x0F0F]`, and `FifoDelayBehaviorTest` passed at `560ns` with the existing BFM helpers.
- A local `regression-basic` Makefile target can safely loop over `FifoSmokeTest`, `FifoResetTest`, `FifoSingleWriteReadTest`, and `FifoDelayBehaviorTest` by reusing the existing `run` wrapper and `COCOTB_TEST_FILTER=$(TESTCASE)$$` mapping.

## 2026-06-02 Task 5 Python scoreboard and FIFO ordering tests
- Added `pyuvm_work/pyuvm_fifo/fifo_scoreboard.py` with a deque-backed `FifoScoreboard` that masks writes and reads to `WIDTH`, detects underflow/data mismatches with Python `assert`, and can assert stable `rempty`/`wfull` states after extra clock settling rather than same-cycle CDC edges.
- `test_async_fifo.py` now includes deterministic scoreboard-driven tests for ordered drain (`[0x0001, 0x00AA, 0x5555, 0xBEEF, 0xFFFF]`) and half-depth drain-at-empty behavior; both wait extra read/write clocks before checking flags so async pointer synchronization has time to settle.
- `resolve_signal_value()` keeps DUT control-signal checks safe by asserting `.value.is_resolvable` before converting `rempty`, `wfull`, `wrst`, `rrst`, `winc`, or `rinc` to integers.
- `regression-core` can reuse the existing `run` wrapper to execute smoke, reset, single-write/read, delay, order-preservation, and multi-item-drain tests in one loop without disturbing the existing `regression` or `regression-basic` targets.
- Verification results: `FifoOrderPreservationTest` passed at `448ns`, `FifoMultiItemDrainTest DEPTH=16` passed at `574ns`, and `conda run -n eda-pyuvm-fifo make regression-core` passed for all six core tests.

## 2026-06-02 Task 5 QA fix for regression-core
- cocotb's recursive make flow can incorrectly reuse a previous testcase's `results.xml` target inside looped regressions even when the outer wrapper removes the file first; the QA symptom was `make[3]: 'results.xml' is up to date.` at the `FifoDelayBehaviorTest` step.
- The minimal reliable fix was to keep the existing `run` wrapper and pass a testcase-specific `COCOTB_RESULTS_FILE` such as `results-FifoDelayBehaviorTest.xml`, so every loop iteration gets a distinct make target and must execute its own simulation.
- `clean::` should remove both the legacy `results.xml` and the new `results-*.xml` files so repeated verification runs leave no cocotb artifacts behind.

## 2026-06-02 Task 6 boundary and almost-flag tests
- Added `FifoFullEmptyBoundaryTest`, `FifoEmptyReadProtectionTest`, and `FifoAlmostFlagsTest` in `pyuvm_work/test_async_fifo.py`, all using Python `assert` only and waiting extra write/read clocks before strict flag checks so async CDC settling does not create same-cycle false failures.
- Verilator/cocotb can reuse an old `sim_build/Vtop` across nested make invocations even when `EXTRA_ARGS` changes, which breaks parameter-dependent generate blocks like `ALMOST_FULL_EN` and `ALMOST_EMPTY_EN`; the reliable local fix was to key `SIM_BUILD` off the elaboration-sensitive parameter set and pass that computed path through the `run` wrapper.
- Enabling the RTL almost-flag generate blocks under Verilator surfaces existing `WIDTHEXPAND` warnings in `wptr.sv` and `rptr.sv`; because Task 6 forbids RTL edits, the local Makefile suppresses that warning class with `COMPILE_ARGS += -Wno-WIDTHEXPAND` so the required almost-flag regression can compile unchanged RTL.

## 2026-06-02 Task 7 advanced async/mode tests
- Added deterministic advanced pyuvm tests for simultaneous async traffic, 200-op random regression, 1000-op stress bursts, FWFT direct visibility, and OUT_REG latency, all using Python `assert` and bounded waits only.
- For precise OUT_REG latency checks under cocotb/Verilator, sample `rdata` after the read-clock edge in `ReadOnly()`; sampling immediately after `RisingEdge` can observe pre-update values even when the RTL timing is correct.
- Keep `COCOTB_TEST_FILTER` scoped to the local `run` wrapper instead of setting a global default, otherwise cocotb's included `regression` path can receive both `COCOTB_TESTCASE` and `COCOTB_TEST_FILTER` and fail before simulation starts.

## 2026-06-02 Task 7 advanced async/mode tests
- Added deterministic advanced pyuvm tests for simultaneous async traffic, 200-op random regression, 1000-op stress bursts, FWFT direct visibility, and OUT_REG latency, all using Python `assert` and bounded waits only.
- For precise OUT_REG latency checks under cocotb/Verilator, sample `rdata` after the read-clock edge in `ReadOnly()`; sampling immediately after `RisingEdge` can observe pre-update values even when the RTL timing is correct.
- Keep `COCOTB_TEST_FILTER` scoped to the local `run` wrapper instead of setting a global default, otherwise cocotb's included `regression` path can receive both `COCOTB_TESTCASE` and `COCOTB_TEST_FILTER` and fail before simulation starts.

## 2026-06-02 Task 7 advanced async/mode tests
- Added deterministic advanced pyuvm tests for simultaneous async traffic, 200-op random regression, 1000-op stress bursts, FWFT direct visibility, and OUT_REG latency, all using Python  and bounded waits only.
- For precise OUT_REG latency checks under cocotb/Verilator, sample  after the read-clock edge in ; sampling immediately after  can observe pre-update values even when the RTL timing is correct.
- Keep  scoped to the local  wrapper instead of setting a global default, otherwise cocotb's included  path can receive both  and  and fail before simulation starts.

## 2026-06-02 Task 7 note
- Ignore the malformed duplicate Task 7 block immediately above this note; it was caused by shell quoting during append. The intended Task 7 learnings are the first complete Task 7 block and the corrected content in this note.
