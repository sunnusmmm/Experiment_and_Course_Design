flex lex.l
echo "FLEX运行完毕"
bison -d -v parser.y
echo "BISON运行完毕"
gcc -o parser ast.c semantic.c parser.tab.c lex.yy.c
echo "GCC连接完毕"
./parser test.c
echo "语义检查、中间代码生成完成"