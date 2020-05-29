#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
#include "parser.tab.h"
#define MAXLENGTH   200
#define DX 3*sizeof(int)          /*活动记录控制信息需要的单元数，这个根据实际系统调整*/

struct node {
	int kind;					//节点种类
	union {
		  char type_id[33];		//由标识符生成的叶结点
		  int type_int;			//由整常数生成的叶结点
		  float type_float;		//由浮点常数生成的叶结点
          char type_char;		//字符
          char type_string[33];	//字符串
	      };
    struct node *ptr[3];		//子树
    int type;					//标识表达式结点的类型
    int pos;					//语法单位所在位置行号
    };

struct node * mknode0(int kind,int pos);
struct node * mknode1(int kind,int pos, struct node *first);
struct node * mknode2(int kind,int pos, struct node *first, struct node *second);
struct node * mknode3(int kind,int pos, struct node *first, struct node *second,struct node *third);