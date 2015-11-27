extern "C" {
#include <stdio.h>
#include <string.h>
#include "lexer_adapter.h"
#include "use_vector.h"
#include "token.h"
}
#include "gtest/gtest.h"
#include <vector>
#include <string>

std::vector<Token> lex_from_file(const std::string &filename) {
  yyin_from_file(filename.c_str());
  std::vector<Token> tokens;
  Token tok;
  while ((tok = (Token)yylex()) != 0) {
    tokens.push_back(tok);
  }
  return tokens;
}

Token lex_first_token(const std::string &code) {
  std::string str;
  str.reserve(code.length() + 1);
  str.assign(code);
  str.resize(code.length() + 1);
  yyin_from_string(str.data());
  Token tok = (Token)yylex();
  return tok;
}

TEST(LexerTest, HandlesSingleToken) {
  EXPECT_EQ('[', lex_first_token("[42"));
  EXPECT_EQ(']', lex_first_token("]+"));
  EXPECT_EQ('(', lex_first_token("(["));
  EXPECT_EQ(')', lex_first_token(")}"));
  EXPECT_EQ('{', lex_first_token("{("));
  EXPECT_EQ('}', lex_first_token("}}"));
  EXPECT_EQ(ARROW, lex_first_token("->>="));
  EXPECT_EQ(INCREMENT, lex_first_token("+++="));
  EXPECT_EQ(DECREMENT, lex_first_token("-->=0"));
  EXPECT_EQ('*', lex_first_token("*p"));
  EXPECT_EQ('*', lex_first_token("*42"));
  EXPECT_EQ('&', lex_first_token("&n"));
  EXPECT_EQ('+', lex_first_token("+ ++n"));
  EXPECT_EQ('-', lex_first_token("- --n"));
  EXPECT_EQ('!', lex_first_token("!*p"));
  EXPECT_EQ('/', lex_first_token("/!n"));
  EXPECT_EQ('%', lex_first_token("%!n"));
  EXPECT_EQ(LEFT_SHIFT, lex_first_token("<<*p"));
  EXPECT_EQ(RIGHT_SHIFT, lex_first_token(">>*p"));
  EXPECT_EQ(LESS, lex_first_token("<!n"));
  EXPECT_EQ(GREATER, lex_first_token(">!n"));
  EXPECT_EQ(LESS_EQUAL, lex_first_token("<=!n"));
  EXPECT_EQ(GREATER_EQUAL, lex_first_token(">=!n"));
  EXPECT_EQ('=', lex_first_token("=++n"));
  EXPECT_EQ(NOT_EQUAL, lex_first_token("!=!n"));
  EXPECT_EQ('^', lex_first_token("^&n"));
  EXPECT_EQ(AND, lex_first_token("&& &n"));
  EXPECT_EQ(OR, lex_first_token("||&n"));
  EXPECT_EQ('|', lex_first_token("|&n"));
  EXPECT_EQ('?', lex_first_token("?*p"));
  EXPECT_EQ('=', lex_first_token("=!n"));
  EXPECT_EQ(MUL_ASSIGN, lex_first_token("*=*p"));
  EXPECT_EQ(ADD_ASSIGN, lex_first_token("+=++n"));
  EXPECT_EQ(ADD_ASSIGN, lex_first_token("+=-n"));
  EXPECT_EQ(SUB_ASSIGN, lex_first_token("-=--n"));
  EXPECT_EQ(SUB_ASSIGN, lex_first_token("-=-n"));
  EXPECT_EQ(LEFT_SHIFT_ASSIGN, lex_first_token("<<=-n"));
  EXPECT_EQ(RIGHT_SHIFT_ASSIGN, lex_first_token(">>=-n"));
  EXPECT_EQ(AND_ASSIGN, lex_first_token("&=&n"));
  EXPECT_EQ(XOR_ASSIGN, lex_first_token("^=!n"));
  EXPECT_EQ(OR_ASSIGN, lex_first_token("|=!n"));
  EXPECT_EQ(',', lex_first_token(",!n"));
  EXPECT_EQ(':', lex_first_token(":&n"));
  EXPECT_EQ(';', lex_first_token(";;;;;"));

  EXPECT_EQ(AUTO, lex_first_token("auto"));
  EXPECT_EQ(BREAK, lex_first_token("break"));
  EXPECT_EQ(CASE, lex_first_token("case"));
  EXPECT_EQ(CHAR, lex_first_token("char"));
  EXPECT_EQ(CONST, lex_first_token("const"));
  EXPECT_EQ(CONTINUE, lex_first_token("continue"));
  EXPECT_EQ(DEFAULT, lex_first_token("default"));
  EXPECT_EQ(DO, lex_first_token("do"));
  EXPECT_EQ(DOUBLE, lex_first_token("double"));
  EXPECT_EQ(ELSE, lex_first_token("else"));
  EXPECT_EQ(ENUM, lex_first_token("enum"));
  EXPECT_EQ(FLOAT, lex_first_token("float"));
  EXPECT_EQ(FOR, lex_first_token("for"));
  EXPECT_EQ(GOTO, lex_first_token("goto"));
  EXPECT_EQ(IF, lex_first_token("if"));
  EXPECT_EQ(INT, lex_first_token("int"));
  EXPECT_EQ(LONG, lex_first_token("long"));
  EXPECT_EQ(REGISTER, lex_first_token("register"));
  EXPECT_EQ(RETURN, lex_first_token("return"));
  EXPECT_EQ(SHORT, lex_first_token("short"));
  EXPECT_EQ(SIGNED, lex_first_token("signed"));
  EXPECT_EQ(SIZEOF, lex_first_token("sizeof"));
  EXPECT_EQ(STATIC, lex_first_token("static"));
  EXPECT_EQ(STRUCT, lex_first_token("struct"));
  EXPECT_EQ(SWITCH, lex_first_token("switch"));
  EXPECT_EQ(TYPEDEF, lex_first_token("typedef"));
  EXPECT_EQ(UNION, lex_first_token("union"));
  EXPECT_EQ(UNSIGNED, lex_first_token("unsigned"));
  EXPECT_EQ(VOID, lex_first_token("void"));
  EXPECT_EQ(VOLATILE, lex_first_token("volatile"));
  EXPECT_EQ(WHILE, lex_first_token("while"));

  EXPECT_EQ(IDENTIFIER, lex_first_token("automobile"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("breakable"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("case_42"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("character"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("constant"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("continued"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("default_value"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("door"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("double_x"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("else_stmt"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("enumerate"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("float_"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("for42"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("gotoh"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("ift"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("integer"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("long_long"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("registerer"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("return_value"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("shortage"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("signed_"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("sizeof42"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("static_value"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("structure"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("switches"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("__typedef"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("__union"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("unsigned_int"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("_42void"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("volatile__volat42"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("_while_"));
  EXPECT_EQ(IDENTIFIER, lex_first_token("forty_two_million"));

  EXPECT_EQ(INT_LITERAL, lex_first_token("42"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("+42"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("-42"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("0x2A"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("-0x2A"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("052"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("0q222"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("0b1001"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("42U"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("42u"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("-42L"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("+42l"));
  EXPECT_EQ(INT_LITERAL, lex_first_token("0x42ul"));

  EXPECT_EQ(DOUBLE_LITERAL, lex_first_token("3.14"));
  EXPECT_EQ(DOUBLE_LITERAL, lex_first_token("+3.14"));
  EXPECT_EQ(DOUBLE_LITERAL, lex_first_token("-.14"));
  EXPECT_EQ(DOUBLE_LITERAL, lex_first_token("3."));
  EXPECT_EQ(DOUBLE_LITERAL, lex_first_token("3.14e+4"));
  EXPECT_EQ(DOUBLE_LITERAL, lex_first_token("3.14E-4"));
  EXPECT_EQ(DOUBLE_LITERAL, lex_first_token("3.14F"));
  EXPECT_EQ(DOUBLE_LITERAL, lex_first_token("-3.14f"));
  EXPECT_EQ(DOUBLE_LITERAL, lex_first_token("-3.14L"));
  EXPECT_EQ(DOUBLE_LITERAL, lex_first_token("3.14l"));

  EXPECT_EQ(CHAR_LITERAL, lex_first_token("'*'"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\a')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\b')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\f')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\n')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\r')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\v')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\0')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\10')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\x8')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\\')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\"')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\'')"));
  EXPECT_EQ(CHAR_LITERAL, lex_first_token(R"('\?')"));

  EXPECT_EQ(STRING_LITERAL, lex_first_token(R"("abcdefgABCDEF\"G\t\'\n\\____;;;")"));
}
