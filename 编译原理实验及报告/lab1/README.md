# 编译原理实验

> 自定义语言名：Vector

### 实验一 ：词法语法分析器的设计与实现

- [x] 数据类型至少包括char类型、int类型和float类型，字符串；
- [x] 基本运算至少包括算术运算、比较运算、自增自减运算和复合赋值运算；
- [x] 控制语句至少包括**if语句、while语句和break、continue语句**（不要求goto语句），另外for、switch语句作为可选项；
- [x] **多维数组**。另外结构作为可选项；
- [x] 语言支持行注释与块注释，不要求支持编译预处理命令和多文件程序. 



### 文件说明

- lex.l：词法分析器

	>lex.yy.c: 通过Vector.l 得到的flex编译文件

- parser.y：语法分析器

	>paser.tab.c/parser.tab.h :BISON编译文件

-  node.h :节点属性定义

- ast.c:规范打印器

- mainc：测试文件

- paser:二进制执行文件

- auto.sh：unix自动执行脚本

