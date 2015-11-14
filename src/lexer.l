/* %option yywrap */
%{
#define YY_USER_INIT initialize_lexer()
#include "token.h"
#include "yacc_mock.h"
#include "utility.h"
#include "use_vector.h"
/* #include "y.tab.h" */

int yywrap(void) {
  return 1;
}

void copy_to_yylval(char *src, int size) {
  char *literal = safe_array_malloc(char, size + 1);
  strncpy(literal, src, size);
  literal[size] = '\0';
  yylval = literal;
}

VECTORREF(char) lexer_string_literal;

void initialize_lexer(void) {
  do_initialize_vector();
  lexer_string_literal = VECTORFUNC(char, ctor)();
}
%}
ESCSEQ    "\\"[\\\'\"abfnrtv0?]
NONESCSEQ [^\\]
CHARACTER {ESCSEQ}|{NONESCSEQ}
IDENT     [_a-z][_a-zA-Z0-9]*
DIGIT2    "0b"("0"|1[01]*)
DIGIT4    "0q"("0"|[1-3][0-3]*)
DIGIT8    "0"("0"|[1-7][0-7]*)
DIGIT10   "0"|[1-9][0-9]*
DIGIT16   "0x"("0"|[1-9A-F][0-9A-F]*)
CHAR8     "\\"[0-7]+
CHAR16    "\\x"[0-9A-F]+
%x COMMENT
%x STRING
%%

"/*"              BEGIN(COMMENT);
<COMMENT>"*/"     BEGIN(INITIAL);
<COMMENT>.        ;

"\""              BEGIN(STRING);

<STRING>"\""      {
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
  return DOUBLE_LITERAL;
}

[+-]?({DIGIT2}|{DIGIT4}|{DIGIT8}|{DIGIT10}|{DIGIT16})[UuLl]? {
  copy_to_yylval(yytext, yyleng);
  return INT_LITERAL;
}

"<<=" return BLSHIFTASSIGN;
">>=" return BRSHIFTASSIGN;
"<<"  return BLSHIFT;
">>"  return BRSHIFT;
"<="  return LE;
">="  return GE;
"=="  return EQ;
"!="  return NEQ;
"->"  return ARROW;
"++"  return INCREMENT;
"--"  return DECREMENT;
"&&"  return LAND;
"||"  return LOR;
"*="  return MULASSIGN;
"/="  return DIVASSIGN;
"%="  return MODASSIGN;
"+="  return ADDASSIGN;
"-="  return SUBASSIGN;
"&="  return BANDASSIGN;
"^="  return BXORASSIGN;
"|="  return BORASSIGN;
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
"="   return ASSIGN;
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

{IDENT} {
  copy_to_yylval(yytext, yyleng);
  return IDENT;
}

"'"({CHARACTER}|{CHAR8}|{CHAR16})"'" {
  copy_to_yylval(yytext, yyleng);
  return CHAR_LITERAL;
}

.           {
  printf("could not lex: %s\n", yytext);
  exit(EXIT_FAILURE);
}
%%
