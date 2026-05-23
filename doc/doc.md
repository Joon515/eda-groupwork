# 广东工业大学 EDA 课程设计报告大纲

## 设计题目：基于 Verilog 的异步 FIFO 系统设计与多平台验证

---

### 一、 设计题目与设计目的
#### 1.1 设计题目
* 基于 Verilog/SystemVerilog 的高可靠性跨时钟域异步 FIFO 系统设计
#### 1.2 设计目的
* 掌握跨时钟域（CDC）信号传输的设计规律，理解多时钟域设计中的潜在风险。
* 深入理解异步 FIFO 的硬件架构、读写控制逻辑及空满标志位的产生机理。
* 学习并应用格雷码进行指针编码及双级寄存器同步技术，抑制亚稳态。
* 实践多维度验证方法学，构建基于 SystemVerilog 覆盖率收集、C++ 算法辅助验证及高级 UVM 验证框架。
* 培养团队协作开发、项目版本控制与规范化 EDA 报告编写能力。

---

### 二、 跨时钟域传输与亚稳态理论基础
#### 2.1 亚稳态产生的原因
* 触发器建立时间（Setup Time）与保持时间（Hold Time）定义。
* 跨时钟域异步信号采样中的时序违规。
* 决断时间（Settling Time / Resolution Time）及输出不确定性分析。
* 平均无故障工作时间（MTBF）数学模型。
#### 2.2 亚稳态的解决方法
* 单比特信号同步：两级寄存器同步器（2-FF Synchronizer）的工作原理与去亚稳态效果。
* 跨时钟域信号类型分析及同步器件（电平、边沿、脉冲同步器）的选择。
#### 2.3 格雷码的使用及其原因
* 多比特二进制指针跨时钟域直接同步的时序 race hazard（竞争冒险）分析。
* 格雷码（Gray Code）相邻跳变仅单比特变化的数学特性。
* 格雷码指针经过两级寄存器同步后，其“亚稳态抑制”与“即便采样错误也仅落后一拍（Pessimistic design）”的安全性分析。
* 二进制与格雷码相互转换的硬件实现原理（公式与异或门网络设计）。

---

### 三、 异步 FIFO 系统架构设计思路
#### 3.1 总体设计思路与预设条件
* 异步时钟域设定：读时钟频率为写时钟频率的 3 倍 ($f_{rclk} = 3 \times f_{wclk}$)。
* 存储介质：$16 \text{ bit} \times 64$ 深度双口 RAM。
* 架构划分：双时钟域完全隔离设计，全寄存器输出。
#### 3.2 总体系统模块框图
* 读时钟域控制子系统。
* 写时钟域控制子系统。
* 双口 RAM 存储阵列。
* 跨时钟域指针同步链路（格雷码形式传输）。
#### 3.3 异步 FIFO 深度计算与时序裕量分析
* 结合 Burst 传输特性的 FIFO 最小安全深度推导方法（针对不同时钟频差及空闲周期的最坏情况分析）。
* 为什么在 $f_{rclk} = 3 \times f_{wclk}$（读快写慢）的情况下，FIFO 深度设置为 64 具有极高的时序安全裕量。
#### 3.4 空、满状态判定逻辑及悲观（Pessimistic）策略
* 引入额外 1 位（MSB）作为折返标志位设计。
* 空（Empty）标志判定条件：读写格雷码指针完全相等。
* 满（Full）标志判定条件：读写格雷码指针高两位相反，其余位相同。
* 悲观标志位的实时性分析：写满判断是即时的，读空判断是即时的，消除溢出与读空风险。

---

### 四、 异步 FIFO 系统具体模块设计与实现
#### 4.1 双口 RAM 模块 (`fifomem.v`)
* 端口定义与多时钟读写驱动。
* 基于 Verilog 行为级建模，杜绝直接调用第三方 IP 模块。
#### 4.2 读指针与空标志产生模块 (`rptr_empty.v`)
* 读地址指针增加、二进制自增及格雷码转换。
* 同步后的写指针与本地读指针比较逻辑。
#### 4.3 写指针与满标志产生模块 (`wptr_full.v`)
* 写地址指针增加、二进制自增及格雷码转换。
* 同步后的读指针与本地写指针比较逻辑。
#### 4.4 跨时钟域指针双级同步模块 (`sync_r2w.v` / `sync_w2r.v`)
* 基于双寄存器链（Double Flip-flop）的硬件结构及参数化设计。
#### 4.5 核心模块的算法伪代码与 Verilog RTL 源码结构

---

### 五、 功能拓展设计（加分与进阶项）
#### 5.1 水位控制逻辑设计 (Almost Full / Almost Empty)
* 基于格雷码转换为二进制指针后计算真实数据残留量（Watermark）。
* 预警标志输出，提高异步系统前级/后级流控安全性。
#### 5.2 异步复位及同步释放（Reset Bridge）机制
* 避免异步复位信号在时钟沿变化引起触发器输出亚稳态。
* 读写时钟域分别进行局部同步复位链设计。

---

### 六、 多验证平台搭建与仿真分析
#### 6.1 验证功能列表（Verification Feature List）与测试用例（Testcase）设计
* **Testcase 1**: 随机数据持续写入直到触发 Full，再持续读取直到触发 Empty。
* **Testcase 2**: 2000 组随机混合读写（读写时钟满足 $f_{rclk} = 3 \times f_{wclk}$），校验标志位及数据完整性。
* **Testcase 3**: 溢出边界防御测试。Full 状态下强行执行写操作（检验数据不被覆盖）；Empty 状态下强行执行读操作（检验读指针不更新，数据无效）。
#### 6.2 SystemVerilog 功能覆盖率（Coverage）测试平台
* 事务类（Transaction）、驱动器（Generator & Driver）、监视器（Monitor）与记分板（Scoreboard）设计。
* **功能覆盖率组 (Covergroup)** 定义：读写使能交叉覆盖率、空满状态交叉覆盖率、数据边界覆盖率。
#### 6.3 C++ 验证平台设计
* 采用 C++ 实现黄金参考模型（Golden Model）算法。
* 基于 SystemVerilog DPI-C 或仿真器接口比对机制。
#### 6.4 UVM 验证平台搭建（高级加分项）
* UVM 测试平台总体拓扑架构（`uvm_env`, `uvm_agent`, `sequencer`, `driver`, `monitor`, `scoreboard`）。
* 基于 UVM Sequence 的激励产生与重构机制。
* 事务级建模（TLM）端口互联与数据比对。
#### 6.5 仿真结果、Log 文件与覆盖率报告分析
* 仿真波形关键时间点标注与时序图释。
* 功能覆盖率报告截图及 100% 覆盖分析。

---

### 七、 团队协作分工与项目历史管理
#### 7.1 成员职责与分工
* **组长**：主要职责（如：异步 FIFO 核心 RTL 编码、多平台集成）。
* **组员 A**：主要职责（如：SV 功能覆盖率验证平台构建、C++ DPI-C 接口编写）。
* **组员 B**：主要职责（如：UVM 测试用例设计、加分项功能拓展、报告撰写与 PPT 制作）。
#### 7.2 项目开展历史节点（Milestones & Git Commit History）
* 第一阶段：文献阅读、亚稳态理论学习与 FIFO 深度计算。
* 第二阶段：Verilog 硬件核心代码编写与基于简单 Testbench 的波形调试。
* 第三阶段：SV 多用例覆盖率验证平台构建与 C++ 算法模型联调。
* 第四阶段：UVM 验证框架搭建与功能拓展测试。
* 第五阶段：项目汇总、报告撰写与成果答辩准备。

---

### 八、 总结
* 设计任务达成度自我评估。
* 项目中跨时钟域调试心得、EDA 工具（VCS, ModelSim, Verdi 等）应用反思。
* 对未来更高吞吐率或变位宽异步 FIFO 设计的拓展展望。

---

### 九、 参考文献
1. Clifford E. Cummings. *Simulation and Synthesis Techniques for Asynchronous FIFO Design*. SNUG 2002.
2. Clifford E. Cummings. *Synthesis and Scripting Techniques for Designing Multi-Asynchronous Clock Designs*. SNUG 2001.
3. Putta Satish. *Calculation of FIFO Depth - Made Easy*.
4. Paradigm Works Inc. *Crossing the Abyss: Asynchronous Signals in a Synchronous World*.