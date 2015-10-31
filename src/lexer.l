%option yywrap
%{
#include "token.h"
#include "yacc_mock.h"
/* #include "y.tab.h" */

int yywrap(void) {
  return 1;
}

void copy_yytext() {
  char *literal = (char*)malloc(yylen);
  strcpy(literal, yytext);
  yylval = literal;
}
%}
%x COMMENT
%%

"/*"              BEGIN(COMMENT);
<COMMENT>"*/"     BEGIN(INITIAL);
<COMMENT>.        ;

"["   return LBRAKET;
"]"   return RBRAKET;
"("   return LPAREN;
")"   return RPAREN;
"{"   return LBRACE;
"}"   return RBRACE;
"->"  return ARROW;
"++"  return INCREMENT;
"--"  return DECREMENT;
"*"   return ASTE;
"&"   return AMP;
"+"   return PLUS;
"-"   return MINUS;
"!"   return NEG;
"/"   return DIV;
"%"   return MOD;
"<<"  return LSHIFT;
">>"  return RSHIFT;
"<"   return LT;
">"   return GT;
"<="  return LE;
">="  return GE;
"=="  return EQEQ;
"!="  return NEQ;
"^"   return LXOR;
"|"   return BAR;
"&&"  return LAND;
"||"  return LOR;
"?"   return QUESTION;
"="   return EQ;
"*="  return MULEQ;
"/="  return DIVEQ;
"%="  return MODEQ;
"+="  return ADDEQ;
"-="  return SUBEQ;
"<<=" return LSHIFTEQ;
">>=" return RSHIFTEQ;
"&="  return LANDEQ;
"^="  return LXOREQ;
"|="  return LOREQ;
","   return COMMA;
":"   return COLON;
";"   return SEMICOLON;

"auto"      return AUTO;
"break"     return BREAK;
"case"      return CASE;
"char"      return CHAR;
"const"     return CONST;
"continue"  return CONTINUE;
"default"   return DEFAULT;
"do"        return DO;
"double"    return DOUBLE;
"else"      return ELSE;
"enum"      return ENUM;
"float"     return FLOAT;
"for"       return FOR;
"goto"      return GOTO;
"if"        return IF;
"int"       return INT;
"long"      return LONG;
"register"  return REGISTER;
"return"    return RETURN;
"short"     return SHORT;
"signed"    return SIGNED;
"sizeof"    return SIZEOF;
"static"    return STATIC;
"struct"    return STRUCT;
"switch"    return SWITCH;
"typedef"   return TYPEDEF;
"union"     return UNION;
"unsigned"  return UNSIGNED;
"void"      return VOID;
"volatile"  return VOLATILE;
"while"     return WHILE;
"answer"    return FORTY_TWO; // funny easter egg

[1-9][0-9]* {
  copy_yytext();
  return INT_LITERAL;
}

[0-9]*\.[0-9]* {
  copy_yytext();
  return DOUBLE_LITERAL;
}

[_a-z][_a-zA-Z0-9]* {
  copy_yytext();
  return IDENT;
}
%%
#include <stdio.h>

int main(argc,argv)
int argc;
char *argv;
{
  yylex();
}
