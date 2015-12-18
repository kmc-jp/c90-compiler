#ifndef KMC_C89_COMPILER_AST_EXPRESSION_H
#define KMC_C89_COMPILER_AST_EXPRESSION_H

#include "../ast.h"

AstRef ast_make_primary_expression();
AstRef ast_make_postfix_expression();
AstRef ast_make_index_access_expression();
AstRef ast_make_function_call_expression();
AstRef ast_make_dot_access_expression();
AstRef ast_make_arrow_access_expression();
AstRef ast_make_postfix_increment_expression();
AstRef ast_make_postfix_decrement_expression();
AstRef ast_make_argument_expression_list();
AstRef ast_make_unary_expression();
AstRef ast_make_prefix_increment_expression();
AstRef ast_make_prefix_decrement_expression();
AstRef ast_make_unary_operator_expression();
AstRef ast_make_sizeof_expression();
AstRef ast_make_sizeof_type_expression();
AstRef ast_make_address_expression();
AstRef ast_make_dereference_expression();
AstRef ast_make_unary_plus_expression();
AstRef ast_make_unary_minus_expression();
AstRef ast_make_complement_expression();
AstRef ast_make_logical_negate_expression();
AstRef ast_make_cast_or_unary_expression();
AstRef ast_make_cast_expression();
AstRef ast_make_multiplicative_expression();
AstRef ast_make_multiply_expression();
AstRef ast_make_divide_expression();
AstRef ast_make_modulo_expression();
AstRef ast_make_additive_expression();
AstRef ast_make_add_expression();
AstRef ast_make_subtract_expression();
AstRef ast_make_shift_expression();
AstRef ast_make_left_shift_expression();
AstRef ast_make_right_shift_expression();
AstRef ast_make_relational_expression();
AstRef ast_make_less_than_expression();
AstRef ast_make_greater_than_expression();
AstRef ast_make_less_than_or_equal_to_expression();
AstRef ast_make_greater_than_or_equal_to_expression();
AstRef ast_make_equality_expression();
AstRef ast_make_equal_to_expression();
AstRef ast_make_not_equal_to_expression();
AstRef ast_make_and_expression();
AstRef ast_make_exclusive_or_expression();
AstRef ast_make_inclusive_or_expression();
AstRef ast_make_logical_and_expression();
AstRef ast_make_logical_or_expression();
AstRef ast_make_conditional_expression();
AstRef ast_make_assignment_expression();
AstRef ast_make_assignment_operator();
AstRef ast_make_expression();
AstRef ast_make_constant_expression();

#endif  /* KMC_C89_COMPILER_AST_EXPRESSION_H */