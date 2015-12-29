#include "code_generator.h"
#include "variable_set.h"
#include "stdstring.h"
#include "ast/expressions_impl.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

DEFINE_VECTOR(LLVMValueRef)

ValueVectorRef get_arguments(
    VariableSetRef variable_set,
    AstArgumentExpressionListRef argument_expression_list) {
  AstVectorRef argument_list = argument_expression_list->argument_list;
  int i;
  ValueVectorRef value_vec = ValueVectorFunc(ctor)(NULL);
  for (i = 0; i < (int)AST_VECTOR_FUNC(size)(argument_list); i++) {
    ValueVectorFunc(push_back)(value_vec,
        get_variable(variable_set, AST_VECTOR_FUNC(at)(argument_list, i))->value);
  }
  return value_vec;
}
