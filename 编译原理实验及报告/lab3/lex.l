%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"
int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int type_int;
	float type_float;
	char type_char[3];
	char type_id[32];
	struct node *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL
#define V 0

%}
%option yylineno
%x COMMENT

ID   [A-Za-z][A-Za-z0-9]*  
INT  ([0-9]+)|(0[xX][0-9a-fA-F]+)|(0[0-7]+)
FLOAT  ([0-9]*\.[0-9]+)|([0-9]+\.)
CHAR ['][^\n][']

%%
{INT}        {if(V) printf("(%s, INT)\n", yytext);yylval.type_int=strtol(yytext,NULL,0);  return INT;}
{FLOAT}  	 {if(V) printf("(%s, FLOAT)\n", yytext);yylval.type_float=atof(yytext); return FLOAT;}
{CHAR}		 {if(V) printf("(%s, CHAR)\n", yytext);yylval.type_char[0]=yytext[1];if(yytext[2] != '\'') {yylval.type_char[1]=yytext[2];yylval.type_char[2]='\0';} else yylval.type_char[1] = yylval.type_char[2] = '\0'; return CHAR;}
"int"        {if(V) printf("(%s, TYPR-INT)\n", yytext);strcpy(yylval.type_id,  yytext);return TYPE;}
"float"      {if(V) printf("(%s, TYPE-FLOAT)\n", yytext);strcpy(yylval.type_id,  yytext);return TYPE;}
"char" 		 {if(V) printf("(%s, TYPE-CHAR)\n", yytext);strcpy(yylval.type_id,  yytext);return TYPE;}

"return"     {if(V) printf("(%s, RETURN)\n", yytext);return RETURN;}
"if"         {if(V) printf("(%s, RETURN)\n", yytext);return IF;}
"else"       {if(V) printf("(%s, ELSE)\n", yytext);return ELSE;}
"while"      {if(V) printf("(%s, WHILE)\n", yytext);return WHILE;}
"for" 		 {if(V) printf("(%s, FOR)\n", yytext);return FOR;}
"break"		 {if(V) printf("(%s, BREAK)\n", yytext);return BREAK;}
"continue"	 {if(V) printf("(%s, CONTINUE)\n", yytext);return CONTINUE;}

{ID}       {if(V) printf("(%s, ID)\n", yytext);strcpy(yylval.type_id,  yytext); return ID;/*由于关键字的形式也符合标识符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			{if(V) printf("(%s, SEMI)\n", yytext);return SEMI;}
","			{if(V) printf("(%s, COMMA)\n", yytext);return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {if(V) printf("(%s, RELOP)\n", yytext);strcpy(yylval.type_id, yytext);return RELOP;}
"="			{if(V) printf("(%s, ASSIGNOP)\n", yytext);return ASSIGNOP;}
"+"			{if(V) printf("(%s, PLUS)\n", yytext);return PLUS;}
"-"			{if(V) printf("(%s, MINUS)\n", yytext);return MINUS;}
"*"			{if(V) printf("(%s, STAR)\n", yytext);return STAR;}
"/"			{if(V) printf("(%s, DIV)\n", yytext);return DIV;}
"%"			{if(V) printf("(%s, MOD)\n", yytext);return MOD;}

"++" 		{if(V) printf("(%s, AUTOADD)\n", yytext);return AUTOADD;}
"--" 		{if(V) printf("(%s, AUTOSUB)\n", yytext);return AUTOSUB;}
"+=" 		{if(V) printf("(%s, COMADD)\n", yytext);return COMADD;}
"-=" 		{if(V) printf("(%s, COMSUB)\n", yytext);return COMSUB;}
"*="     	{if(V) printf("(%s, COMSUB)\n", yytext);return COMSTAR;}
"/="     	{if(V) printf("(%s, COMDIV)\n", yytext);return COMDIV;}
"%="     	{if(V) printf("(%s, COMMOD)\n", yytext);return COMMOD;}

"&&"        {if(V) printf("(%s, AND)\n", yytext);return AND;}
"||"        {if(V) printf("(%s, OR)\n", yytext);return OR;}
"!"			{if(V) printf("(%s, NOT)\n", yytext);return NOT;}
"("			{if(V) printf("(%s, LP)\n", yytext);return LP;}
")"			{if(V) printf("(%s, RP)\n", yytext);return RP;}
"[" 		{if(V) printf("(%s, LB)\n", yytext);return LB;}
"]" 		{if(V) printf("(%s, RB)\n", yytext);return RB;}
"{"			{if(V) printf("(%s, LC)\n", yytext);return LC;}
"}"			{if(V) printf("(%s, RC)\n", yytext);return RC;}
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
