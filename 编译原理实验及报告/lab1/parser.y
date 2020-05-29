%error-verbose
%locations
//声明部分
%{
    #include "stdio.h"
    #include "math.h"
    #include "string.h"
    #include "node.h"
    extern int yylineno;
    extern char *yytext;
    extern FILE *yyin;
    int yylex();
    void yyerror(const char* fmt, ...);
    void display(struct node *,int);
    void displayRoot();
%} 

//辅助定义部分
%union {
	int    type_int;
    char   type_char;
	float  type_float;
	char   type_id[32];
	struct node *ptr;
};

//  %type 定义非终结符的语义值类型
%type <ptr> program ExtDefList ExtDef  Specifier ExtDecList FuncDec CompSt VarList VarDec ParamDec Stmt StmList DefList Def DecList Dec Exp Args 
%type <ptr> CaseStmtList CaseStmt DefaultStmt Struct_dec StructName ForDec Arraylist

//% token 定义终结符的语义值类型
%token <type_char> CHAR
%token <type_int> INT              /*指定INT的语义值是type_int，有词法分析得到的数值*/
%token <type_id> ID STRING RELOP TYPE    /*指定ID,RELOP,TYPE,STRING 的语义值是type_id，有词法分析得到的标识符字符串*/
%token <type_float> FLOAT          /*指定FLOAT的语义值是type_float，有词法分析得到的标识符字符串*/
%token STRUCT RETURN FOR SWITCH CASE COLON DEFAULT
%token STRUCT_VISIT STRUCT_NEW STRUCT_DEC EXT_STRUCT_DEC/*结构体*/
%token CASE_STMT CASE_STMT_LIST DEFAULT_STMT
%token FOR_DEC FOR_EXP1 FOR_EXP2 FOR_EXP3

%token DPLUS LP RP LC RC LB RB SEMI COMMA DOT      /*用bison对该文件编译时，带参数-d，生成的.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码*/
%token PLUS MINUS STAR DIV MOD ASSIGNOP_MOD ASSIGNOP ASSIGNOP_MINUS ASSIGNOP_PLUS ASSIGNOP_DIV ASSIGNOP_STAR AND OR NOT AUTOPLUS AUTOMINUS IF ELSE WHILE BREAK CONTINUE 
/*以下为接在上述token后依次编码的枚举常量，作为AST结点类型标记*/
%token EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF FUNC_DEC EXT_DEC_LIST PARAM_LIST PARAM_DEC VAR_DEF DEC_LIST DEF_LIST COMP_STM STM_LIST EXP_STMT IF_THEN IF_THEN_ELSE
%token FUNC_CALL ARGS FUNCTION PARAM ARG
%token ARRAY_LIST //加入Array

//优先级
%left ASSIGNOP ASSIGNOP_MINUS ASSIGNOP_PLUS ASSIGNOP_DIV ASSIGNOP_STAR ASSIGNOP_MOD 
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV MOD
%left AUTOPLUS AUTOMINUS
%right UMINUS NOT DPLUS DMINUS
%left LB RB LP RP DOT

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

//规则定义部分
%%
program: ExtDefList {displayRoot();display($1,0);}     //显示语法树,语义分析
         ; 
ExtDefList: {$$=NULL;}
          | ExtDef ExtDefList {$$=mknode2(EXT_DEF_LIST,yylineno,$1,$2);}   //每一个EXTDEFLIST的结点，其第1棵子树对应一个外部变量声明或函数
          ;  
ExtDef:   Specifier ExtDecList SEMI   {$$=mknode2(EXT_VAR_DEF,yylineno,$1,$2);}   //该结点对应一个外部变量声明
         |Specifier FuncDec CompSt    {$$=mknode3(FUNC_DEF,yylineno,$1,$2,$3);}         //该结点对应一个函数定义
         |Struct_dec SEMI{$$=mknode1(EXT_STRUCT_DEC, yylineno,$1);}
         | error SEMI   {$$=NULL;}
         ;
Specifier:  TYPE    {$$=mknode0(TYPE,yylineno);strcpy($$->type_id,$1);$$->type=!strcmp($1,"int")?INT:FLOAT;}   
           ;      
ExtDecList:  VarDec      {$$=$1;}       /*每一个EXT_DECLIST的结点，其第一棵子树对应一个变量名(ID类型的结点),第二棵子树对应剩下的外部变量名*/
           | VarDec COMMA ExtDecList {$$=mknode2(EXT_DEC_LIST,yylineno,$1,$3);}
           ;  
VarDec:  ID          {$$=mknode0(ID,yylineno);strcpy($$->type_id,$1);} |   //ID结点，标识符符号串存放结点的type_id
         ID Arraylist  {$$=mknode1(ARRAY_LIST,yylineno,$2);strcpy($$->type_id,$1);} 
         ;

Arraylist:  LB INT RB           {$$=mknode0(ARRAY_LIST,yylineno);$$->type_int=$2;}
            | LB INT RB Arraylist       {$$=mknode1(ARRAY_LIST,yylineno,$4);$$->type_int=$2;}
        ;
		
FuncDec: ID LP VarList RP   {$$=mknode1(FUNC_DEC,yylineno,$3);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
	|ID LP  RP   {$$=mknode0(FUNC_DEC,yylineno);strcpy($$->type_id,$1);$$->ptr[0]=NULL;}//函数名存放在$$->type_id
        ;  
VarList: ParamDec  {$$=mknode1(PARAM_LIST,yylineno,$1);}
        | ParamDec COMMA  VarList  {$$=mknode2(PARAM_LIST,yylineno,$1,$3);}
        ;
ParamDec: Specifier VarDec         {$$=mknode2(PARAM_DEC,yylineno,$1,$2);}
         ;

CompSt: LC DefList StmList RC    {$$=mknode2(COMP_STM,yylineno,$2,$3);}
       ;
StmList: {$$=NULL; }  
        | Stmt StmList  {$$=mknode2(STM_LIST,yylineno,$1,$2);}
        ;
Stmt:   Exp SEMI    								{$$=mknode1(EXP_STMT,yylineno,$1);}
      | CompSt      								{$$=$1;}      //复合语句结点直接为语句结点，不再生成新的结点
      | RETURN Exp SEMI   							{$$=mknode1(RETURN,yylineno,$2);}
      | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   	{$$=mknode2(IF_THEN,yylineno,$3,$5);}
      | IF LP Exp RP Stmt ELSE Stmt   				{$$=mknode3(IF_THEN_ELSE,yylineno,$3,$5,$7);}
      | WHILE LP Exp RP Stmt 						{$$=mknode2(WHILE,yylineno,$3,$5);}
      | CONTINUE SEMI								{ $$ = mknode0(CONTINUE, yylineno); strcpy($$->type_id, "CONTINUE"); }
      | BREAK	SEMI								{ $$ = mknode0( BREAK, yylineno); strcpy($$->type_id, "BREAK"); }
      | FOR LP ForDec RP Stmt 						{$$=mknode2(FOR,yylineno,$3,$5);} //FOR循环识别 for(FORDEC):Stmt
      | SWITCH LP Exp RP LC CaseStmtList RC 		{$$=mknode2(SWITCH, yylineno, $3, $6);} //SWITCH识别
      ;
//用于识别Default:*****
DefaultStmt: DEFAULT COLON StmList {$$=mknode1( DEFAULT_STMT, yylineno, $3);}
        ;

//识别Case
CaseStmt: CASE INT COLON StmList 	{$$=mknode1(CASE_STMT, yylineno, $4);$$->type_int=$2;$$->type=INT;}
        | CASE CHAR COLON StmList	{$$=mknode1(CASE_STMT, yylineno, $4);$$->type_char=$2;$$->type=CHAR;}
        ;

//用于识别连续多个case+Default(DEFAULT为终结符)
CaseStmtList: 
          {$$=NULL;}
        | CaseStmt CaseStmtList {$$=mknode2(CASE_STMT_LIST, yylineno, $1, $2);}
        | DefaultStmt 			{$$=mknode1(CASE_STMT_LIST, yylineno,$1);}
        ;

//用于识别For循环
ForDec: Exp SEMI Exp SEMI Exp {$$=mknode3( FOR_DEC,yylineno,$1,$3,$5);}//for(int i ; i < 10 ;i++)
       | Exp SEMI SEMI Exp {$$=mknode3(FOR_DEC,yylineno,$1,NULL,$4);}//for(int i;i<10;)
       | Exp SEMI Exp SEMI {$$=mknode3(FOR_DEC,yylineno,$1,$3,NULL);}//for(int i;;i++)
       | Exp SEMI SEMI {$$=mknode3(FOR_DEC,yylineno,$1,NULL,NULL);}//for(int i;;)
       | SEMI Exp SEMI Exp {$$=mknode3(FOR_DEC,yylineno,NULL,$2,$4);}//for(;i<10;i++)
       | SEMI Exp SEMI  {$$=mknode3( FOR_DEC,yylineno,NULL,$2,NULL);}//for(;i<10;)
       | SEMI SEMI Exp {$$=mknode3(FOR_DEC,yylineno,NULL,NULL,$3);}//for(;;i++)
       | SEMI SEMI {$$=mknode3(FOR_DEC, yylineno, NULL, NULL, NULL);}//for(;;)
       ;

//struct name {DefList}识别
//struct name ID识别
Struct_dec: STRUCT StructName LC DefList RC {$$=mknode2(STRUCT_NEW, yylineno, $2, $4);}
        | STRUCT ID ID {$$=mknode0(STRUCT_DEC,yylineno);strcpy($$->type_id,$3);}
        ;
StructName: {$$=NULL;}
        | ID {$$=mknode0(ID,yylineno);strcpy($$->type_id,$1);}
        ;

DefList: {$$=NULL; }
        | Def DefList {$$=mknode2(DEF_LIST,yylineno,$1,$2);}
        | error SEMI   {$$=NULL;}
        ;
Def:    Specifier DecList SEMI {$$=mknode2(VAR_DEF,yylineno,$1,$2);}
        |Struct_dec SEMI {$$=$1;}
        ;
DecList: Dec  {$$=mknode1(DEC_LIST,yylineno,$1);}
       | Dec COMMA DecList  {$$=mknode2(DEC_LIST,yylineno,$1,$3);}
	   ;
//变量赋值
Dec:     VarDec  {$$=$1;}
       | VarDec ASSIGNOP Exp  {$$=mknode2(ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}
       ;
//参数列表
Args:    Exp COMMA Args    {$$=mknode2(ARGS,yylineno,$1,$3);}
       | Exp               {$$=mknode1(ARGS,yylineno,$1);}
       ;
	   
Exp:    Exp ASSIGNOP Exp 		{$$=mknode2(ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}//a=b
	  | Exp PLUS ASSIGNOP Exp 	{$$=mknode2(ASSIGNOP_PLUS,yylineno,$1,$4);strcpy($$->type_id,"ASSIGNOP_PLUS");}//a+=b
	  | Exp MINUS ASSIGNOP Exp 	{$$=mknode2(ASSIGNOP_MINUS,yylineno,$1,$4);strcpy($$->type_id,"ASSIGNOP_MINUS");}//a-=b
	  | Exp STAR ASSIGNOP Exp 	{$$=mknode2(ASSIGNOP_STAR,yylineno,$1,$4);strcpy($$->type_id,"ASSIGNOP_STAR");}//a*=b
	  | Exp DIV ASSIGNOP Exp 	{$$=mknode2(ASSIGNOP_DIV,yylineno,$1,$4);strcpy($$->type_id,"ASSIGNOP_DIV");}//a/=b
	  | Exp MOD ASSIGNOP Exp 	{$$=mknode2(ASSIGNOP_MOD,yylineno,$1,$4);strcpy($$->type_id,"ASSIGNOP_MOD");}//a%=b
      | Exp AND Exp   			{$$=mknode2(AND,yylineno,$1,$3);strcpy($$->type_id,"AND");}//a&&b
      | Exp OR Exp    			{$$=mknode2(OR,yylineno,$1,$3);strcpy($$->type_id,"OR");}//a||b
      | Exp RELOP Exp 			{$$=mknode2(RELOP,yylineno,$1,$3);strcpy($$->type_id,$2);}//a relop b
      | Exp PLUS Exp  			{$$=mknode2(PLUS,yylineno,$1,$3);strcpy($$->type_id,"PLUS");}//a+b
      | Exp MINUS Exp 			{$$=mknode2(MINUS,yylineno,$1,$3);strcpy($$->type_id,"MINUS");}//a-b
      | Exp STAR Exp  			{$$=mknode2(STAR,yylineno,$1,$3);strcpy($$->type_id,"STAR");}//a*b
      | Exp DIV Exp   			{$$=mknode2(DIV,yylineno,$1,$3);strcpy($$->type_id,"DIV");}//a/b
      | Exp MOD Exp   			{$$=mknode2(MOD,yylineno,$1,$3);strcpy($$->type_id,"MOD");}//a%b
      | Exp PLUS PLUS  			{$$=mknode1(AUTOPLUS,yylineno,$1);strcpy($$->type_id, "RPAUTOPLUS");}//a++
      | Exp MINUS MINUS 		{$$=mknode1(AUTOMINUS,yylineno,$1);strcpy($$->type_id,"RPAUTOMINUS");}//a--
      | LP Exp RP     			{$$=$2;}//(a)
      | MINUS Exp				{$$=mknode1(UMINUS,yylineno,$2);strcpy($$->type_id,"UMINUS");}//-a
      | NOT Exp       			{$$=mknode1(NOT,yylineno,$2);strcpy($$->type_id,"NOT");}//!a
      | ID LP Args RP 			{$$=mknode1(FUNC_CALL,yylineno,$3);strcpy($$->type_id,$1);}//函数调用
      | ID LP RP      			{$$=mknode0(FUNC_CALL,yylineno);strcpy($$->type_id,$1);}//函数调用
      | ID            			{$$=mknode0(ID,yylineno);strcpy($$->type_id,$1);}
      | INT          			{$$=mknode0(INT,yylineno);$$->type_int=$1;$$->type=INT;}
      | CHAR        			{$$=mknode0(CHAR,yylineno);$$->type_char=$1;$$->type=CHAR;}
      | STRING       			{$$=mknode0(STRING,yylineno);strcpy($$->type_id,$1);$$->type=STRING;}
      | FLOAT        			{$$=mknode0(FLOAT,yylineno);$$->type_float=$1;$$->type=FLOAT;}
      | LB Args RB   			{$$=$2;}//数组
      | ID Arraylist  			{$$=mknode1(ID,yylineno,$2);strcpy($$->type_id,$1);}//a[2][3]
      | Exp DOT ID 				{$$=mknode1(STRUCT_VISIT, yylineno, $1);strcpy($$->type_id,$3);}//A.a
      ;
%%

int main(int argc, char *argv[]){
    yyin=fopen(argv[1],"r");
	if (!yyin) 
        return 0;
	yylineno=1;
	yyparse();
	return 0;
}

void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}