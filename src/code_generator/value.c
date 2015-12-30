#include "code_generator.h"
#include "variable_set.h"
#include "pool.h"
#include "stdstring.h"
#include "ast/expressions_impl.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

ValueVectorRef get_arguments(
    VariableSetRef variable_set,
    AstArgumentExpressionListRef argument_expression_list) {
  AstVectorRef argument_list = argument_expression_list->argument_list;
  ValueVectorRef value_vec = ValueVectorFunc(ctor)(NULL);
  AstRef *itr;
  AstRef *begin = AST_VECTOR_FUNC(begin)(argument_list);
  AstRef *end = AST_VECTOR_FUNC(end)(argument_list);
  for (itr = begin; itr != end; itr++) {
    ValueVectorFunc(push_back)(value_vec,
        get_variable(variable_set, *itr)->value);
  }
  return value_vec;
}
