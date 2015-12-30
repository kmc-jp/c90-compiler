#include "code_generator.h"
#include "variable_set.h"
#include "pool.h"
#include "stdstring.h"
#include "ast/expressions_impl.h"
#include "ast/declarations_impl.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

ValueVectorRef get_arguments(
    ValueVectorRef variable_set,
    AstArgumentExpressionListRef argument_expression_list) {
  AstVectorRef argument_list = argument_expression_list->argument_list;
  ValueVectorRef value_vec = ValueVectorFunc(ctor)(NULL);
  AstRef *itr;
  AstRef *begin = AST_VECTOR_FUNC(begin)(argument_list);
  AstRef *end = AST_VECTOR_FUNC(end)(argument_list);
  for (itr = begin; itr != end; itr++) {
    ValueVectorFunc(push_back)(value_vec,
        get_variable(variable_set, *itr));
  }
  return value_vec;
}

LLVMValueRef make_value_initializer(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    LLVMTypeRef type, AstInitializerRef initializer) {
  return make_value(module, builder, variable_set, type, initializer->initializer);
}

LLVMValueRef make_value_assignment_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    LLVMTypeRef type, AstAssignmentExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef make_value_initializer_list(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    LLVMTypeRef type, AstInitializerListRef initializer_list) {
  ValueVectorRef value_vec = ValueVectorFunc(ctor)(NULL);
  AstRef *itr;
  AstRef *begin = AST_VECTOR_FUNC(begin)(initializer_list->initializer_vector);
  AstRef *end = AST_VECTOR_FUNC(end)(initializer_list->initializer_vector);
  for (itr = begin; itr != end; itr++) {
    ValueVectorFunc(push_back)(
        value_vec, make_value(module, builder, variable_set, type, *itr));
  }
  switch (LLVMGetTypeKind(type)) {
    case LLVMStructTypeKind:
      return LLVMConstStruct(
          ValueVectorFunc(data)(value_vec), ValueVectorFunc(size)(value_vec), false);
    case LLVMArrayTypeKind:
      return LLVMConstArray(
          LLVMGetElementType(type), ValueVectorFunc(data)(value_vec),
          ValueVectorFunc(size)(value_vec));
    default:
      return NULL;
  }
}

LLVMValueRef make_value(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    LLVMTypeRef type, AstRef ast) {
  switch (ast->tag) {
    case AST_INITIALIZER:
      return make_value_initializer(module, builder, variable_set, type,
          ast_get_initializer(ast));
    case AST_ASSIGNMENT_EXPRESSION:
      return make_value_assignment_expression(module, builder, variable_set, type,
          ast_get_assignment_expression(ast));
    case AST_INITIALIZER_LIST:
      return make_value_initializer_list(module, builder, variable_set, type,
          ast_get_initializer_list(ast));
    default:;
  }
}
