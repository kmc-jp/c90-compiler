#ifndef KMC_C89_COMPILER_AST_METHOD_H
#define KMC_C89_COMPILER_AST_METHOD_H

#include "ast/lexical_elements.h"
#include "ast/expressions.h"
#include "ast/declarations.h"
#include "ast/statements.h"
#include "ast/external_definitions.h"
#include "ast/pool.h"

void ast_initialize_pool(void);
void ast_finalize_pool(void);

#endif  /* KMC_C89_COMPILER_AST_METHOD_H */
