# pyuvm/cocotb Verification Platform for Async FIFO

## TL;DR
> **Summary**: Add a side-by-side pyuvm/cocotb verification flow for the existing async FIFO, using a new conda environment, OSS CAD Suite Verilator, and Python `assert` checks only. Preserve the current SystemVerilog UVM/VCS flow as reference and add Chinese learning documentation explaining how the new platform is built and run.
> **Deliverables**:
> - `prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml`
> - `prj_src/design_rv1_tv7/FIFO/pyuvm_work/Makefile`
> - `prj_src/design_rv1_tv7/FIFO/pyuvm_work/pyuvm_fifo/` Python package
> - `prj_src/design_rv1_tv7/FIFO/pyuvm_work/test_async_fifo.py`
> - `prj_src/design_rv1_tv7/FIFO/doc/PYUVM_GUIDE.md` Chinese learning/build guide
> - README/document index update for the new guide
> **Effort**: Large
> **Parallel**: YES - 4 waves
> **Critical Path**: Task 1 → Task 2 → Task 3 → Tasks 4-7 → Task 8 → Final Verification

## Context

### Original Request
The project is a course assignment with an implemented asynchronous FIFO and an existing UVM platform at `prj_src/design_rv1_tv7/FIFO`. The teacher advised: try using pyuvm; try using assert for judgment/checking. The requested outcome is to build the pyuvm platform, create a new conda environment, and write documentation explaining the construction method for learning.

### Interview Summary
- User environment: OSS CAD Suite is available and includes Icarus Verilog/Verilator; no commercial simulator is available.
- Simulator decision: use Verilator as the primary cocotb backend.
- Assert decision: use Python `assert` only; do not add SystemVerilog assertions.
- Documentation decision: write Chinese learning documentation.
- Scope decision: add a side-by-side pyuvm/cocotb flow; do not replace or refactor the existing SV UVM flow.

### Metis Review (gaps addressed)
- Locked exact directory layout: `prj_src/design_rv1_tv7/FIFO/pyuvm_work/`.
- Locked conda strategy: conda creates Python environment; Verilator comes from OSS CAD Suite on `PATH`, not from conda.
- Locked package versions from PyPI as of planning: `pyuvm==4.0.1`, `cocotb==2.0.1`.
- Locked waveform strategy: optional but enabled by default via Verilator trace output; no human waveform inspection required for acceptance.
- Locked CI decision: no CI; local OSS CAD Suite execution only.
- Guardrail: Python must not run with optimization because `python -O` disables `assert`.

## Work Objectives

### Core Objective
Create a reproducible pyuvm/cocotb verification platform for `async_fifo_top` that can be run locally with conda + OSS CAD Suite Verilator and demonstrates teacher-requested Python `assert` checking.

### Deliverables
- New conda environment manifest under `pyuvm_work/environment.yml`.
- New cocotb Makefile under `pyuvm_work/Makefile` using only RTL sources.
- Python pyuvm package under `pyuvm_work/pyuvm_fifo/` with transaction, BFM/helper, scoreboard, environment, and sequence/test utilities.
- `pyuvm_work/test_async_fifo.py` containing pyuvm tests decorated with `@pyuvm.test()`.
- Chinese guide `doc/PYUVM_GUIDE.md` explaining conda setup, OSS CAD Suite/Verilator, cocotb, pyuvm, Python asserts, directory structure, run commands, and troubleshooting.
- README documentation index update pointing to `doc/PYUVM_GUIDE.md`.

### Definition of Done (verifiable conditions with commands)
- `conda env create -f prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml` succeeds on a clean machine with conda.
- `conda run -n eda-pyuvm-fifo python -c "import sys; assert not sys.flags.optimize; import cocotb, pyuvm; print(cocotb.__version__)"` prints `2.0.1` and exits 0.
- `verilator --version` exits 0 from the activated OSS CAD Suite shell.
- From `prj_src/design_rv1_tv7/FIFO/pyuvm_work`, `conda run -n eda-pyuvm-fifo make SIM=verilator TESTCASE=FifoSmokeTest` passes.
- From the same directory, `conda run -n eda-pyuvm-fifo make SIM=verilator regression` passes all planned tests with no Python assertion failures.
- `prj_src/design_rv1_tv7/FIFO/doc/PYUVM_GUIDE.md` exists and includes Chinese explanations for conda, pyuvm, cocotb, Verilator, and Python assert checking.

### Must Have
- Use Verilator as default: `SIM ?= verilator`.
- Use `TOPLEVEL=async_fifo_top`.
- Compile only the six RTL files in this order:
  1. `../rtl_src/fifo_cfg_pkg.sv`
  2. `../rtl_src/sync_gray.sv`
  3. `../rtl_src/dual_port_ram.sv`
  4. `../rtl_src/wptr.sv`
  5. `../rtl_src/rptr.sv`
  6. `../rtl_src/async_fifo_top.sv`
- Use Python `assert` for reset checks, data-order checks, full/empty checks, almost-full/almost-empty checks, and regression end-state checks.
- Explicitly verify `assert` is enabled with `assert not sys.flags.optimize`.
- Preserve existing SV UVM files and existing UVM documentation.

### Must NOT Have
- Must not add SystemVerilog `assert`, `assert property`, or `cover property`.
- Must not require VCS, Verdi, DVE, URG, FSDB, or any commercial simulator.
- Must not compile `uvm_src/fifo_if.sv`, `uvm_src/tb_top.sv`, or any SV UVM class file in the cocotb flow.
- Must not rewrite FIFO RTL behavior unless a compile-blocking Verilator issue is discovered; if discovered, document the issue and make the smallest compatibility fix only.
- Must not add CI unless separately requested.
- Must not rely on manual waveform inspection for pass/fail.

## Verification Strategy
> ZERO HUMAN INTERVENTION - all verification is agent-executed.
- Test decision: TDD-style incremental tests using pyuvm/cocotb + Verilator.
- Framework: conda environment with Python 3.11, `cocotb==2.0.1`, `pyuvm==4.0.1`.
- QA policy: Every task has agent-executed scenarios.
- Evidence: `.sisyphus/evidence/task-{N}-{slug}.{ext}`.
- Waveform policy: Verilator trace enabled by default when supported, but pass/fail uses logs and assertions only.

## Execution Strategy

### Parallel Execution Waves
> Target: 5-8 tasks per wave. This project is dependency-heavy, so Wave 1 is foundation, Wave 2 is core tests, Wave 3 is expanded coverage/docs, Wave 4 is final verification.

Wave 1: Task 1 environment + Task 2 Makefile/smoke scaffold.
Wave 2: Task 3 BFM/env + Task 4 basic reset/write-read + Task 5 scoreboard/order.
Wave 3: Task 6 boundary/almost flags + Task 7 async/random/FWFT modes + Task 8 Chinese documentation.
Wave 4: Final verification agents F1-F4.

### Dependency Matrix (full, all tasks)
- Task 1: blocks Tasks 2-8.
- Task 2: blocked by Task 1; blocks Tasks 3-7.
- Task 3: blocked by Task 2; blocks Tasks 4-7.
- Task 4: blocked by Task 3; blocks Task 5.
- Task 5: blocked by Task 4; blocks Tasks 6-7.
- Task 6: blocked by Task 5; no implementation dependents.
- Task 7: blocked by Task 5; no implementation dependents.
- Task 8: blocked by Tasks 1-7 for final command accuracy.

### Agent Dispatch Summary
- Wave 1 → 2 tasks → quick + unspecified-high.
- Wave 2 → 3 tasks → unspecified-high.
- Wave 3 → 3 tasks → unspecified-high + writing.
- Wave 4 → 4 final review tasks → oracle, unspecified-high, unspecified-high, deep.

## TODOs
> Implementation + Test = ONE task. Never separate.
> EVERY task MUST have: Agent Profile + Parallelization + QA Scenarios.

- [x] 1. Create conda environment manifest and Python dependency checks

  **What to do**:
  - Add `prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml`.
  - Use exact environment name `eda-pyuvm-fifo`.
  - Use conda-forge channel.
  - Include `python=3.11`, `pip`, `make`, and pip packages `cocotb==2.0.1`, `pyuvm==4.0.1`.
  - Do not include Verilator in conda; document that Verilator is provided by OSS CAD Suite on `PATH`.
  - Do not add a separate `pyuvm_work/README.md`; all explanatory prose belongs in `doc/PYUVM_GUIDE.md` in Task 8.

  **Must NOT do**:
  - Do not edit RTL or SV UVM files.
  - Do not install packages globally.
  - Do not depend on VCS/Verdi.

  **Recommended Agent Profile**:
  - Category: `quick` - Reason: bounded manifest/setup task.
  - Skills: [] - No specialized skill required.
  - Omitted: [`frontend-ui-ux`] - No UI work.

  **Parallelization**: Can Parallel: YES | Wave 1 | Blocks: Tasks 2-8 | Blocked By: none

  **References**:
  - Pattern: `README.md:1-64` - existing project-level directory/documentation style.
  - External: `https://docs.cocotb.org/en/stable/install.html` - cocotb installation context.
  - External: `https://pyuvm.readthedocs.io/` - pyuvm documentation.

  **Acceptance Criteria**:
  - [ ] `prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml` exists.
  - [ ] `conda env create -f prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml` exits 0 on a clean conda installation.
  - [ ] `conda run -n eda-pyuvm-fifo python -c "import sys; assert not sys.flags.optimize; import cocotb, pyuvm; print(cocotb.__version__)"` exits 0 and prints `2.0.1`.
  - [ ] `verilator --version` exits 0 in the OSS CAD Suite shell.

  **QA Scenarios**:
  ```
  Scenario: Fresh conda environment creation
    Tool: Bash
    Steps: Run `conda env remove -n eda-pyuvm-fifo -y || true`; then run `conda env create -f prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml`; then run `conda run -n eda-pyuvm-fifo python -c "import sys; assert not sys.flags.optimize; import cocotb, pyuvm; print(cocotb.__version__)"`.
    Expected: Environment creation exits 0; Python command exits 0 and prints `2.0.1`; no assertion failure.
    Evidence: .sisyphus/evidence/task-1-conda-env.log

  Scenario: Missing OSS CAD Suite / Verilator detection
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo python -c "import shutil; print(shutil.which('verilator'))"`; then run `verilator --version` in the OSS CAD Suite shell.
    Expected: The conda environment itself is not responsible for installing Verilator; the OSS CAD Suite shell reports a Verilator version; no conda package is required for Verilator.
    Evidence: .sisyphus/evidence/task-1-verilator-path.log
  ```

  **Commit**: NO | Message: N/A | Files: [`prj_src/design_rv1_tv7/FIFO/pyuvm_work/environment.yml`]

- [x] 2. Add cocotb/Verilator Makefile and smoke elaboration test

  **What to do**:
  - Add `prj_src/design_rv1_tv7/FIFO/pyuvm_work/Makefile`.
  - Set defaults: `SIM ?= verilator`, `TOPLEVEL_LANG ?= verilog`, `TOPLEVEL ?= async_fifo_top`, `MODULE ?= test_async_fifo`, `TESTCASE ?= FifoSmokeTest`, `WAVES ?= 1`.
  - Define `VERILOG_SOURCES` with exactly the six RTL files listed in `uvm_work/filelist:1-7` and omit `uvm_work/filelist:9-12` UVM sources.
  - Add parameter variables: `DEPTH ?= 16`, `WIDTH ?= 16`, `FWFT_EN ?= 0`, `OUT_REG_EN ?= 0`, `SYNC_STAGES ?= 2`, `ALMOST_FULL_EN ?= 0`, `ALMOST_FULL_VAL ?= 4`, `ALMOST_EMPTY_EN ?= 0`, `ALMOST_EMPTY_VAL ?= 4`.
  - Pass parameters with Verilator `-G...` options for the numeric/bit parameters above; leave enum reset parameters at RTL defaults for the initial platform.
  - Add `EXTRA_ARGS += --timing --trace` for Verilator.
  - Add initial `regression` target that runs `FifoSmokeTest`; later tasks must extend this target as their tests are added.
  - Add `clean` target that removes cocotb build artifacts under `pyuvm_work/` only.
  - Add initial `prj_src/design_rv1_tv7/FIFO/pyuvm_work/test_async_fifo.py` with one `@pyuvm.test()` class `FifoSmokeTest` that imports pyuvm, checks `assert not sys.flags.optimize`, waits at least one delta/timer, and asserts that DUT handles exist: `wclk`, `rclk`, `wrst`, `rrst`, `winc`, `rinc`, `wdata`, `rdata`, `wfull`, `rempty`.

  **Must NOT do**:
  - Do not include `fifo_if.sv`, `tb_top.sv`, or any UVM source in `VERILOG_SOURCES`.
  - Do not use `+UVM_TESTNAME`; pyuvm tests use cocotb/pyuvm test discovery.

  **Recommended Agent Profile**:
  - Category: `unspecified-high` - Reason: requires Makefile/cocotb simulator integration.
  - Skills: [] - No specialized skill required.
  - Omitted: [`git-master`] - No commit requested.

  **Parallelization**: Can Parallel: NO | Wave 1 | Blocks: Tasks 3-7 | Blocked By: Task 1

  **References**:
  - Pattern: `prj_src/design_rv1_tv7/FIFO/uvm_work/filelist:1-7` - RTL compile order.
  - Must omit: `prj_src/design_rv1_tv7/FIFO/uvm_work/filelist:9-12` - UVM/testbench sources unsuitable for cocotb.
  - API/Type: `prj_src/design_rv1_tv7/FIFO/rtl_src/async_fifo_top.sv:1-29` - TOPLEVEL name and DUT ports.
  - API/Type: `prj_src/design_rv1_tv7/FIFO/rtl_src/async_fifo_top.sv:3-14` - DUT parameters.
  - External: `https://docs.cocotb.org/en/stable/runner.html` - cocotb Makefile/runner flow.

  **Acceptance Criteria**:
  - [ ] `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoSmokeTest` exits 0.
  - [ ] Smoke test log contains no Python assertion failure.
  - [ ] A Python source check confirms `Makefile` does not contain `uvm_src`, `fifo_if.sv`, or `tb_top.sv` in `VERILOG_SOURCES`.

  **QA Scenarios**:
  ```
  Scenario: Verilator smoke elaboration
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoSmokeTest`.
    Expected: cocotb reports `FifoSmokeTest` passed; no compile reference to SV UVM files.
    Evidence: .sisyphus/evidence/task-2-smoke.log

  Scenario: Guard against accidental SV UVM compilation
    Tool: Bash
    Steps: Run `python - <<'PY'\nfrom pathlib import Path\np=Path('prj_src/design_rv1_tv7/FIFO/pyuvm_work/Makefile').read_text()\nfor bad in ['uvm_src', 'fifo_if.sv', 'tb_top.sv', '+UVM_TESTNAME']:\n    assert bad not in p, bad\nPY`.
    Expected: Python exits 0; any forbidden token fails with AssertionError.
    Evidence: .sisyphus/evidence/task-2-no-uvm-sources.log
  ```

  **Commit**: NO | Message: N/A | Files: [`prj_src/design_rv1_tv7/FIFO/pyuvm_work/Makefile`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/test_async_fifo.py`]

- [x] 3. Build pyuvm FIFO package, clocks, reset helper, and BFMs

  **What to do**:
  - Add package directory `prj_src/design_rv1_tv7/FIFO/pyuvm_work/pyuvm_fifo/` with `__init__.py`.
  - Add `fifo_transaction.py` defining a Python dataclass `FifoTransaction` with fields `data: int`, `is_write: bool`, and `delay: int`, mirroring `fifo_seq_item.sv:4-18`.
  - Add `fifo_bfm.py` with helpers:
    - `start_clocks(dut, w_period_ns=10, r_period_ns=14)` for independent `wclk` and `rclk`.
    - `reset_fifo(dut, cycles=5)` for default active-low reset: set `wrst=0`, `rrst=0`, clear enables/data, wait both domains, then set `wrst=1`, `rrst=1`, wait both domains.
    - `write_word(dut, data, delay=0)` that waits write clock cycles, drives `wdata`, asserts `winc` for one `wclk` cycle, and deasserts.
    - `read_word(dut, delay=0, latency=1)` that asserts `rinc` for one `rclk` cycle, waits latency cycles, returns integer `rdata`.
    - `wait_wclk(dut, cycles)` and `wait_rclk(dut, cycles)`.
  - Add `fifo_env.py` with pyuvm component skeletons sufficient for tests: `FifoEnv`, `FifoWriteDriver`, `FifoReadDriver`, `FifoMonitor` placeholders if tests directly use BFM first. Keep this lean; no overbuilt UVM hierarchy.
  - Update `test_async_fifo.py` so `FifoSmokeTest` starts clocks, resets DUT, and asserts reset state: `rempty == 1`, `wfull == 0`, `winc == 0`, `rinc == 0` after reset stabilization.

  **Must NOT do**:
  - Do not add random/stress tests here.
  - Do not model unsupported reset enum variants in Python yet; keep default active-low reset.

  **Recommended Agent Profile**:
  - Category: `unspecified-high` - Reason: Python/cocotb timing and multi-clock helpers.
  - Skills: [] - No specialized skill required.
  - Omitted: [`frontend-ui-ux`] - No UI work.

  **Parallelization**: Can Parallel: NO | Wave 2 | Blocks: Tasks 4-7 | Blocked By: Task 2

  **References**:
  - API/Type: `prj_src/design_rv1_tv7/FIFO/uvm_src/fifo_seq_item.sv:4-18` - transaction fields and delay constraints.
  - API/Type: `prj_src/design_rv1_tv7/FIFO/rtl_src/async_fifo_top.sv:16-28` - DUT clock/reset/control/data ports.
  - API/Type: `prj_src/design_rv1_tv7/FIFO/rtl_src/fifo_cfg_pkg.sv:10-14` - default active-low reset polarity enum values.
  - Pattern: `prj_src/design_rv1_tv7/FIFO/rtl_src/async_fifo_top.sv:58-95` - reset bridge behavior.

  **Acceptance Criteria**:
  - [ ] `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoSmokeTest` passes.
  - [ ] Smoke test includes at least four Python `assert` statements, including `assert int(dut.rempty.value) == 1` after reset.
  - [ ] Python package import check passes: `conda run -n eda-pyuvm-fifo python -c "import sys; sys.path.insert(0, 'prj_src/design_rv1_tv7/FIFO/pyuvm_work'); import pyuvm_fifo"`.

  **QA Scenarios**:
  ```
  Scenario: Reset happy path
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoSmokeTest`.
    Expected: After reset release, Python asserts confirm empty=1 and full=0; test passes.
    Evidence: .sisyphus/evidence/task-3-reset.log

  Scenario: Assert-enabled guard
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo python -c "import sys; assert not sys.flags.optimize"`; then run `conda run -n eda-pyuvm-fifo python -O -c "import sys; raise SystemExit(0 if sys.flags.optimize else 1)"`.
    Expected: First command exits 0 and proves normal asserts are enabled; second command exits 0 and proves `-O` sets optimization, which the guide forbids because Python assert statements would be skipped.
    Evidence: .sisyphus/evidence/task-3-assert-enabled.log
  ```

  **Commit**: NO | Message: N/A | Files: [`prj_src/design_rv1_tv7/FIFO/pyuvm_work/pyuvm_fifo/*`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/test_async_fifo.py`]

- [x] 4. Add reset, single write/read, and delay behavior pyuvm tests

  **What to do**:
  - In `test_async_fifo.py`, add pyuvm test classes:
    - `FifoResetTest`: reset-only state validation.
    - `FifoSingleWriteReadTest`: write `0x1234`, read it back, assert equality.
    - `FifoDelayBehaviorTest`: write/read several values with delays `[0, 1, 3, 5]` and assert returned data order.
  - Ensure BFM read latency matches standard mode defaults from `async_fifo_top.sv:175-226`: default `FWFT_EN=0`, `OUT_REG_EN=0` gives one read-clock latency; `OUT_REG_EN=1` gives two read-clock latency.
  - Make `Makefile` support `TESTCASE=<class>` and `regression-basic` target running these three tests plus smoke.
  - All pass/fail checks must be Python `assert` statements, not log-string comparisons.

  **Must NOT do**:
  - Do not introduce randomized tests yet.
  - Do not silently ignore unknown `X/Z` values; convert only after checking `value.is_resolvable` where needed.

  **Recommended Agent Profile**:
  - Category: `unspecified-high` - Reason: cocotb timing correctness and assert-based functional checks.
  - Skills: [] - No specialized skill required.
  - Omitted: [`git-master`] - No commit requested.

  **Parallelization**: Can Parallel: NO | Wave 2 | Blocks: Task 5 | Blocked By: Task 3

  **References**:
  - Pattern: `prj_src/design_rv1_tv7/FIFO/doc/TEST_SUITE.md:13-19` - existing verification goals to mirror.
  - Test: `prj_src/design_rv1_tv7/FIFO/doc/TEST_SUITE.md:198-218` - existing delay behavior intent.
  - API/Type: `prj_src/design_rv1_tv7/FIFO/rtl_src/async_fifo_top.sv:175-226` - standard mode read latency.

  **Acceptance Criteria**:
  - [ ] `FifoResetTest`, `FifoSingleWriteReadTest`, and `FifoDelayBehaviorTest` pass individually under Verilator.
  - [ ] `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work regression-basic` exits 0.
  - [ ] At least one test intentionally verifies a nonzero delay path.

  **QA Scenarios**:
  ```
  Scenario: Single data happy path
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoSingleWriteReadTest`.
    Expected: Test writes 0x1234, reads 0x1234, and passes through Python assert equality.
    Evidence: .sisyphus/evidence/task-4-single-write-read.log

  Scenario: Delay edge path
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoDelayBehaviorTest`.
    Expected: Delay values 0, 1, 3, 5 all pass; data order is unchanged; no assertion failure.
    Evidence: .sisyphus/evidence/task-4-delay.log
  ```

  **Commit**: NO | Message: N/A | Files: [`prj_src/design_rv1_tv7/FIFO/pyuvm_work/test_async_fifo.py`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/Makefile`]

- [x] 5. Add Python scoreboard and FIFO ordering tests

  **What to do**:
  - Add `prj_src/design_rv1_tv7/FIFO/pyuvm_work/pyuvm_fifo/fifo_scoreboard.py`.
  - Implement `FifoScoreboard` with:
    - `expected = deque()`.
    - `push_write(data)` appends masked `WIDTH` bits.
    - `pop_and_check(actual)` pops expected data and uses `assert actual == expected`.
    - `assert_empty()` verifies no unread expected data remains.
    - `check_flags(dut, depth, capacity)` uses Python asserts for core flags, with CDC latency tolerance documented and only strict at stable points.
  - Port the core idea from the SV scoreboard: expected queue, write/read counts, error-free final state.
  - Add tests:
    - `FifoOrderPreservationTest`: write deterministic sequence `[0x0001, 0x00AA, 0x5555, 0xBEEF, 0xFFFF]`, read all, assert order.
    - `FifoMultiItemDrainTest`: write `DEPTH/2` values, drain, assert scoreboard empty and `rempty==1` after stabilization.
  - Add `regression-core` target including smoke, basic, and scoreboard tests.

  **Must NOT do**:
  - Do not rely on print/log messages as pass/fail.
  - Do not check almost flags here; that belongs to Task 6.

  **Recommended Agent Profile**:
  - Category: `unspecified-high` - Reason: golden model and CDC-aware assertion design.
  - Skills: [] - No specialized skill required.
  - Omitted: [`frontend-ui-ux`] - No UI work.

  **Parallelization**: Can Parallel: NO | Wave 2 | Blocks: Tasks 6-7 | Blocked By: Task 4

  **References**:
  - Pattern: `prj_src/design_rv1_tv7/FIFO/uvm_src/fifo_scoreboard.sv:24-31` - queue and counters.
  - Pattern: `prj_src/design_rv1_tv7/FIFO/uvm_src/fifo_scoreboard.sv:60-82` - read compare behavior.
  - Pattern: `prj_src/design_rv1_tv7/FIFO/uvm_src/fifo_scoreboard.sv:131-140` - final report pass/fail concept.
  - Test: `prj_src/design_rv1_tv7/FIFO/doc/TEST_SUITE.md:45-67` - random/order/data integrity goals.

  **Acceptance Criteria**:
  - [ ] `FifoOrderPreservationTest` passes with deterministic data list.
  - [ ] `FifoMultiItemDrainTest` passes and asserts final empty state.
  - [ ] `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work regression-core` exits 0.
  - [ ] `fifo_scoreboard.py` contains Python `assert` statements for data comparison and final empty state.

  **QA Scenarios**:
  ```
  Scenario: FIFO ordering happy path
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoOrderPreservationTest`.
    Expected: Read sequence equals write sequence exactly; scoreboard final queue is empty.
    Evidence: .sisyphus/evidence/task-5-order.log

  Scenario: Drain-to-empty edge path
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoMultiItemDrainTest DEPTH=16`.
    Expected: After draining all written items and waiting CDC stabilization, `rempty==1`, `wfull==0`, and scoreboard queue empty.
    Evidence: .sisyphus/evidence/task-5-drain-empty.log
  ```

  **Commit**: NO | Message: N/A | Files: [`prj_src/design_rv1_tv7/FIFO/pyuvm_work/pyuvm_fifo/fifo_scoreboard.py`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/test_async_fifo.py`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/Makefile`]

- [x] 6. Add boundary, full/empty, and almost flag tests

  **What to do**:
  - Add pyuvm tests:
    - `FifoFullEmptyBoundaryTest`: with `DEPTH=8`, write 8 words, wait at least `SYNC_STAGES + 2` write-clock cycles, assert `wfull==1`; attempt extra write while full and assert accepted read sequence excludes overflow data; drain and assert `rempty==1`.
    - `FifoEmptyReadProtectionTest`: after reset, pulse `rinc` while empty, wait read latency, assert scoreboard remains empty and `rempty==1`.
    - `FifoAlmostFlagsTest`: run with `DEPTH=8 ALMOST_FULL_EN=1 ALMOST_FULL_VAL=2 ALMOST_EMPTY_EN=1 ALMOST_EMPTY_VAL=2`; assert `walmost_full==1` after stable occupancy reaches threshold and `ralmost_empty==1` after stable drain reaches threshold.
  - Add Makefile target `regression-boundary` for these tests with required parameters.
  - In flag checks, wait stabilization cycles before strict assertions to account for asynchronous pointer synchronization.

  **Must NOT do**:
  - Do not assert almost flags immediately on the same cycle as the write/read causing threshold crossing.
  - Do not use SV assertions.

  **Recommended Agent Profile**:
  - Category: `unspecified-high` - Reason: boundary conditions and CDC timing nuance.
  - Skills: [] - No specialized skill required.
  - Omitted: [`frontend-ui-ux`] - No UI work.

  **Parallelization**: Can Parallel: YES | Wave 3 | Blocks: none | Blocked By: Task 5

  **References**:
  - Pattern: `prj_src/design_rv1_tv7/FIFO/uvm_src/fifo_scoreboard.sv:87-126` - existing flag-checking intent.
  - Test: `prj_src/design_rv1_tv7/FIFO/doc/TEST_SUITE.md:76-112` - full/empty boundary test intent.
  - Test: `prj_src/design_rv1_tv7/FIFO/doc/TEST_SUITE.md:115-155` - full/empty toggle intent.
  - API/Type: `prj_src/design_rv1_tv7/FIFO/rtl_src/async_fifo_top.sv:11-14` - almost flag parameters.
  - API/Type: `prj_src/design_rv1_tv7/FIFO/rtl_src/async_fifo_top.sv:125-160` - write/read pointer flag instances.

  **Acceptance Criteria**:
  - [ ] `FifoFullEmptyBoundaryTest` passes with `DEPTH=8`.
  - [ ] `FifoEmptyReadProtectionTest` passes.
  - [ ] `FifoAlmostFlagsTest` passes with almost flags enabled and threshold value 2.
  - [ ] `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work regression-boundary` exits 0.

  **QA Scenarios**:
  ```
  Scenario: Full and empty boundary happy path
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoFullEmptyBoundaryTest DEPTH=8`.
    Expected: FIFO reaches full after 8 accepted writes, ignores overflow write for scoreboard purposes, drains all 8 valid words, then reaches empty.
    Evidence: .sisyphus/evidence/task-6-full-empty.log

  Scenario: Almost flag edge path
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoAlmostFlagsTest DEPTH=8 ALMOST_FULL_EN=1 ALMOST_FULL_VAL=2 ALMOST_EMPTY_EN=1 ALMOST_EMPTY_VAL=2`.
    Expected: After stabilization, `walmost_full` asserts near full and `ralmost_empty` asserts near empty; Python assertions determine pass/fail.
    Evidence: .sisyphus/evidence/task-6-almost-flags.log
  ```

  **Commit**: NO | Message: N/A | Files: [`prj_src/design_rv1_tv7/FIFO/pyuvm_work/test_async_fifo.py`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/Makefile`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/pyuvm_fifo/*`]

- [x] 7. Add async simultaneous, random, stress, and FWFT/OUT_REG mode tests

  **What to do**:
  - Add pyuvm tests:
    - `FifoAsyncSimultaneousReadWriteTest`: run independent writer and reader coroutines with different clocks and assert no corruption.
    - `FifoRandomRegressionTest`: deterministic seed `0xEDA2026`, generate 200 operations with bounded delays, maintain scoreboard, and assert final consistency.
    - `FifoStressTest`: deterministic seed `0xF1F0`, 1000 operations total, back-to-back where legal, intended for regression but still bounded for course runtime.
    - `FifoFwftDirectTest`: run with `FWFT_EN=1 OUT_REG_EN=0`; after first write and stabilization, assert first word appears without an explicit extra read latency beyond FWFT behavior.
    - `FifoOutRegLatencyTest`: run with `FWFT_EN=0 OUT_REG_EN=1`; assert read data appears after two read-clock cycles, matching `async_fifo_top.sv:197-226`.
  - Add Makefile target `regression-advanced` for these tests and parameterized invocations.
  - Add final `regression` target that runs smoke/basic/core/boundary/advanced.

  **Must NOT do**:
  - Do not make random tests nondeterministic; fixed seeds only.
  - Do not require coverage metrics; this is a pyuvm/assert platform, not coverage closure.
  - Do not allow stress test to run unbounded.

  **Recommended Agent Profile**:
  - Category: `unspecified-high` - Reason: multi-clock concurrency, mode-dependent latency, deterministic randomization.
  - Skills: [] - No specialized skill required.
  - Omitted: [`git-master`] - No commit requested.

  **Parallelization**: Can Parallel: YES | Wave 3 | Blocks: Task 8 | Blocked By: Task 5

  **References**:
  - Test: `prj_src/design_rv1_tv7/FIFO/doc/TEST_SUITE.md:159-185` - stress test intent.
  - Test: `prj_src/design_rv1_tv7/FIFO/doc/TEST_SUITE.md:45-67` - random/data integrity intent.
  - API/Type: `prj_src/design_rv1_tv7/FIFO/rtl_src/async_fifo_top.sv:228-236` - FWFT direct behavior.
  - API/Type: `prj_src/design_rv1_tv7/FIFO/rtl_src/async_fifo_top.sv:238-260` - FWFT + output register/skid-buffer branch start.
  - API/Type: `prj_src/design_rv1_tv7/FIFO/rtl_src/async_fifo_top.sv:197-226` - OUT_REG standard-mode latency.

  **Acceptance Criteria**:
  - [ ] `FifoAsyncSimultaneousReadWriteTest` passes.
  - [ ] `FifoRandomRegressionTest` passes deterministically with seed `0xEDA2026`.
  - [ ] `FifoStressTest` passes deterministically with seed `0xF1F0` and completes within 120 seconds in the local OSS CAD Suite shell.
  - [ ] `FifoFwftDirectTest` passes with `FWFT_EN=1 OUT_REG_EN=0`.
  - [ ] `FifoOutRegLatencyTest` passes with `FWFT_EN=0 OUT_REG_EN=1`.
  - [ ] `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work regression` exits 0.

  **QA Scenarios**:
  ```
  Scenario: Async simultaneous happy path
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoAsyncSimultaneousReadWriteTest DEPTH=16`.
    Expected: Concurrent write/read coroutines complete; scoreboard reads exactly the written order; no assertion failure.
    Evidence: .sisyphus/evidence/task-7-async-simultaneous.log

  Scenario: Mode latency edge paths
    Tool: Bash
    Steps: Run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoFwftDirectTest FWFT_EN=1 OUT_REG_EN=0`; then run `conda run -n eda-pyuvm-fifo make -C prj_src/design_rv1_tv7/FIFO/pyuvm_work SIM=verilator TESTCASE=FifoOutRegLatencyTest FWFT_EN=0 OUT_REG_EN=1`.
    Expected: FWFT direct mode exposes first word according to FWFT behavior; OUT_REG mode checks two-cycle read latency; both pass by Python asserts.
    Evidence: .sisyphus/evidence/task-7-mode-latency.log
  ```

  **Commit**: NO | Message: N/A | Files: [`prj_src/design_rv1_tv7/FIFO/pyuvm_work/test_async_fifo.py`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/Makefile`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/pyuvm_fifo/*`]

- [ ] 8. Write Chinese pyuvm learning guide and update documentation index

  **What to do**:
  - Add `prj_src/design_rv1_tv7/FIFO/doc/PYUVM_GUIDE.md` in Chinese.
  - Required sections:
    1. `为什么引入 pyuvm/cocotb` - explain teacher request and relationship to existing UVM.
    2. `环境准备` - conda environment creation, activation, OSS CAD Suite/Verilator `PATH`, package versions.
    3. `目录结构` - explain every new file under `pyuvm_work/`.
    4. `Makefile 构建方法` - explain `SIM`, `TOPLEVEL`, `MODULE`, `TESTCASE`, `VERILOG_SOURCES`, `-G` parameters, and why UVM SV files are omitted.
    5. `pyuvm 平台结构` - transaction/BFM/scoreboard/test classes and how they map from SV UVM.
    6. `assert 判断方法` - explain Python `assert`, why `python -O` is forbidden, examples of data/flag asserts.
    7. `运行命令` - exact commands for smoke, basic, boundary, advanced, full regression.
    8. `常见问题` - Verilator not found, conda not activated, assertion disabled, cocotb cannot find module, wrong parameter mode.
    9. `与原 UVM 平台对比` - concise comparison table.
  - Update project `README.md` documentation index to include `prj_src/design_rv1_tv7/FIFO/doc/PYUVM_GUIDE.md` in both English and Chinese sections.
  - Update `.gitignore` only for new pyuvm/cocotb generated artifacts: `prj_src/design_rv1_tv7/FIFO/pyuvm_work/sim_build/`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/results.xml`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/*.vcd`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/*.fst`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/**/__pycache__/`, `prj_src/design_rv1_tv7/FIFO/pyuvm_work/.pytest_cache/`.

  **Must NOT do**:
  - Do not delete or rewrite existing UVM docs.
  - Do not claim SVA was implemented.
  - Do not include commercial simulator commands as the main path; mention the existing VCS flow only as historical/reference context.

  **Recommended Agent Profile**:
  - Category: `writing` - Reason: Chinese technical learning documentation.
  - Skills: [] - No specialized skill required.
  - Omitted: [`frontend-ui-ux`] - No visual UI work.

  **Parallelization**: Can Parallel: YES | Wave 3 | Blocks: Final Verification | Blocked By: Tasks 1-7 for exact commands

  **References**:
  - Pattern: `README.md:98-118` - English quick-start/documentation index style.
  - Pattern: `README.md:214-234` - Chinese quick-start/documentation index style.
  - Pattern: `prj_src/design_rv1_tv7/FIFO/doc/TEST_SUITE.md:1-20` - Chinese documentation tone and verification goals.
  - External: `https://pyuvm.readthedocs.io/` - pyuvm official docs.
  - External: `https://docs.cocotb.org/en/stable/` - cocotb official docs.

  **Acceptance Criteria**:
  - [ ] `prj_src/design_rv1_tv7/FIFO/doc/PYUVM_GUIDE.md` exists and is primarily Chinese.
  - [ ] Guide includes all 9 required sections above.
  - [ ] Guide includes exact commands for `conda env create`, `conda activate`, `verilator --version`, smoke test, and full regression.
  - [ ] Guide explicitly states Python `assert` is disabled by `python -O` and must not be used in this project flow.
  - [ ] README contains links to `PYUVM_GUIDE.md` in both English and Chinese documentation indexes.
  - [ ] `.gitignore` adds only the pyuvm/cocotb generated artifact patterns listed above and does not ignore source/docs.

  **QA Scenarios**:
  ```
  Scenario: Documentation command accuracy
    Tool: Bash
    Steps: Extract every shell command from `PYUVM_GUIDE.md` that begins with `conda`, `verilator`, or `make`; execute smoke and regression commands exactly as documented in the activated environment.
    Expected: Documented commands execute successfully or are explicitly marked as examples not to execute; smoke and regression pass.
    Evidence: .sisyphus/evidence/task-8-doc-commands.log

  Scenario: Documentation scope guard
    Tool: Bash
    Steps: Run a Python script that reads `PYUVM_GUIDE.md` and asserts it contains `Python assert`, `pyuvm`, `cocotb`, `Verilator`, `conda`, and does not claim `assert property` implementation.
    Expected: Script exits 0; guide is aligned with user decisions.
    Evidence: .sisyphus/evidence/task-8-doc-scope.log
  ```

  **Commit**: NO | Message: N/A | Files: [`prj_src/design_rv1_tv7/FIFO/doc/PYUVM_GUIDE.md`, `README.md`, `.gitignore`]

## Final Verification Wave (MANDATORY — after ALL implementation tasks)
> 4 review agents run in PARALLEL. ALL must APPROVE. Present consolidated results to user and get explicit "okay" before completing.
> **Do NOT auto-proceed after verification. Wait for user's explicit approval before marking work complete.**
> **Never mark F1-F4 as checked before getting user's okay.** Rejection or user feedback -> fix -> re-run -> present again -> wait for okay.
- [ ] F1. Plan Compliance Audit — oracle
- [ ] F2. Code Quality Review — unspecified-high
- [ ] F3. Real Manual QA — unspecified-high
- [ ] F4. Scope Fidelity Check — deep

## Commit Strategy
- User did not request commits. Do not commit by default.
- If the user later explicitly requests commits, use atomic commits in this order:
  1. `chore(pyuvm): add conda environment manifest`
  2. `test(pyuvm): add cocotb verilator scaffold`
  3. `test(pyuvm): add fifo bfm and basic assertions`
  4. `test(pyuvm): add scoreboard and boundary regressions`
  5. `docs(pyuvm): add chinese learning guide`

## Success Criteria
- New pyuvm/cocotb platform runs under OSS CAD Suite Verilator with conda-managed Python dependencies.
- Existing SV UVM/VCS files remain available and are not compiled in the pyuvm flow.
- All checking in the new platform uses Python `assert`.
- Basic, boundary, random/stress, and selected mode-latency scenarios pass with deterministic commands.
- Chinese learning documentation teaches how the platform was built and how to run it.
- Final verification wave passes and user explicitly approves the consolidated result.
