#ifndef KMC_C89_COMPILER_AST_AST_VECTOR_H
#define KMC_C89_COMPILER_AST_AST_VECTOR_H

#include "../ast.h"
#include "../vector.h"

#define AST_VECTOR_FUNC(function) \
  VECTORFUNC(AstRef, function)

DECLARE_VECTOR(AstRef)

typedef VECTORREF(AstRef) AstVectorRef;

void ast_vector_allocator_ctor(void);

AstVectorRef ast_make_vector(void);
void ast_push_vector(AstVectorRef vector, AstRef element);

#endif  /* KMC_C89_COMPILER_AST_AST_VECTOR_H */
