#ifndef KMC_C89_COMPILER_CODE_GENERATOR_H
#define KMC_C89_COMPILER_CODE_GENERATOR_H

#include <llvm-c/Core.h>
#include "ast.h"
#include "ast/external_definitions.h"
#include "utility.h"
#include "vector.h"

#define ParameterTypeFunc(func) VECTORFUNC(LLVMTypeRef, func)

DECLARE_VECTOR(LLVMTypeRef)

typedef VECTORREF(LLVMTypeRef) ParameterTypeRef;

void translation_unit(LLVMModuleRef module, AstTranslationUnitRef translation_unit);
LLVMTypeRef get_type(AstRef ast);
ParameterTypeRef get_parameter_types(AstRef ast);
void build_block(LLVMModuleRef module, LLVMBuilderRef builder, AstRef ast);

#endif /* KMC_C89_COMPILER_CODE_GENERATOR_H */
