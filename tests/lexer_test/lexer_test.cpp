extern "C" {
#include <stdio.h>
#include <string.h>
#include "lexer_adapter.h"
#include "token.h"
}
#include "gtest/gtest.h"
#include <vector>

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
  char *str = new char[code.length() + 1];
  strcpy(str, code.c_str());
  yyin_from_string(str, code.length());
  Token tok;
  tok = (Token)yylex();
  return tok;
}

TEST(LexerTest, HandlesSingleToken) {
  EXPECT_EQ(LBRAKET, lex_first_token("[42];"));
  EXPECT_EQ(RBRAKET, lex_first_token("] + 42;"));
  EXPECT_EQ(LPAREN, lex_first_token("(42);"));
  EXPECT_EQ(RPAREN, lex_first_token(") * 50; /* comment */"));
}
