#ifndef KMC_C89_COMPILER_AST_AST_STRING_H
#define KMC_C89_COMPILER_AST_AST_STRING_H

#include "../ast.h"
#include "../stdstring.h"

typedef StringRef AstTokenRef;

void ast_string_allocator_ctor(void);

AstRef ast_make_token(const char* src, size_t length);

#endif  /* KMC_C89_COMPILER_AST_AST_STRING_H */
