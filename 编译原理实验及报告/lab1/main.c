int a;//声明int
float b;//声明float
char c;//声明char
int d[2];
/*
*main函数定义
*/
int main(){
	int a = 2;
	float b = 3.0;
	int i;
    int v[2][3]=[[1,2,3],[4,5,6]];
	/*
	*if-else语句测试
	*/
	if(a>b){
		a = b;
	}else{
		b = a;
	}
	/*
	*while循环语句测试
	*/
	while(a <= 5){
		int k = 0;
	}
	/*
	*for循环语句测试
	*/
	for(i = 1; i < 10; i++){
		if(i = 5) 
			break;
		else
			continue;		
	}
	/*
	*赋值语句测试
	*/
	a = a + b;
	a += 1;
	a -= b;
	a *= 1;
	a /= b;
	a %= 1;
	return 0;
}
