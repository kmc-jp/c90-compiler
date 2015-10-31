#ifndef KMC_C89_COMPILER_YACC_MOCK_H
#define KMC_C89_COMPILER_YACC_MOCK_H
union TokenVal {
  int int_value;
  double double_value;
  char string_value[72];
};

extern union TokenVal yylval;
#endif  /* KMC_C89_COMPILER_YACC_MOCK_H */
