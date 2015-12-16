#ifndef KMC_C89_COMPILER_AST_AST_STRING_H
#define KMC_C89_COMPILER_AST_AST_STRING_H

#include "../stdstring.h"

void ast_string_allocator_ctor(void);

StringRef ast_make_string(const char* src, size_t length);

#endif  /* KMC_C89_COMPILER_AST_AST_STRING_H */
