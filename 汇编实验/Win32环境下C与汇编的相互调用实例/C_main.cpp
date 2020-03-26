//Please test this program in Debug Win32
#include "stdafx.h"
#include "stdio.h"

extern "C" long _cdecl asmTest(char *szMsg);
extern "C" long _cdecl sum(long a, long b);

int main(int argc, char *argv[])
{
	long i = asmTest("This is a message from main program\n"); //汇编程序调用sum(200,100),返回300
	_asm {
		mov  ecx, 100
		L1:		inc  i
				loop L1
	};
	printf("i = %ld \n", i);  //i = 400
	return 0;
}

long sum(long a, long b)
{
	return a + b;
}
