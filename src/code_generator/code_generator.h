#ifndef KMC_C89_COMPILER_CODE_GENERATOR_H
#define KMC_C89_COMPILER_CODE_GENERATOR_H

#include <llvm-c/Core.h>
#include "ast.h"
#include "ast/external_definitions.h"
#include "utility.h"
#include "vector.h"
#include "stdstring.h"
#include "variable_set.h"

#define TypeVectorFunc(func) VECTORFUNC(LLVMTypeRef, func)

DECLARE_VECTOR(LLVMTypeRef)
typedef VECTORREF(LLVMTypeRef) TypeVectorRef;

DECLARE_VECTOR(LLVMValueRef)
typedef VECTORREF(LLVMValueRef) ValueVectorRef;

void translation_unit(LLVMModuleRef module, AstTranslationUnitRef translation_unit);
LLVMTypeRef get_type(AstRef ast);
TypeVectorRef get_parameter_types(AstRef ast);
LLVMTypeRef get_function_type(AstFunctionDefinitionRef function_definition);
AstTokenRef get_name(AstRef ast);
void build_block(LLVMModuleRef module, LLVMBuilderRef builder, VariableSetRef variable_set, AstRef ast);
LLVMValueRef build_expression(LLVMModuleRef module, LLVMBuilderRef builder, VariableSetRef variable_set, AstRef ast);

#endif /* KMC_C89_COMPILER_CODE_GENERATOR_H */
