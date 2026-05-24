# 如何运行仿真并查看波形/覆盖率

在终端的 `uvm_work` 路径下，使用 Makefile 运行所有需要的仿真目标。

## A. 全自动测试
在命令行中执行：
> 全自动回环编译-仿真
```bash
make run_all
```

## B. 启动 Verdi 调试硬件波形
仿真运行完毕后，会自动在 `uvm_work` 下生成 `tb_top.fsdb` 波形。键入以下指令即可一键启动 Verdi：
> 但是实际上波形输出的是最后一次测试的波形
```bash
make verdi
```

## C. 查看覆盖率结果
Makefile 已内置了所有的代码覆盖率指标（行、翻转、分支、条件）。键入以下指令启动覆盖率视图：
> 生成可交互页面覆盖率报告
```bash
make html_cov
```

> 启动DVE查看覆盖率报告
```bash
make cov
```

## D. 清理重置工程
> uvm_work内可能会遗留报告或log文件，若不需要也可以删除
> 只有filelist和Makefile是不能删除的
```bash
make clean
```
