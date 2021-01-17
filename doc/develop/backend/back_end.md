llvm后端

# 简介

把llvm IR转换为目标平台的代码或者汇编码。

# 基本流程

LLVM后端有一套流水线构架，指令经历多个阶段的处理：

LLVM IR →  SelectionDAG  →  MachineDAG  →  MachineInstr  → MCInst

1. IR首先被转为SelectionDAG（DAG指的是有向无环图）
2. SelectionDAG会被合法化（目标平台不支持的指令会被转换成合法的指
令），接着转为MachineDAG（基本上是针对后端的指令选择）
3. 对SelectionDAG的节点进行指令调度，由于CPU线性地执行指令序列，指令调度阶段分配指令的执行顺序，把DAG转换成线性的指令（MachineInstrs列表）
4. 

