
### 1. 如何运行仿真并查看波形/覆盖率

在终端的 `uvm_work` 路径下，使用 Makefile 运行所有需要的仿真目标。

#### A. 编译工程
在命令行中执行：
```bash
make compile
```

#### B. 运行 2000组随机并发混合读写测试 (对应需求2)
```bash
make sim TESTNAME=fifo_random_test
```

#### C. 运行写满读空与溢出/下溢极值测试 (对应需求1、3)
```bash
make sim TESTNAME=fifo_boundary_test
```

#### D. 启动 Verdi 调试硬件波形
仿真运行完毕后，会自动在 `uvm_work` 下生成 `tb_top.fsdb` 波形。键入以下指令即可一键启动 Verdi：
```bash
make verdi
```

#### E. 查看覆盖率结果 (代码+功能覆盖率)
Makefile 已内置了所有的代码覆盖率指标（行、翻转、状态机、分支、条件）。键入以下指令启动 DVE/Verdi 覆盖率视图：
```bash
make cov
```

#### F. 清理重置工程
```bash
make clean
```
