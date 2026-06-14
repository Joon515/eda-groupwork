# README

## 本UVM脚本体系
工程脚本体系"./async_fifo"来自于[git_repo](https://github.com/Kevin-Quinn-blackCat/Digital_Design_and_Verification_Platform)

## 快速上手
1. 需要将"win_make"文件夹所在路径添加到环境变量（需要手动添加，win_make也可以移动到其他地方，尽量位于稳定的路径下）
2. 需要将VScode添加到环境变量（一般随着VScode安装自动添加）
3. 需要确保Modelsim安装目录下的"\modeltech64_10.4\win64"添加到环境变量（一般随着Modelsim安装自动添加）
4. 点击"./async_fifo/launch.exe"自动启动VScode
5. 在所启动的VScode界面下，点击"Ctrl+Shift+B"呼出task选项列表，选择你要的脚本行为

## 示例流程
1. 完成《快速上手》1~4
2. 点击"Ctrl+Shift+B"后列表中选择"6. 清理并执行终端仿真"
3. 执行完成后"./async_fifo/sim/output/"下可以看见输出结果