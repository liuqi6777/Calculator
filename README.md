# 可编程计算器

## 一、需求分析

1. 实现一个具有交互界面的计算器，可以完成不同的数据处理或计算要求。
2. 简单表达式运算，计算输出结果。
3. 带单变量的表达式运算，可以重复给出不同的变量值，并计算输出相应结果。
4. 任意同维度的两个向量运算，完成包括加法、减法、余弦相似度等计算，输出结果。
5. 一元多项式运算，完成包括加法、减法、乘法、导数(包括任意阶)等计算，输出结果。
6. 定义并运行简单函数。
7. 矩阵运算，包括加、减、乘、转制、特征值、行列式的值等矩阵基本运算，输出结果。

## 二、开发环境

本项目在 Windows 系统下开发使用 c++ 语言开发，使用 CMake 生成项目。

## 三、设计思路

考虑到简单表达式、单变量表达式、函数具有一定的相似性、在解析字符串的过程中也可以一定程度上复用代码，因此采用了继承的方式。而向量和矩阵的功能独立实现。最后将这些相对独立的功能统一集成到计算器类 ```Calculator``` 中。

## 四、用户手册

### 00 默认说明

1. 计算器中出现的文本提示遵循以下规则：

	- ```[INFO]```     表示提示信息，一般用于提示用户输入。
	- ```[ERROR]```   表示程序运行过程中遇到错误，可能为输入非法、运算非法等。
	- ```[RESULT]``` 表示输出运算的结果。

	样例中出现以上字样均为提示信息。 

2. 需要用户输入时，默认输入为一行，即以换行符作为结尾。

3. 输入中会默认跳过空格。

### 0 启动计算器

运行程序后，会出现 ```HELLO WORLD!``` 字样，计算器启动成功。

之后出现提示，需要输入 ```1-6``` 的数字，以选择计算器的运行模式。

### 1 基本模式

直接输入运算表达式即可计算。目前支持的二元运算符有 ```+```，```-```，```*```，```/```，```^```。

**样例：**

```
Input:
 (-18) * ((-0.52e1) + (2 * x -1)) ^ x + 8 / 2.3 + 2
 
Output:
[RESULT] The rusult is : 5.62226.
```

### 2 变量模式

1. 定义一个变量，输入变量名。

2. 输入带有变量的表达式。目前支持的二元运算符有 ```+```，```-```，```*```，```/```，```^```。
3. 输入变量的值
4. 输出结果。
5. 输入 ```q``` 退出变量模式，输入其他字符则重复 3 和 4 过程。

**样例：**

```
Input:
x
3+x
2

Output:
[RESULT] The rusult is : 5.
```

### 3 向量模式

1. 输入一个向量。向量以中括号作为开头和结尾，中间用 ```,``` 分隔，如 ```[1, 2, 3, 4]```。
2. 输入需要进行的运算。目前支持加法、减法、向量的点乘、余弦相似度。
3. 输入另一个向量。
4. 输出运算结果。

**样例：**

```
Input:
[1, 2, 3]
+
[2, 4, 6]

Output:
[RESULT] The result is [3,6,9].
```

### 4 多项式模式

1. 输入一个单变量多项式。多项式以 ```x``` 作为变量名，系数和变量之间用 ```*``` 分隔，变量和指数之间用 ```^``` 分隔，如系数或指数为 1 可以不输入。例如 ```x^5+3*x^2+4*x+2```。
2. 输入需要进行的运算。目前支持多项式的加法、减法、乘法、求导运算。
3. 输入另一个多项式（加减、乘法），或者一个整数（求导运算）。
4. 输出运算结果。

**样例：**

```
Input:
2*x^2+x-2
+
3*x^3-x+3

Output:
[RESULT] The result is : 3*x^3+2*x^2+1.
```

### 5 矩阵模式

1. 输入一个矩阵。矩阵以中括号作为开头和结尾，为行优先输入，以 ```,``` 作为行元素的分隔，```;``` 作为两行元素之间的分隔。例如 ```[1, 2, 3; 4, 5, 6]``` 表示一个 ```2x3``` 的矩阵。
2. 输入需要进行的运算。目前支持矩阵的加法、减法、矩阵乘法、转置、求特征值（向量）、求行列式、求逆矩阵等矩阵基本运算。
3. 输入另一个矩阵（加减、乘法），转置、求特征值（向量）、求行列式值则不需要。
4. 输出运算结果。

**样例：**

```
Input:
[1, 2, 3; 4, 5, 6]
*
[3, 1; 2, 0; 1, 0]

Output:
[RESULT] The result is :
14	28
1	4
```

### 6 函数模式

1. 输入 ```DEF function(variable)``` 定义一个函数。
2. 输入 ```RUN function(value)``` 运行之前定义过的函数。
3. 输入 ```q``` 退出函数模式，输入其他字符则重复 1 或 2 过程。
4. 支持同时定义多个函数（最多10个），并且可以运行之前定义的函数。
5. 支持在函数定义中调用之前定义过的函数。
6. 暂时不支持定义 ```f(x+1)``` 此类函数。

**样例**

```
Input:
DEF f(x)=x+1
DEF g(y)=(f(y))^2    
RUN g(2)

Ouput:
[RESULT] The result is 9.000000.
```

### 7 退出程序

在某种模式进行一系列输入和操作，并且输出结果后，程序会进行是否退出程序的提示。此时输入其他字符可以重新选择计算模式，输入 ```q``` 可以退出程序，屏幕上显示 ```BYE!``` 并退出。

## 五、单元测试

在本次实验中，实现了独立的单元测试部分，详细代码位于```test.cpp```文件中。采用宏定义的方式实现了对计算器的每一个功能的单元测试，并能够给出单元测试的通过率，以及使用 ```stderr``` 和 ```__LINE__``` ，能够具体定位到未通过测试的代码的行数。

将部分测试数据展示如下：

```c++
static void test_calculation()
{
    TEST_CALCULATION(0, "0");
    TEST_CALCULATION(3.33, "3.33");
    TEST_CALCULATION(1, "-3+4*2-2^2");
    TEST_CALCULATION(9, "2*4+1");
    TEST_CALCULATION(2, "3+(10-(4*2))*7-3*5");
    TEST_CALCULATION(1.5, "2.25/1.5");
    TEST_CALCULATION(1, "0.99999+0.000001*10");
}

static void test_variable_expression()
{
    TEST_VARIABLE_EXPRESSION(15, "3*(x+4)-2*x", "x", 3);
}

static void test_polynomial()
{
    TEST_POLYNOMIAL_OPER("3.000000*x^2+2.000000*x^1", "3*x^2", "2*x^1", '+');
    TEST_POLYNOMIAL_DIFF("6.000000*x^1+2.000000", "3*x^2+2*x^1", 1);
}
```

以上测试数据运算结果正确，和手动利用计算器的计算结果一致。

## 六、附录

### 1 源程序文件名清单：

```c++
/****************************************
 * calculation.h	-- 简单表达式功能单元
 * calculator.h		-- 集成多种功能的计算器
 * CMakeLists.txt	-- 项目工程文件
 * defines.h		-- 全程常量、类型、宏定义
 * expression.h		-- 基础表达式（虚基类）
 * function.h		-- 函数功能单元
 * main.h			-- 主程序文件
 * matrix.h			-- 矩阵功能单元
 * polynomial.h		-- 多项式功能单元
 * test.cpp			-- 单元测试 
 * vatiable.h		-- 变量表达式功能单元
 * vector.h			-- 向量功能单元
 ****************************************/
```

### 2 可改进部分 / TODO

由于本人完成作业的时间并不充裕，项目中还有许多可以完善或优化的地方，虽然以后可能不会完善了，但仍然列出如下：

- 总体
  - 感觉架构的设计并非很合理，存在很多缺陷。
  - 例如，本来想通过虚基类的方式，可以在查询历史运行时接受不同类型的运算。先不说最后并没有实现这个功能，在不同的子类接口和成员变量差距过大的情况下，这种方法是否可行、高效？在运行过程中是否还需要加一个对表达式类型的判断？
  - 向量和矩阵也并没有继承，而是独立实现（虽然修改成继承只需要一点点小小的改动）。

- 多项式
  - 支持运算后可以返回一个新的多项式的方式（目前实现为在原多项式上修改）。

- 函数部分

  - 优化（或重构）通过字符串替换的实现方式。
  - 将一些硬编码的代码重构。
  - 支持定义类似 ```f(x+1)``` 的函数。 
  - 将部分在计算器代码中实现的解析函数表达式的代码，移动到函数的实现代码中，使代码更加优雅。
  - （函数功能的实现真的很不优雅，但是也没办法了><）

- 计算器
  - 支持查询历史运算结果（查询上一次运算）。
  - 优化使用过程中的文字信息提示，使代码和输出的信息更加规范统一。
  - 优化用户进行非法输入和非法操作之后的行为。
- 单元测试部分
  - 目前并未给出很多单元测试的测试样例，可以多考虑些边界情况。
