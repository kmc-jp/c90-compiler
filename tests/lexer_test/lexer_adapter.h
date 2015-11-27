#ifndef KMC_C89_COMPILER_LEXER_ADAPTER_H
#define KMC_C89_COMPILER_LEXER_ADAPTER_H

#include "utility.h"

BEGIN_EXTERN_C

void yyin_from_file(const char *filename);
void yyin_from_string(const char *code);

int yylex(void);

END_EXTERN_C

#endif  /* KMC_C89_COMPILER_LEXER_ADAPTER_H */
