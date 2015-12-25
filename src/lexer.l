/* %option yywrap */
%{
#define YY_USER_INIT initialize_lexer()
#include "utility.h"
#include "use_vector.h"
#include "ast/ast_string.h"
#include "parser.tab.h"
#include "ast_method.h"

int yywrap(void) {
  return 1;
}

VECTORREF(char) lexer_string_literal;

void initialize_lexer(void) {
  lexer_string_literal = VECTORFUNC(char, ctor)(NULL);
  ast_initialize_pool();
}
%}
SIMPLE_ESCAPE_SEQUENCE "\\"[\'\"?\\abfnrtv]
OCT_ESCAPE_SEQUENCE "\\"[0-7]{1,3}
HEX_ESCAPE_SEQUANCE "\\x"[0-9a-fA-F]+
ESCAPE_SEQUENCE {SIMPLE_ESCAPE_SEQUENCE}|{OCT_ESCAPE_SEQUENCE}|{HEX_ESCAPE_SEQUANCE}
C_CHAR ([^\'\\\n]|{ESCAPE_SEQUENCE})
IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*
DIGIT2 "0b"("0"|1[01]*)
DIGIT4 "0q"("0"|[1-3][0-3]*)
DIGIT8 "0"[0-7]*
DIGIT10 [1-9][0-9]*
DIGIT16 ("0x"|"0X")[0-9a-fA-F]+
SINGLE_CHARACTER_TOKEN [\[\]\(\)\{\}+\-*/%&|^!?=,:;]
INTEGER_SUFFIX ([uU][lL]?|[Ll][uU]?)
WHITESPACE [ \t\n]
%x COMMENT
%x STRING
%%

"/*"          BEGIN(COMMENT);
<COMMENT>"*/" BEGIN(INITIAL);
<COMMENT>.    ;

("L"?)"\"" BEGIN(STRING);

<STRING>"\"" {
  int len = VECTORFUNC(char, size)(lexer_string_literal);
  char *str = VECTORFUNC(char, data)(lexer_string_literal);
  yylval = ast_make_token(str, len);
  VECTORFUNC(char, clear)(lexer_string_literal);
  BEGIN(INITIAL);
  return STRING_LITERAL;
}

<STRING>{CHARACTER} {
  unsigned i;
  for (i = 0; i < yyleng; ++i) {
    VECTORFUNC(char, push_back)(lexer_string_literal, yytext[i]);
  }
}

WHITESPACE ;

[0-9]*"."[0-9]*([Ee][+-]?{DIGIT10})?[FfLl]? {
  yylval = ast_make_token(yytext, yyleng);
  return FLOATING_CONSTANT;
}

({DIGIT2}|{DIGIT4}|{DIGIT8}|{DIGIT10}|{DIGIT16})({INTEGER_SUFFIX})? {
  yylval = ast_make_token(yytext, yyleng);
  return INTEGER_CONSTANT;
}

{SINGLE_CHARACTER_TOKEN} {
  return *yytext;
}

"->" return ARROW;
"++" return INCREMENT;
"--" return DECREMENT;
"<<" return LEFT_SHIFT;
">>" return RIGHT_SHIFT;
"==" return EQUAL;
"!=" return NOT_EQUAL;
"<" return LESS;
">" return GREATER;
"<=" return LESS_EQUAL;
">=" return GREATER_EQUAL;
"&&" return AND;
"||" return OR;
"+=" return ADD_ASSIGN;
"-=" return SUB_ASSIGN;
"*=" return MUL_ASSIGN;
"/=" return DIV_ASSIGN;
"%=" return MOD_ASSIGN;
"<<=" return LEFT_SHIFT_ASSIGN;
">>=" return RIGHT_SHIFT_ASSIGN;
"&=" return AND_ASSIGN;
"|=" return OR_ASSIGN;
"^=" return XOR_ASSIGN;

"auto"     return AUTO;
"break"    return BREAK;
"case"     return CASE;
"char"     return CHAR;
"const"    return CONST;
"continue" return CONTINUE;
"default"  return DEFAULT;
"do"       return DO;
"double"   return DOUBLE;
"else"     return ELSE;
"enum"     return ENUM;
"extern"   return EXTERN;
"float"    return FLOAT;
"for"      return FOR;
"goto"     return GOTO;
"if"       return IF;
"int"      return INT;
"long"     return LONG;
"register" return REGISTER;
"return"   return RETURN;
"short"    return SHORT;
"signed"   return SIGNED;
"sizeof"   return SIZEOF;
"static"   return STATIC;
"struct"   return STRUCT;
"switch"   return SWITCH;
"typedef"  return TYPEDEF;
"union"    return UNION;
"unsigned" return UNSIGNED;
"void"     return VOID;
"volatile" return VOLATILE;
"while"    return WHILE;

{IDENTIFIER} {
  yylval = ast_make_token(yytext, yyleng);
  return IDENTIFIER;
}

("'"{C_CHAR}*"'"|"L'"{C_CHAR}*"'") {
  yylval = ast_make_token(yytext, yyleng);
  return CHARACTER_CONSTANT;
}

. {
  printf("could not lex: %s\n", yytext);
  exit(EXIT_FAILURE);
}
%%
