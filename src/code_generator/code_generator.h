#ifndef KMC_C89_COMPILER_CODE_GENERATOR_H
#define KMC_C89_COMPILER_CODE_GENERATOR_H

#include <llvm-c/Core.h>
#include "ast.h"
#include "ast/external_definitions.h"
#include "utility.h"
#include "vector.h"
#include "stdstring.h"
#include "variable_set.h"
#include "pool.h"

void translation_unit(LLVMModuleRef module, AstTranslationUnitRef translation_unit);
LLVMTypeRef get_type(AstRef ast);
LLVMTypeRef get_type_with_type(LLVMTypeRef base_type, AstRef ast);
TypeVectorRef get_parameter_types(AstRef ast);
LLVMTypeRef get_function_type(AstFunctionDefinitionRef function_definition);
AstTokenRef get_name(AstRef ast);
ValueVectorRef get_arguments(ValueVectorRef variable_set, AstArgumentExpressionListRef ast);
void build_block(LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set, AstRef ast);
LLVMValueRef build_expression(LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set, AstRef ast);
LLVMValueRef make_value(LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set, LLVMTypeRef type, AstRef ast);

#endif /* KMC_C89_COMPILER_CODE_GENERATOR_H */
