# Issues: pyuvm-fifo-platform

## 2026-06-02 Start Work
- Background research tasks are running for pyuvm/cocotb examples and RTL compatibility; collect before Makefile/test scaffold if Task 1 verification passes quickly.
- YAML LSP diagnostics could not run because `yaml-language-server` is not installed in this workspace; file content was still validated by inspection and conda creation succeeded.

## 2026-06-02 Task 2 Prep
- Existing README English section says `make run`, while the actual UVM Makefile uses `run_all`; do not copy that stale command into new docs.
- pyuvm syntax/Makefile research completed. Important caveat: plan names `TESTCASE`, but cocotb 2.0 prefers `COCOTB_TEST_FILTER`; Task 2 should provide `TESTCASE` as a user-friendly wrapper variable and export/map it to cocotb's current variable.
