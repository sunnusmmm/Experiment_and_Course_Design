int a;
float b;
char c;
string d;
int e[2];
struct V{
    int a;
    char b;
    float c;
    string d;
};

int Max(int a,int b){
	if(a>b)
		return a;
	else
		return b;
}
int main(){//主函数
	int a,b,i;
	int v[2][3]=[[1,2,3],[4,5,6]];
	char c = 'Q';
	string s = "QAQ";
	a = 5;
	b = 6;
	i = Max(a,b);
	switch(a){	
        case 1:
            i++;
            i--;
            break;
        case 3:
            i+=1;
            i-=1;
            break;
        case 5:
            i*=1;
            i/=1;
            break;
        default:
            break;
    }
	for(a=1;a<10;a++){
        s.a=1;
        s.b = '1';
        s.c = 1.0;
        s.d = "nhy_test";
    }
	while(a <= 5){
		int m;
		a += 1;
        if(i = 5) break;
        if(i != 5) continue;
    }
    return 1;
}
int k;