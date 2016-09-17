/* %option yywrap */
%{
#include "parser.tab.h"
#include "sexpr.h"
#include "stdstring.h"

int yywrap(void) {
  return 1;
}

static StringRef lexer_string_literal;

void create_token(void) {
  yylval = sexpr_new_symbol(yytext, yyleng);
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
SINGLE_CHARACTER_TOKEN [\[\]\(\)\{\}+\-*/%<>&|^!?=,:;]
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
  const size_t length = string_length(lexer_string_literal);
  const char* const data = string_data(lexer_string_literal);
  yylval = sexpr_new_symbol(data, length);
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
"..." return ELLIPSIS;

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

void set_yyin_file(FILE* fp) {
  yyin = fp;
}
