# EDA Groupwork: Asynchronous FIFO Design & UVM Verification

[![Platform](https://img.shields.io/badge/Platform-Linux-blue.svg)]()
[![Language](https://img.shields.io/badge/Language-SystemVerilog%20%7C%20UVM-orange.svg)]()

This repository contains the EDA groupwork project focusing on the design and verification of a highly reliable **Asynchronous FIFO**. The project integrates a parameterizable RTL design with a robust UVM (Universal Verification Methodology) testbench to achieve comprehensive functional and code coverage.

---

## 📂 Repository Directory Structure

Below is the directory structure of this repository.

```text
eda-groupwork
├── doc/                     # Project-level global documentation
├── prj_src/                 # Source code directory
│   ├── design_rv1_tv7/      # Current active workspace (Release v1, Test v7)
│   └── history_design/      # Historical versions prior to the first official release
│       ├── design_v0/
│       ├── design_v1/
│       ├── design_v2/
│       ├── design_v3/
│       ├── design_v4/
│       ├── design_v5/
│       ├── design_v6/
│       └── design_v7/
├── .gitignore               # Git ignore configuration
└── README.md                # Project main README (This file)
```

### 🔍 Project Workspace Example (`design_rv1_tv7/FIFO`)

Our active design directory contains dedicated folders for RTL, UVM Verification, Workspaces, and Detailed Documentation:

```text
design_rv1_tv7/FIFO
├── doc/                             # Technical documentation and guides
│   ├── COVERAGE_PATCH.md            # Details of patch tests designed for specific coverage holes
│   ├── COVERAGE_PATCH_QUICK_REF.md  # Quick reference for coverage patch tests
│   ├── RTL_ANALYSIS.md              # In-depth RTL architecture analysis
│   ├── SIM.md                       # Quick Start Guide to run simulation
│   ├── TEST_SUITE.md                # List of test cases and verification plan
│   ├── TEST_TUTORIAL.md             # Tutorial for adding customized tests (slightly outdated)
│   └── UVM_ANALYSIS.md              # In-depth UVM environment analysis (slightly outdated)
├── rtl_src/                         # Hardware Design (SystemVerilog RTL)
│   ├── async_fifo_top.sv            # Top module of the asynchronous FIFO
│   ├── dual_port_ram.sv             # Dual-port RAM for data storage
│   ├── fifo_cfg_pkg.sv              # FIFO hardware configuration package
│   ├── rptr.sv                      # Read pointer & empty logic generator
│   ├── sync_gray.sv                 # Gray code multi-stage synchronizer
│   └── wptr.sv                      # Write pointer & full logic generator
├── uvm_src/                         # UVM Verification Environment
│   ├── fifo_cfg_pkg.sv              # Verification configuration parameters
│   ├── fifo_cov_listener.sv         # Functional coverage collector (subscriber)
│   ├── fifo_env.sv                  # UVM Environment class
│   ├── fifo_env_pkg.sv              # UVM Package importing all components
│   ├── fifo_if.sv                   # SystemVerilog Interface for FIFO signals
│   ├── fifo_read_agent.sv           # Read Agent (Monitor + Driver + Sequencer)
│   ├── fifo_scoreboard.sv           # Scoreboard for self-checking data integrity
│   ├── fifo_sequence.sv             # Verification stimulus sequences
│   ├── fifo_test.sv                 # Base and derived testcases
│   ├── fifo_write_agent.sv          # Write Agent (Monitor + Driver + Sequencer)
│   └── tb_top.sv                    # Verification Top-level Module
└── uvm_work/                        # Simulation Workspace
    ├── urgReport/                   # Example of generated coverage report (not tracked by Git)
    ├── filelist                     # Compiler file compilation list (DO NOT DELETE)
    └── Makefile                     # Simulation control script (DO NOT DELETE)
```

---

## 🏷️ Version Control Naming Convention

We implement a strict naming convention to manage our development lifecycle:
* **`rv` (Release Version):** Refers to the official stable release version.
* **`tv` (Test/Developer Version):** Refers to the internal development/testing iteration.
* **`design_rv1_tv7`**: This directory represents **Release Version 1**, built on top of the **Test Version 7** development branch. It represents our first major official milestone.
* **`history_design/`**: Contains historical intermediate versions (`design_v0` to `design_v7`) developed prior to the first official release.

---

## 🚀 Quick Start (Simulation & Verification)

To compile the design and run the verification testbench:

1. Navigate to the simulation workspace:
   ```bash
   cd prj_src/design_rv1_tv7/FIFO/uvm_work
   ```
2. Run the default simulation target using the provided Makefile:
   ```bash
   make run
   ```
3. To view the coverage reports or run specific testcases, please refer directly to the internal guide:
   👉 **[Detailed Simulation Guide](prj_src/design_rv1_tv7/FIFO/doc/SIM.md)**

---

## 📝 Documentations Index

We maintain comprehensive documentation for developers and reviewers:

| Document | Description | Status |
| :--- | :--- | :--- |
| [RTL Analysis](prj_src/design_rv1_tv7/FIFO/doc/RTL_ANALYSIS.md) | In-depth breakdown of asynchronous FIFO logic, Gray code, and synchronizers. | Up to Date |
| [UVM Architecture](prj_src/design_rv1_tv7/FIFO/doc/UVM_ANALYSIS.md) | Structural details of our UVM verification environment and agents. | Legacy (Usable) |
| [Test Suite Info](prj_src/design_rv1_tv7/FIFO/doc/TEST_SUITE.md) | Details of existing test cases and functional coverage targets. | Up to Date |
| [Coverage Patching Guide](prj_src/design_rv1_tv7/FIFO/doc/COVERAGE_PATCH.md) | Documentation on handling edge-case coverage holes using specialized patches. | Up to Date |
| [Adding Custom Tests](prj_src/design_rv1_tv7/FIFO/doc/TEST_TUTORIAL.md) | Step-by-step instructions to write and integrate your own test cases. | Legacy (Usable) |

---
---

# EDA 期末大作业: 异步 FIFO 设计与 UVM 验证项目

[![Platform](https://img.shields.io/badge/Platform-Linux-blue.svg)]()
[![Language](https://img.shields.io/badge/Language-SystemVerilog%20%7C%20UVM-orange.svg)]()

本仓库为 EDA 期末大作业项目，主要内容为一个高可靠性的 **异步 FIFO** 的设计与验证。项目结合了参数化的 RTL 设计以及功能完备的 UVM (通用验证方法学) 验证平台，以达到极高的功能覆盖率和代码覆盖率。

---

## 📂 仓库目录结构

本项目的整体目录结构如下：

```text
eda-groupwork
├── doc/                     # 项目全局文档
├── prj_src/                 # 工程源码目录
│   ├── design_rv1_tv7/      # 当前主工作区 (发布版本 v1, 开发者版本 v7)
│   └── history_design/      # 第一次正式发布前的历史版本
│       ├── design_v0/
│       ├── design_v1/
│       ├── design_v2/
│       ├── design_v3/
│       ├── design_v4/
│       ├── design_v5/
│       ├── design_v6/
│       └── design_v7/
├── .gitignore               # Git 忽略文件配置
└── README.md                # 项目主 README (本文档)
```

### 🔍 工作区示例目录说明 (`design_rv1_tv7/FIFO`)

当前最新的工作区目录划分了明确的 RTL 设计、UVM 验证平台、运行环境以及技术文档：

```text
design_rv1_tv7/FIFO
├── doc/                             # 技术文档与指南
│   ├── COVERAGE_PATCH.md            # 针对特定覆盖率缺陷设计的两个修补测试详细描述
│   ├── COVERAGE_PATCH_QUICK_REF.md  # 覆盖率修补测试快速参考
│   ├── RTL_ANALYSIS.md              # RTL 设计详细分析
│   ├── SIM.md                       # 仿真运行快速开始指南
│   ├── TEST_SUITE.md                # 测试用例集与验证计划
│   ├── TEST_TUTORIAL.md             # 自定义测试用例添加指南 (略微过期，但不影响使用)
│   └── UVM_ANALYSIS.md              # UVM 验证平台设计详细分析 (略微过期，但不影响使用)
├── rtl_src/                         # 硬件设计 (SystemVerilog RTL)
│   ├── async_fifo_top.sv            # 异步 FIFO 顶层模块
│   ├── dual_port_ram.sv             # 用于存储数据的双口 RAM
│   ├── fifo_cfg_pkg.sv              # FIFO 硬件配置参数包
│   ├── rptr.sv                      # 读指针与空信号产生逻辑
│   ├── sync_gray.sv                 # 格雷码多级同步器
│   └── wptr.sv                      # 写指针与满信号产生逻辑
├── uvm_src/                         # UVM 验证环境
│   ├── fifo_cfg_pkg.sv              # 验证配置参数
│   ├── fifo_cov_listener.sv         # 功能覆盖率收集器 (Subscriber)
│   ├── fifo_env.sv                  # UVM 验证环境类
│   ├── fifo_env_pkg.sv              # 导入所有组件的 UVM 包
│   ├── fifo_if.sv                   # 接口文件
│   ├── fifo_read_agent.sv           # 读通道 Agent (Monitor + Driver + Sequencer)
│   ├── fifo_scoreboard.sv           # 用于数据自比对的比对黄金模型 (Scoreboard)
│   ├── fifo_sequence.sv             # 验证激励序列
│   ├── fifo_test.sv                 # 基础测试与派生测试用例
│   ├── fifo_write_agent.sv          # 写通道 Agent (Monitor + Driver + Sequencer)
│   └── tb_top.sv                    # 验证平台顶层模块
└── uvm_work/                        # 仿真运行工作区
    ├── urgReport/                   # 导出的覆盖率报告示例 (Git已忽略，可随时删除)
    ├── filelist                     # 编译路径文件列表 (切勿删除)
    └── Makefile                     # 自动化仿真脚本 (切勿删除)
```

---

## 🏷️ 版本控制与命名规范

本项目采用严格的版本命名规范来管理开发周期：
* **`rv` (Release Version):** 正式发布版本。
* **`tv` (Test/Developer Version):** 内部测试及开发迭代版本。
* **`design_rv1_tv7`**: 意为**第1次正式发布版本**，它基于**第7个开发测试版本**优化而来。这是我们项目的第一个重要里程碑。
* **`history_design/`**: 存放了正式发布前的所有历史演进版本（`design_v0` 至 `design_v7`），记录了项目的迭代过程。

---

## 🚀 快速开始 (仿真与验证)

若要编译设计并运行验证平台，请按以下步骤操作：

1. 进入仿真工作区：
   ```bash
   cd prj_src/design_rv1_tv7/FIFO/uvm_work
   ```
2. 使用 Makefile 运行默认仿真目标：
   ```bash
   make run_all
   ```
3. 若需运行特定测试用例或查看覆盖率报告，请直接参考仿真指南：
   👉 **[仿真运行快速开始指南 (SIM.md)](prj_src/design_rv1_tv7/FIFO/doc/SIM.md)**

---

## 📝 文档索引

我们为开发者和评审老师准备了详尽的文档支持：

| 文档名称 | 内容描述 | 状态更新 |
| :--- | :--- | :--- |
| [RTL 设计分析](prj_src/design_rv1_tv7/FIFO/doc/RTL_ANALYSIS.md) | 异步 FIFO 核心逻辑、格雷码同步及空满判断逻辑的详细拆解。 | 最新 |
| [UVM 平台架构](prj_src/design_rv1_tv7/FIFO/doc/UVM_ANALYSIS.md) | UVM 验证平台的结构关系、组件设计与 Agent 划分。 | 略微过期 (仍具参考价值) |
| [测试用例集说明](prj_src/design_rv1_tv7/FIFO/doc/TEST_SUITE.md) | 已实现的测试用例列表与功能验证计划。 | 最新 |
| [覆盖率修补说明](prj_src/design_rv1_tv7/FIFO/doc/COVERAGE_PATCH.md) | 针对边界情况及难点覆盖率漏洞设计的特定修补测试说明。 | 最新 |
| [添加自定义测试](prj_src/design_rv1_tv7/FIFO/doc/TEST_TUTORIAL.md) | 如何编写并向现有验证平台中添加新的测试用例。 | 略微过期 (仍具参考价值) |

---

```txt
Signature of Kevin-Quinn-blackCat, one of the developers(4 UVM)
                 ░▒▒▒░           ░▒▒▒░            
                ▒▒░░░▒▒▒       ░▒▒░░░▒▒           
               ░▒░░░░░░▒▒     ▒▒░░░░░░▒▒          
              ░▒░░░░░░░░▒▒░░▒▒▒░░░░░░░░▒░         
              ▒▒░░░░░░░░░░▒░░░░░░░░░░░░▒▒         
             ░▒░░░░░░░░░░░░░░░░░░░░░░░░░▒░        
             ░▒░░░░░░░░░░░░░░░░░░░░░░░░░▒▒        
          ▒▒▒▒▒░░░░░░░  ░░░░░░░  ░░░░░░░▒▒        
       ▒▒▒░░░▒▒░░░░░░░  ░░░░░░░  ░░░░░░░▒▒        
     ░▒▒░░░░░▒▒░░░░░░░  ░░░░░░░  ░░░░░░░▒░        
     ░▒░░░░░░░▒▒░░▒░▒░░░░░░░░░░░░░░▒░▒░▒▒         
     ░▒░░░░░░░░▒▒░░░░░░░░░░░░░░░░░░░░░░▒░         
      ░▒▒▒░▒▒▒▒░░▒▒▒░░░░░░░░░░░░░░░░▒▒░           
        ░░▒░░     ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░             
 ____  __.          .__         ________        .__               
|    |/ _|_______  _|__| ____   \_____  \  __ __|__| ____   ____  
|      <_/ __ \  \/ /  |/    \   /  / \  \|  |  \  |/    \ /    \ 
|    |  \  ___/\   /|  |   |  \ /   \_/.  \  |  /  |   |  \   |  \
|____|__ \___  >\_/ |__|___|  / \_____\ \_/____/|__|___|  /___|  /
        \/   \/             \/         \__>             \/     \/ 
    ___                                                                       
  /'___\        __                       /'\_/`\                              
 /\ \__/  _ __ /\_\     __     _ __     /\      \     __    ___   __  __  __  
 \ \ ,__\/\`'__\/\ \  /'__`\  /\`'__\   \ \ \__\ \  /'__`\ / __`\/\ \/\ \/\ \ 
  \ \ \_/\ \ \/ \ \ \/\ \L\.\_\ \ \/     \ \ \_/\ \/\  __//\ \L\ \ \ \_/ \_/ \
   \ \_\  \ \_\  \ \_\ \__/.\_\\ \_\      \ \_\\ \_\ \____\ \____/\ \___x___/'
    \/_/   \/_/   \/_/\/__/\/_/ \/_/       \/_/ \/_/\/____/\/___/  \/__//__/  
```