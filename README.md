# Simple Calculator

## 1. 开发环境

VSCode + CMake

## 2. 使用说明

### 2.1 运行

### 2.2 选择运算模式

计算器启动后需要选择一种运算模式。

目前共支持四种运算模式：

- 基本模式：简单运算表达式，支持加、减、乘、除、幂运算。
- 变量模式：含单变量的简单运算表达式，可以指定变量名称，支持对变量重复赋值计算。
- 多项式模式：计算单变量多项式，支持加、减、乘、导数运算。
- 向量模式：计算n维向量，支持加、减、内积、余弦相似度运算。

### 2.3 基本模式

直接输入四则运算表达式即可计算。（目前只支持不带空白符的字符串）

### 2.4 变量模式

输入变量名（目前只支持单个字符的变量名称）。输入带变量的表达式。可以给变量重复赋值，计算输出结果。

### 2.5 多项式模式

可以输入多个单变量多项式进行加、减、乘运算。输入的多项式需要以'x'作为变量名，项的系数和'x'之间需要用'*'连接（若不为1），指数和'x'之间需要用'^'连接（若不为1）。

输入的需要计算的多项式之间可以输入运算符（带提示），最后输入'='进行计算得出结果。

### 2.6 向量模式 

可以输入多个向量进行加、减、乘运算。输入的向量维度应该相同，先输入向量的维度，再输入n个元素。

输入的需要计算的向量之间可以输入运算符（带提示），最后输入'='进行计算得出结果。

### 2.7 输出说明

