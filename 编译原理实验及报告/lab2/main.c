int a,b,c;
float m,n;
char o;
int d[5];
float f[2];
char k[2];
int fibo(int a)
{
	int a;//测试重复定义
	g = 0;//调用未声明变量
	m();//测试对非函数名采用函数调用形式
    if (a == 1 || a == 2) return 1;
    return fibo(a-1)+fibo(a-2);
}

int main()
{
    int m,n,i;
	float g;
	g[1];//测试非数组变量采用下标变量的形式访问
    m = read();
    i = 1;
	i = 'a';//测试类型不匹配
	0 = 0;//测试赋值号左边不是左值表达式
	0++;//测试非左值表达式进行自增、自减运算
	0--;//测试非左值表达式进行自增、自减运算
	i = fibo(i);
	i = fibo(g);//测试参数类型不匹配
	i = fibo();//测试参数太少
	i = fibo(m,n);//测试参数太多
	break;//测试break语句不在循环语句或switch语句中
	continue;//测试continue语句不在循环语句中
    while(i<=m)
    {
        n = fibo(i);
        write(n);
        i=i+1;
		break;
		continue;
    }
    return g;//测试返回值类型不匹配
}
