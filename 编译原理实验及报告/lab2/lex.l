%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"
int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int type_int;
	char type_char;
	int type_float;
	char type_id[32];
	struct node *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL
#define V 0

%}
%option yylineno
%x COMMENT

id   [A-Za-z][A-Za-z0-9]*  
int    [0-9]+
float  ([0-9]*\.[0-9]+)|([0-9]+\.)
char ['][^\n][']

%%
{int}        {if(V) printf("(%s, INT)\n", yytext);yylval.type_int=atoi(yytext); return INT;}
{float}      {if(V) printf("(%s, FLOAT)\n", yytext);yylval.type_float=atof(yytext); return FLOAT;}
{char}      {if(V) printf("(%s, CHAR)\n", yytext);yylval.type_float=atof(yytext); return CHAR;}
"int"        {if(V) printf("(%s, TYPE)\n", yytext);strcpy(yylval.type_id,  yytext);return TYPE;}
"float"      {if(V) printf("(%s, TYPE)\n", yytext);strcpy(yylval.type_id,  yytext);return TYPE;}
"char"      {if(V) printf("(%s, TYPE)\n", yytext);strcpy(yylval.type_id,  yytext);return TYPE;}

"return"     {if(V) printf("(%s, RETURN)\n", yytext);return RETURN;}
"if"         {if(V) printf("(%s, IF)\n", yytext);return IF;}
"else"       {if(V) printf("(%s, ELSE)\n", yytext);return ELSE;}
"while"      {if(V) printf("(%s, WHILE)\n", yytext);return WHILE;}
"for"		 {if(V) printf("(%s, FOR)\n", yytext);return FOR;}
"break"		 {if(V) printf("(%s, BREAK)\n", yytext);return BREAK;}
"continue"	 {if(V) printf("(%s, CONTINUE)\n", yytext);return CONTINUE;}

{id}       {if(V) printf("(%s, ID)\n", yytext);strcpy(yylval.type_id,  yytext); return ID;/*由于关键字的形式也符合标识符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			{if(V) printf("(%s, SEMI)\n", yytext);return SEMI;}
","			{if(V) printf("(%s, COMMA)\n", yytext);return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {if(V) printf("(%s, RELOP)\n", yytext);strcpy(yylval.type_id, yytext);;return RELOP;}
"="			{if(V) printf("(%s, SSIGNOP)\n", yytext);return ASSIGNOP;}
"+"			{if(V) printf("(%s, PLUS)\n", yytext);return PLUS;}
"-"			{if(V) printf("(%s, MINUS)\n", yytext);return MINUS;}
"*"			{if(V) printf("(%s, STAR)\n", yytext);return STAR;}
"/"			{if(V) printf("(%s, DIV)\n", yytext);return DIV;}
"%"			{if(V) printf("(%s, MOD)\n", yytext);return MOD;}

"++"     {if(V) printf("(%s, AUTOPLUS)\n", yytext);return AUTOPLUS;}//自增
"--"     {if(V) printf("(%s, AUTOMINUS)\n", yytext);return AUTOMINUS;}//自减
"+="     {if(V) printf("(%s, PLUSASSIGNOP)\n", yytext);return PLUSASSIGNOP;}
"-="     {if(V) printf("(%s, MINUSASSIGNOP)\n", yytext);return MINUSASSIGNOP;}
"*="     {if(V) printf("(%s, STARASSIGNOP)\n", yytext);return STARASSIGNOP;}
"/="     {if(V) printf("(%s, DIVASSIGNOP)\n", yytext);return DIVASSIGNOP;}
"%="     {if(V) printf("(%s, MODASSIGNOP)\n", yytext);return MODASSIGNOP;}

"&&"        {if(V) printf("(%s, AND)\n", yytext);return AND;}
"||"        {if(V) printf("(%s, OR)\n", yytext);return OR;}
"!"			{if(V) printf("(%s, NOT)\n", yytext);return NOT;}
"("			{if(V) printf("(%s, LP)\n", yytext);return LP;}
")"			{if(V) printf("(%s, RP)\n", yytext);return RP;}
"{"			{if(V) printf("(%s, LC)\n", yytext);return LC;}
"}"			{if(V) printf("(%s, RC)\n", yytext);return RC;}
"[" 		{if(V) printf("(%s, LB)\n", yytext);return LB;}
"]" 		{if(V) printf("(%s, RB)\n", yytext);return RB;}
[\n]        {if(V) printf("(\\n, EOF)\n");yycolumn=1;}   
[ \r\t]          {}
\/\/[^\n]*  {}//匹配注释
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}

"/*"		{BEGIN(COMMENT);}
<COMMENT>"*/" {BEGIN(INITIAL);}
<COMMENT>([^*]|\n)+|.
%%

/* 和bison联用时，不需要这部分
void main()
{
yylex();
return 0;
}

*/
int yywrap()
{
return 1;
}
