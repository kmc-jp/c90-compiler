#ifndef KMC_C89_COMPILER_VARIABLE_SET_H
#define KMC_C89_COMPILER_VARIABLE_SET_H

#include <llvm-c/Core.h>
#include "ast.h"
#include "vector.h"
#include "stdstring.h"

struct Variable {
  AstTokenRef name;
  LLVMTypeRef type;
  LLVMValueRef value;
};

typedef struct Variable *VariableRef;

#define VariableSetFunc(func) VECTORFUNC(VariableRef, func)

DECLARE_VECTOR(VariableRef)

typedef VECTORREF(VariableRef) VariableSetRef;

VariableRef get_variable(VariableSetRef variable_set, AstRef ast);

#endif /* KMC_C89_COMPILER_VARIABLE_SET_H */
