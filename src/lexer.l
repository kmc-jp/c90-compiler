%option yywrap
%{
#include "token.h"
#include "yacc_mock.h"
/* #include "y.tab.h" */

int yywrap(void) {
  return 1;
}

void copy_to_yylval(char *src, int size) {
  char *literal = (char*)malloc(size + 1);
  if (literal == NULL) {
    printf("could not allocate memory for literal\n");
    exit(EXIT_FAILURE);
  }
  strncpy(literal, src, size);
  literal[size] = '\0';
  yylval = literal;
}

VECTORREF(char) lexer_string_literal;
%}
ESCSEQ    \\[\\\?\'\"abfnrtv0]
NONESCSEQ [^\\\?\'\"abfnrtv0]
CHARACTER {ESCSEQ}|{NONESCSEQ}
IDENT     [_a-z][_a-zA-Z0-9]*
%x COMMENT
%x STRING
%%

"/*"              BEGIN(COMMENT);
<COMMENT>"*/"     BEGIN(INITIAL);
<COMMENT>.        ;

"\""              BEGIN(STRING);

<STRING>{CHARACTER} {
  int i;
  for (i = 0; i < yyleng; ++i) {
    VECTORREF(char, push)(lexer_string_literal, &(yytext[i]));
  }
}

<STRING>"\""      {
  int len = VECTORREF(char, size)(lexer_string_literal);
  char *str = VECTORREF(char, data)(lexer_string_literal);
  copy_to_yylval(str, len);
  VECTORREF(char, clear)(lexer_string_literal);
  BEGIN(INITIAL);
  return STRING_LITERAL;
}

"<<"  return BLSHIFT;
">>"  return BRSHIFT;
"<="  return LE;
">="  return GE;
"=="  return EQEQ;
"!="  return NEQ;
"->"  return ARROW;
"++"  return INCREMENT;
"--"  return DECREMENT;
"&&"  return LAND;
"||"  return LOR;
"*="  return MULEQ;
"/="  return DIVEQ;
"%="  return MODEQ;
"+="  return ADDEQ;
"-="  return SUBEQ;
"<<=" return BLSHIFTEQ;
">>=" return BRSHIFTEQ;
"&="  return BANDEQ;
"^="  return BXOREQ;
"|="  return BOREQ;
"["   return LBRAKET;
"]"   return RBRAKET;
"("   return LPAREN;
")"   return RPAREN;
"{"   return LBRACE;
"}"   return RBRACE;
"*"   return ASTE;
"&"   return AMP;
"+"   return PLUS;
"-"   return MINUS;
"!"   return NEG;
"/"   return DIV;
"%"   return MOD;
"<"   return LT;
">"   return GT;
"^"   return BXOR;
"|"   return BOR;
"?"   return QUESTION;
"="   return EQ;
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
"the_answer"  return FORTY_TWO; /* funny easter egg */

"0"|[1-9][0-9]* {
  copy_to_yylval(yytext, yyleng);
  return INT_LITERAL;
}

[0-9]*\.[0-9]* {
  copy_to_yylval(yytext, yyleng);
  return DOUBLE_LITERAL;
}

{IDENT} {
  copy_to_yylval(yytext, yyleng);
  return IDENT;
}

"'"{CHARACTER}"'" {
  copy_to_yylval(yytext, yyleng);
  return CHAR_LITERAL;
}

.           {
  printf("could not lex: %s\n", yytext);
  exit(EXIT_FAILURE);
}
%%
#include <stdio.h>

int main(argc,argv)
int argc;
char *argv;
{
  yylex();
}
