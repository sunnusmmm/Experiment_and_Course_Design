#include "node.h"
#include "parser.tab.h"
#define OFFSET 4


struct node * mknode0(int kind,int pos){
	struct node *T=(struct node *)calloc(sizeof(struct node),1);
	T->kind = kind;
    T->ptr[0] = NULL;
    T->ptr[1] = NULL;
    T->ptr[2] = NULL;
    T->pos = pos;
    return T;
}
struct node * mknode1(int kind,int pos, struct node *first){
	struct node *T=(struct node *)calloc(sizeof(struct node),1);
	T->kind = kind;
    T->ptr[0] = first;
    T->ptr[1] = NULL;
    T->ptr[2] = NULL;
    T->pos = pos;
    return T;
}
struct node * mknode2(int kind,int pos, struct node *first, struct node *second){
	struct node *T=(struct node *)calloc(sizeof(struct node),1);
	T->kind = kind;
    T->ptr[0] = first;
    T->ptr[1] = second;
    T->ptr[2] = NULL;
    T->pos = pos;
    return T;
}
struct node * mknode3(int kind,int pos, struct node *first, struct node *second,struct node *third){
struct node *T=(struct node *)calloc(sizeof(struct node),1);
	T->kind = kind;
    T->ptr[0] = first;
    T->ptr[1] = second;
    T->ptr[2] = third;
    T->pos = pos;
    return T;
}

void displayRoot(){
    printf("语法树:\n");
}
void display(struct node *T,int indent)
{//对抽象语法树的先根遍历
  int i=1;
  struct node *T0;
  if (T)
	{
    switch (T->kind)
    {
	case EXT_DEF_LIST:  
        display(T->ptr[0],indent);    //显示该外部定义（外部变量和函数）列表中的第一个
        display(T->ptr[1],indent);    //显示该外部定义列表中的其它外部定义
        break;
	case EXT_VAR_DEF:   
        printf("%*c外部变量定义:\n",indent,' ');
        display(T->ptr[0],indent+OFFSET);        //显示外部变量类型
        printf("%*c变量名:\n",indent+OFFSET,' ');
        display(T->ptr[1],indent+OFFSET*2);        //显示变量列表
        break;
    case TYPE:         
        printf("%*c类型: %s\n",indent,' ',T->type_id);
        break;
    case EXT_DEC_LIST:  
        display(T->ptr[0],indent);     //依次显示外部变量名，
        display(T->ptr[1],indent);     //后续还有相同的，仅显示语法树此处理代码可以和类似代码合并
        break;
	case FUNC_DEF:      
        printf("%*c函数定义:\n",indent,' ');
		display(T->ptr[1],indent+OFFSET);      //显示函数名和参数
        display(T->ptr[0],indent+OFFSET);      //显示函数返回类型
        display(T->ptr[2],indent+OFFSET);      //显示函数体
        break;
	case FUNC_DEC:      
        printf("%*c函数名:%s\n",indent,' ',T->type_id);
        if (T->ptr[0])
        {
            printf("%*c函数形参:\n",indent,' ');
            display(T->ptr[0],indent+OFFSET);  //显示函数参数列表
        }
        else printf("%*c无参函数\n",indent+OFFSET,' ');
        break;
	case PARAM_LIST:    
        display(T->ptr[0],indent);     //依次显示全部参数类型和名称，
        display(T->ptr[1],indent);
        break;
	case PARAM_DEC:     
        printf("%*c类型:%s, 参数名:%s\n",indent,' ',T->ptr[0]->type==INT?"int":"float",T->ptr[1]->type_id);
        break;
	case EXP_STMT:      
        printf("%*c表达式语句:\n",indent,' ');
        display(T->ptr[0],indent+OFFSET);
        break;
	case RETURN:        
        printf("%*c返回语句:\n",indent,' ');
        display(T->ptr[0],indent+OFFSET);
        break;
	case COMP_STM:      
        printf("%*c复合语句:\n",indent,' ');
        printf("%*c复合语句的变量定义部分:\n",indent+OFFSET,' ');
        display(T->ptr[0],indent+OFFSET*2);      //显示定义部分
        printf("%*c复合语句的语句部分:\n",indent+OFFSET,' ');
        display(T->ptr[1],indent+OFFSET*2);      //显示语句部分
        break;
	case STM_LIST:      
        display(T->ptr[0],indent);      //显示第一条语句
        display(T->ptr[1],indent);        //显示剩下语句
        break;
	case WHILE:         
        printf("%*cWHILE(语句)(%d):\n",indent,' ',indent);
        printf("%*c循环条件:\n",indent+OFFSET,' ');
        display(T->ptr[0],indent+OFFSET*2);      //显示循环条件
        printf("%*c循环体:\n",indent+OFFSET,' ');
        display(T->ptr[1],indent+OFFSET*2);      //显示循环体
        break;
	case IF_THEN:       
        printf("%*c条件语句(IF_THEN):\n",indent,' ');
        printf("%*c条件:\n",indent+OFFSET,' ');
        display(T->ptr[0],indent+OFFSET*2);      //显示条件
        printf("%*cIF子句:\n",indent+OFFSET,' ');
        display(T->ptr[1],indent+OFFSET*2);      //显示if子句
        break;
	case IF_THEN_ELSE:  
        printf("%*c条件语句(IF_THEN_ELSE):\n",indent,' ');
        printf("%*c条件:\n",indent+OFFSET,' ');
        display(T->ptr[0],indent+OFFSET*2);      //显示条件
        printf("%*cIF子句:\n",indent+OFFSET,' ');
        display(T->ptr[1],indent+OFFSET*2);      //显示if子句
        printf("%*cELSE子句:\n",indent+OFFSET,' ');
        display(T->ptr[2],indent+OFFSET*2);      //显示else子句
        break;
    case DEF_LIST:     
        display(T->ptr[0],indent);    //显示该局部变量定义列表中的第一个
        display(T->ptr[1],indent);    //显示其它局部变量定义
        break;
    case VAR_DEF:       
        printf("%*c局部变量定义:\n",indent,' ');
        display(T->ptr[0],indent+OFFSET);   //显示变量类型
        display(T->ptr[1],indent+OFFSET);   //显示该定义的全部变量名
        break;
    case DEC_LIST:      
        printf("%*c变量名:\n",indent,' ');
        T0=T;
        while (T0) {
            if (T0->ptr[0]->kind==ID){
                 printf("%*cID:%s\n",indent+OFFSET*2,' ',T0->ptr[0]->type_id);
            }
            else if (T0->ptr[0]->kind==ASSIGNOP)
            {
                if(T0->ptr[0]->ptr[0]->kind == ARRAY_LIST) display(T0->ptr[0]->ptr[0],indent); //var_dec assignop exp的情况
                printf("%*c %s ASSIGNOP\n ",indent+OFFSET*2,' ',T0->ptr[0]->ptr[0]->type_id);
                display(T0->ptr[0]->ptr[1],indent+strlen(T0->ptr[0]->ptr[0]->type_id)+7);        //显示初始化表达式
                
            }
            else if(T0->ptr[0]->kind==ARRAY_LIST){
                printf("%*c 数组%s\n",indent+OFFSET*2,' ',T0->ptr[0]->type_id);//var $$=$1
            }

            T0=T0->ptr[1];
        }
        break;
    case ID:	        
        printf("%*cID: %s\n",indent,' ',T->type_id);
        break;
    case CONTINUE:
	    printf("%*c CONTINUE语句\n", indent, ' ');
	    break;
	case BREAK:
	    printf("%*c BREAK语句\n", indent, ' ');
	    break;
    //数组的打印
    case ARRAY_LIST:
        printf("%*c 数组%s\n",indent,' ',T->type_id);
        break;
	case INT:	     
        printf("%*cINT:%d\n",indent,' ',T->type_int);
        break;
	case FLOAT:	        
        printf("%*cFLAOT:%f\n",indent,' ',T->type_float);
        break;
    case CHAR:
        printf("%*cCHAR: %c\n", indent, ' ', T->type_char);
        break;
    case STRING:
        printf("%*cSTRING: %s\n", indent, ' ', T->type_id);//STRING
        break;
	case ASSIGNOP:
        T0=T;
        if(T0->ptr[0]->kind==ARRAY_LIST){
                printf("%*c数组%s\n",indent+OFFSET*2,' ',T0->ptr[0]->type_id);
            }
			
    case ASSIGNOP_MINUS:
    case ASSIGNOP_PLUS:
    case ASSIGNOP_DIV:
    case ASSIGNOP_STAR:
    case ASSIGNOP_MOD:
	case AND:
	case OR:
	case RELOP:
	case PLUS:
    case AUTOPLUS:
    case AUTOMINUS:
	case MINUS:
	case STAR:
	case DIV:
    case MOD:
        printf("%*c%s\n",indent,' ',T->type_id);
        display(T->ptr[0],indent+OFFSET);
        display(T->ptr[1],indent+OFFSET);
        break;
	case NOT:
	case UMINUS:    
        printf("%*c%s\n",indent,' ',T->type_id);
        display(T->ptr[0],indent+OFFSET);
        break;
    case FUNC_CALL: 
        printf("%*c函数调用:\n",indent,' ');
        printf("%*c函数名:%s\n",indent+OFFSET,' ',T->type_id);
        display(T->ptr[0],indent+OFFSET);
        break;
	case ARGS:      
        i=1;
        while (T) {  //ARGS表示实际参数表达式序列结点，其第一棵子树为其一个实际参数表达式，第二棵子树为剩下的
            struct node *T0=T->ptr[0];
            printf("%*c第%d个:\n",indent,' ',i++);
            display(T0,indent+OFFSET);
            T=T->ptr[1];
        }
//      printf("%*c第%d个实际参数表达式:\n",indent,' ',i);
  //    display(T,indent+OFFSET);
        printf("\n");
        break;
    case SWITCH:
        printf("%*cSwitch语句(%d):\n", indent, ' ',indent);
        printf("%*c判断对象:\n", indent+OFFSET, ' ');
        display(T->ptr[0], indent+OFFSET*2);
        display(T->ptr[1],indent+OFFSET*2);
        break;
    case CASE_STMT_LIST:
        display(T->ptr[0], indent);
        display(T->ptr[1], indent);
        break;
    case CASE_STMT:
        printf("%*cCase语句:\n", indent, ' ');
        printf("%*c匹配值:\n", indent+OFFSET, ' ');
        if (T->type == CHAR){
            printf("%*cCHAR:'%c'\n", indent+OFFSET*2, ' ', T->type_char);
        } else if (T->type == INT) {
            printf("%*cINT:%d\n", indent+OFFSET*2, ' ', T->type_int);
        }
        printf("%*cCase语句块:\n", indent+OFFSET, ' ');
        display(T->ptr[0], indent+OFFSET*2);
        break;
    case DEFAULT_STMT:
        printf("%*cDefualt语句:\n", indent, ' ');
        printf("%*cDefault语句块:\n", indent+OFFSET, ' ');
        display(T->ptr[0], indent+OFFSET*2);
        break;
    case STRUCT_NEW:
        printf("%*c定义结构体:\n", indent, ' ');
        display(T->ptr[0], indent+OFFSET*2);
        printf("%*c结构体成员:\n", indent, ' ');
        display(T->ptr[1], indent+OFFSET*2);
        break;
    case STRUCT_DEC:
        printf("%*c新建结构体变量:\n", indent, ' ');
        printf("%*c   变量名:%s\n", indent, ' ', T->type_id);
        break;
    case EXT_STRUCT_DEC:
        printf("%*c外部结构体:\n", indent, ' ');
        display(T->ptr[0], indent+OFFSET);
        break;
    case STRUCT_VISIT:
        printf("%*c访问对象:\n", indent, ' ');
        display(T->ptr[0], indent+OFFSET);
        printf("%*c目标元素:\n", indent, ' ');
        printf("%*cID: %s\n",indent+OFFSET, ' ', T->type_id);
        break;
    case FOR:
        printf("%*cFor(循环)(%d):\n", indent, ' ',indent);
        printf("%*c循环条件:\n", indent + OFFSET, ' ');
        display(T->ptr[0], indent + OFFSET*2); //显示循环条件
        printf("%*c循环体:\n", indent + OFFSET, ' ');
        display(T->ptr[1], indent + OFFSET*2); //显示循环体
        break;
    case FOR_DEC:
		printf("%*c初始化语句:\n", indent, ' ');
        display(T->ptr[0], indent + OFFSET);
		printf("%*c条件判断语句:\n", indent, ' ');
        display(T->ptr[1], indent + OFFSET);
		printf("%*c循环操作语句:\n", indent, ' ');
        display(T->ptr[2], indent + OFFSET);
        break;
    default:
        printf("未找到该类型\n");
        break;
        }
    }
}