#ifndef KMC_C89_COMPILER_LEXER_ADAPTER_H
#define KMC_C89_COMPILER_LEXER_ADAPTER_H

void yyin_from_file(const char *filename);
void yyin_from_string(char *code, int size);

int yylex(void);

#endif  /* KMC_C89_COMPILER_LEXER_ADAPTER_H */
