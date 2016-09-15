/* %option yywrap */
%{
#define YY_USER_INIT initialize_lexer()
#include <stdlib.h>
#include "ast_method.h"
#include "stdstring.h"
#include "parser.tab.h"

int yywrap(void) {
  return 1;
}

static StringRef lexer_string_literal;

void initialize_lexer(void) {
  ast_initialize_pool();
}
void create_token(void) {
  yylval = ast_make_token(yytext, yyleng);
}
%}
SIMPLE_ESCAPE_SEQUENCE "\\"[\'\"?\\abfnrtv]
OCT_ESCAPE_SEQUENCE "\\"[0-7]{1,3}
HEX_ESCAPE_SEQUANCE "\\x"[0-9a-fA-F]+
ESCAPE_SEQUENCE {SIMPLE_ESCAPE_SEQUENCE}|{OCT_ESCAPE_SEQUENCE}|{HEX_ESCAPE_SEQUANCE}
C_CHAR ([^\'\\\n]|{ESCAPE_SEQUENCE})
S_CHAR ([^\"\\\n]|{ESCAPE_SEQUENCE})
IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*
DIGIT8 "0"[0-7]*
DIGIT10 [1-9][0-9]*
DIGIT16 ("0x"|"0X")[0-9a-fA-F]+
SINGLE_CHARACTER_TOKEN [\[\]\(\)\{\}+\-*/%&|^!?=,:;]
INTEGER_SUFFIX ([uU][lL]?|[Ll][uU]?)
%x PREPROCESS
%x COMMENT
%x STRING
%%

"#"              BEGIN(PREPROCESS);
<PREPROCESS>"\n" BEGIN(INITIAL);
<PREPROCESS>.    ;

"/*"          BEGIN(COMMENT);
<COMMENT>"*/" BEGIN(INITIAL);
<COMMENT>.    ;

("L"?)"\"" {
  lexer_string_literal = string_ctor("", NULL);
  BEGIN(STRING);
}

<STRING>"\"" {
  const size_t leng = string_length(lexer_string_literal);
  yylval = ast_make_token(string_data(lexer_string_literal), leng);
  string_dtor(&lexer_string_literal);
  BEGIN(INITIAL);
  return STRING_LITERAL;
}

<STRING>{S_CHAR} {
  unsigned i;
  for (i = 0; i < yyleng; ++i) {
    string_push_back(lexer_string_literal, yytext[i]);
  }
}

("'"{C_CHAR}*"'"|"L'"{C_CHAR}*"'") {
  create_token();
  return CHARACTER_CONSTANT;
}

[ \t\n] ;

[0-9]*"."[0-9]*([Ee][+-]?{DIGIT10})?[FfLl]? {
  create_token();
  return FLOATING_CONSTANT;
}

({DIGIT8}|{DIGIT10}|{DIGIT16})({INTEGER_SUFFIX})? {
  create_token();
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

"auto" {
  create_token();
  return AUTO;
}
"break"    return BREAK;
"case"     return CASE;
"char" {
  create_token();
  return CHAR;
}
"const" {
  create_token();
  return CONST;
}
"continue" return CONTINUE;
"default"  return DEFAULT;
"do"       return DO;
"double" {
  create_token();
  return DOUBLE;
}
"else"     return ELSE;
"enum"     return ENUM;
"extern" {
  create_token();
  return EXTERN;
}
"float" {
  create_token();
  return FLOAT;
}
"for"      return FOR;
"goto"     return GOTO;
"if"       return IF;
"int" {
  create_token();
  return INT;
}
"long" {
  create_token();
  return LONG;
}
"register" {
  create_token();
  return REGISTER;
}
"return"   return RETURN;
"short" {
  create_token();
  return SHORT;
}
"signed" {
  create_token();
  return SIGNED;
}
"sizeof"   return SIZEOF;
"static" {
  create_token();
  return STATIC;
}
"struct" {
  create_token();
  return STRUCT;
}
"switch"   return SWITCH;
"typedef" {
  create_token();
  return TYPEDEF;
}
"union"  {
  create_token();
  return UNION;
}
"unsigned" {
  create_token();
  return UNSIGNED;
}
"void" {
  create_token();
  return VOID;
}
"volatile" {
  create_token();
  return VOLATILE;
}
"while"    return WHILE;

{IDENTIFIER} {
  create_token();
  return IDENTIFIER;
}

. {
  StringRef text = make_string(yytext, yyleng, NULL);
  fprintf(stderr, "could not lex: %s\n", string_data(text));
  string_dtor(&text);
  exit(EXIT_FAILURE);
}
%%

void set_yyin_string(const char *code) {
  yy_scan_string(code);
}

void set_yyin_file(const char *filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "fatal error: failed to open %s\n", filename);
    exit(EXIT_FAILURE);
  }
  yyin = fp;
}
