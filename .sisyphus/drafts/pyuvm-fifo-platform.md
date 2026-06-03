# Draft: pyuvm FIFO Platform

## Requirements (confirmed)
- User's exact request: "按照老师的要求完成pyuvm平台的构建（要求新建一个conda环境）；完成文档，指出构建方法以供学习。"
- Existing project: course assignment with implemented async FIFO and SystemVerilog UVM platform at `prj_src/design_rv1_tv7/FIFO`.
- Teacher guidance: "尝试使用pyuvm；尝试使用assert作判断。"

## Technical Decisions
- Preserve existing RTL and SV UVM platform as reference; add pyuvm/cocotb platform alongside it rather than replacing existing files.
- Mirror existing UVM architecture in Python where practical: transaction, write/read BFMs or drivers, monitors, scoreboard, tests.
- User decision: use only Python `assert` for pyuvm/cocotb functional and scoreboard checks; do not add SystemVerilog assertions.
- Use a project-local conda environment definition and documentation so the learning path is reproducible.
- User environment decision: current machine has OSS CAD Suite with Icarus Verilog/Verilator and no commercial simulator, so target open-source simulation rather than VCS.
- User documentation decision: write Chinese learning documentation.

## Research Findings
- Existing simulation is VCS/Verdi/URG/FSDB-driven via `prj_src/design_rv1_tv7/FIFO/uvm_work/Makefile` and `filelist`.
- Current UVM structure: `tb_top.sv` -> `fifo_env_pkg.sv` -> `fifo_env.sv` -> write/read agents -> drivers/monitors -> scoreboard + coverage.
- No current `assert`, `assert property`, or `cover property` usage was found in FIFO `.sv` sources; checking is scoreboard-based in `fifo_scoreboard.sv`.
- Existing documentation covers SIM, TEST_SUITE, TEST_TUTORIAL, UVM_ANALYSIS, RTL_ANALYSIS, and coverage patch workflow.
- No CI or Python dependency manifests were found; `.gitignore` is empty.
- Official references: pyuvm docs `https://pyuvm.readthedocs.io/`, pyuvm repo examples `https://github.com/pyuvm/pyuvm`, cocotb docs `https://docs.cocotb.org/en/stable/`.

## Open Questions
- Which open-source simulator should be the primary pyuvm/cocotb target after compatibility review: Icarus Verilog or Verilator?
- Should generated logs/waves/coverage files be ignored via `.gitignore`, or should that remain out of scope?

## Scope Boundaries
- INCLUDE: pyuvm/cocotb verification platform for async FIFO, conda environment setup, runnable instructions, learning documentation, assertion-based checks.
- INCLUDE: OSS CAD Suite based workflow; no reliance on VCS/Verdi.
- INCLUDE: preserve existing SV UVM flow for comparison/reference.
- EXCLUDE: commercial simulator dependency.
- EXCLUDE: SystemVerilog assertion implementation; assert checks are Python-side only.
- EXCLUDE: rewriting FIFO RTL functionality unless required for simulator compatibility or assertions.
- EXCLUDE: replacing existing UVM platform.
