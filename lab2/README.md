# lab2
> 计卓1701 张淇 U201714466

## Environment
MacOS\
flex : 2.5.35\
bison : 2.3\
clang : 11.0.0

## Build

```
To build and test the project :

% make

To compile a mini-C file:

%./parser <filename>

To compile a mini-C file and output the AST-tree in a new file:

%./parser <filename> > <output file>

To clean the project:

%make clean
```

test.c is the test file and out.txt is the output.

可以检查出的错误有

- 使用未定义的变量
- 调用未定义或未声明的函数
- 在同一作用域，名称的重复定义（如变量名、函数名、结构类型名以及结构体成员名等）
- 对非函数名采用函数调用形式
- 对函数名采用非函数调用形式访问
- 函数调用时参数个数不匹配，如实参表达式个数太多、或实参表达式个数太少
- 函数调用时实参和形参类型不匹配
- 对非数组变量采用下标变量的形式访问
- 数组变量的下标不是整型表达式
- 数组变量下标为负数
- 数组变量维数错误
- 对非结构变量采用成员选择运算符“.”
- 结构成员不存在
- 赋值号左边不是左值表达式
- 对非左值表达式进行自增、自减运算
- 对结构体变量进行自增、自减运算
- 类型不匹配
- 函数返回值类型与函数定义的返回值类型不匹配
- 函数没有返回语句
- break语句不在循环语句或switch语句中
- continue语句不在循环语句中

