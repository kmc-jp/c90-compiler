/* %option yywrap */
%{
#define YY_USER_INIT initialize_lexer()
#include "utility.h"
#include "use_vector.h"
extern VECTORREF(char) lexer_string_literal;
void initialize_lexer(void);
void copy_to_yylval(char *src, int size);
%}
%top{
#include "parser.tab.h"
void scan_from_file(const char* filename);
void scan_from_string(const char* code);
}
ESCAPE_SEQUENCE "\\"[\\\'\"abfnrtv0?]
NOT_ESCAPE_SEQUENCE [^\\]
CHARACTER {ESCAPE_SEQUENCE}|{NOT_ESCAPE_SEQUENCE}
IDENTIFIER [_a-z][_a-zA-Z0-9]*
DIGIT2 "0b"("0"|1[01]*)
DIGIT4 "0q"("0"|[1-3][0-3]*)
DIGIT8 "0"("0"|[1-7][0-7]*)
DIGIT10 "0"|[1-9][0-9]*
DIGIT16 "0x"("0"|[1-9A-F][0-9A-F]*)
CHAR8 "\\"[0-7]+
CHAR16 "\\x"[0-9A-F]+
SINGLE_CHARACTER_TOKEN [\[\]\(\)\{\}+\-*/%&|^!?=,:;]
%x COMMENT
%x STRING
%%

"/*"          BEGIN(COMMENT);
<COMMENT>"*/" BEGIN(INITIAL);
<COMMENT>.    ;

"\"" BEGIN(STRING);

<STRING>"\"" {
  int len = VECTORFUNC(char, size)(lexer_string_literal);
  char *str = VECTORFUNC(char, data)(lexer_string_literal);
  copy_to_yylval(str, len);
  VECTORFUNC(char, clear)(lexer_string_literal);
  BEGIN(INITIAL);
  return STRING_LITERAL;
}

<STRING>{CHARACTER} {
  unsigned i;
  for (i = 0; i < yyleng; ++i) {
    VECTORFUNC(char, push_back)(lexer_string_literal, &(yytext[i]));
  }
}

[+-]?[0-9]*"."[0-9]*([Ee][+-]?{DIGIT10})?[FfLl]? {
  copy_to_yylval(yytext, yyleng);
  return FLOATING_CONSTANT;
}

[+-]?({DIGIT2}|{DIGIT4}|{DIGIT8}|{DIGIT10}|{DIGIT16})[UuLl]? {
  copy_to_yylval(yytext, yyleng);
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
  copy_to_yylval(yytext, yyleng);
  return IDENTIFIER;
}

"'"({CHARACTER}|{CHAR8}|{CHAR16})"'" {
  copy_to_yylval(yytext, yyleng);
  return CHARACTER_CONSTANT;
}

. {
  printf("could not lex: %s\n", yytext);
  exit(EXIT_FAILURE);
}
%%

VECTORREF(char) lexer_string_literal;

int yywrap(void) {
  return 1;
}

void initialize_lexer(void) {
  initialize_vector();
  lexer_string_literal = VECTORFUNC(char, ctor)();
}

void copy_to_yylval(char *src, int size) {
  char *literal = safe_array_malloc(char, size + 1);
  strncpy(literal, src, size);
  literal[size] = '\0';
  yylval.null_terminated = literal;
}

void scan_from_file(const char* file) {
  FILE* const fp = fopen(file, "r");
  if (fp == NULL) {
    fprintf(stderr, "fatal error: failed to open %s\n", file);
    exit(EXIT_FAILURE);
  }
  yyin = fp;
}

void scan_from_string(const char* str) {
  yy_scan_string(str);
}
