enum Token {
  LBRAKET, RBRAKET, LPAREN, RPAREN, LBRACE, RBRACE,
  ARROW, INCREMENT, DECREMENT, ASTE, AMP, PLUS, MINUS,
  NEG, DIV, MOD, BLSHIFT, BRSHIFT, LT, GT, LE, GE, ASSIGN,
  NEQ, BXOR, LAND, LOR, BOR, QUESTION, EQ, MULEQ, DIVEQ,
  MODASSIGN, ADDASSIGN, SUBASSIGN, BLSHIFTASSIGN, BRSHIFTASSIGN, BANDASSIGN, BXORASSIGN,
  BORASSIGN, COMMA, COLON, SEMICOLON,
  
  AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO,
  DOUBLE, ELSE, ENUM, FLOAT, FOR, GOTO, IF, INT, LONG,
  REGISTER, RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT,
  SWITCH, TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE, WHILE,
  FORTY_TWO,

  INT_LITERAL, DOUBLE_LITERAL,
  CHAR_LITERAL, STRING_LITERAL,
  IDENT
};
