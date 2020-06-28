flex lex.l
echo "FLEX运行完毕"
bison -d parser.y
echo "BISON运行完毕"
gcc -o parser lex.yy.c parser.tab.c ast.c
echo "GCC连接完毕"