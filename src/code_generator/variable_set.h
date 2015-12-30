#ifndef KMC_C89_COMPILER_VARIABLE_SET_H
#define KMC_C89_COMPILER_VARIABLE_SET_H

#include <llvm-c/Core.h>
#include "ast.h"
#include "pool.h"

LLVMValueRef get_variable(ValueVectorRef variable_set, AstRef ast);
LLVMValueRef get_variable_identifier(ValueVectorRef variable_set, AstIdentifierRef ast);

#endif /* KMC_C89_COMPILER_VARIABLE_SET_H */
