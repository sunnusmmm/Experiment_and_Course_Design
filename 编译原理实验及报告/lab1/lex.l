%option yylineno
%{
#include "parser.tab.h"
#include "string.h"
#include "node.h"
int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno;yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int type_int;
	char type_char;
	float type_float;
	char type_id[32];
	struct node *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL
%}
%x COMMENT

ID   [A-Za-z][A-Za-z0-9]*  
INT [0-9]+
FLOAT [0-9]*\.[0-9]+)|([0-9]+\.
CHAR ['][^\n][']
STRING ["][^\n]*["]

%%
{INT} {yylval.type_int=atoi(yytext); return INT;}
{FLOAT}  {yylval.type_float=atof(yytext); return FLOAT;}
{CHAR}   {yylval.type_char=yytext[1];return CHAR;}
{STRING} {strncpy(yylval.type_id,yytext+1,strlen(yytext)-2);return STRING;}//string
"int"    {strcpy(yylval.type_id, yytext);return TYPE;}
"float"  {strcpy(yylval.type_id, yytext);return TYPE;}
"char"   {strcpy(yylval.type_id, yytext);return TYPE;}
"string" {strcpy(yylval.type_id,yytext);return TYPE;}//string
"struct" {return STRUCT;}//struct

"if"     {return IF;}
"else"   {return ELSE;}
"while"  {return WHILE;}
"break"	 {return BREAK;} // break
"continue" {return CONTINUE;} //continue
"for"	 {return FOR;}//for
"switch" {return SWITCH;}//switch
"case"	 {return CASE;}//case
"default" {return DEFAULT;}//DEFAULT
"return" {return RETURN;}

{ID}     {strcpy(yylval.type_id,  yytext); return ID;}
":"		 {return COLON;}
";"		 {return SEMI;}
","		 {return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);return RELOP;}
"="		 {return ASSIGNOP;}
"+"		 {return PLUS;}
"-"		 {return MINUS;}
"*"		 {return STAR;}
"/"		 {return DIV;}
"."      {return DOT;}
"%"      {return MOD;}
"&&"     {return AND;}
"||"     {return OR;}
"!"		 {return NOT;}
"("		 {return LP;}
")"		 {return RP;}
"{"		 {return LC;}
"}"		 {return RC;}
"["      {return LB;}
"]"      {return RB;}
[\n]     {yycolumn=1;}   
[ \r\t]  {}
\/\/[^\n]*  {printf("(%s, LINECOMMENT)\n", yytext);}//匹配注释
.		 {printf("Error character: \"%s\"\n\t at Line %d\n",yytext,yylineno);}

 /* 注释 */
"/*"		{BEGIN(COMMENT);}
<COMMENT>"*/" {BEGIN(INITIAL);}
<COMMENT>([^*]|\n)+|.
%%

int yywrap()
{
    return 1;
}