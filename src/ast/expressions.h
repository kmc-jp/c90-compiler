#ifndef KMC_C90_COMPILER_AST_EXPRESSION_H
#define KMC_C90_COMPILER_AST_EXPRESSION_H

#include "ast.h"

AstRef ast_make_primary_expression(AstRef primary_expression);
AstRef ast_make_postfix_expression(AstRef postfix);
AstRef ast_make_array_subscript_expression(AstRef array, AstRef subscript);
AstRef ast_make_function_call_expression(AstRef function, AstRef argument_list);
AstRef ast_make_member_access_expression(AstRef object, AstRef member);
AstRef ast_make_member_access_through_pointer_expression(
    AstRef object, AstRef member);
AstRef ast_make_postfix_increment_expression(AstRef postfix);
AstRef ast_make_postfix_decrement_expression(AstRef postfix);
AstRef ast_make_argument_expression_list(void);
AstRef ast_push_argument_expression_list(AstRef argument_list, AstRef argument);
AstRef ast_make_unary_expression(AstRef unary);
AstRef ast_make_prefix_increment_expression(AstRef unary);
AstRef ast_make_prefix_decrement_expression(AstRef unary);
AstRef ast_make_address_of_expression(AstRef cast);
AstRef ast_make_pointer_dereference_expression(AstRef cast);
AstRef ast_make_unary_plus_expression(AstRef cast);
AstRef ast_make_unary_minus_expression(AstRef cast);
AstRef ast_make_bitwise_not_expression(AstRef cast);
AstRef ast_make_logical_not_expression(AstRef cast);
AstRef ast_make_sizeof_expression(AstRef unary);
AstRef ast_make_sizeof_type_expression(AstRef type_name);
AstRef ast_make_cast_expression(AstRef cast);
AstRef ast_make_type_cast_expression(AstRef type_name, AstRef expression);
AstRef ast_make_multiplicative_expression(AstRef expression);
AstRef ast_make_product_expression(AstRef multiplicative, AstRef cast);
AstRef ast_make_division_expression(AstRef multiplicative, AstRef cast);
AstRef ast_make_modulo_expression(AstRef multiplicative, AstRef cast);
AstRef ast_make_additive_expression(AstRef expression);
AstRef ast_make_addition_expression(AstRef additive, AstRef multiplicative);
AstRef ast_make_subtraction_expression(AstRef additive, AstRef multiplicative);
AstRef ast_make_shift_expression(AstRef expression);
AstRef ast_make_left_shift_expression(AstRef shift, AstRef additive);
AstRef ast_make_right_shift_expression(AstRef shift, AstRef additive);
AstRef ast_make_relational_expression(AstRef expression);
AstRef ast_make_less_than_expression(AstRef relational, AstRef shift);
AstRef ast_make_greater_than_expression(AstRef relational, AstRef shift);
AstRef ast_make_less_than_or_equal_to_expression(
    AstRef relational, AstRef shift);
AstRef ast_make_greater_than_or_equal_to_expression(
    AstRef relational, AstRef shift);
AstRef ast_make_equality_expression(AstRef expression);
AstRef ast_make_equal_to_expression(AstRef equality, AstRef relational);
AstRef ast_make_not_equal_to_expression(AstRef equality, AstRef relational);
AstRef ast_make_bitwise_and_expression(AstRef expression);
AstRef ast_make_bitwise_and_operator_expression(
    AstRef bitwise_and, AstRef equality);
AstRef ast_make_bitwise_xor_expression(AstRef expression);
AstRef ast_make_bitwise_xor_operator_expression(
    AstRef bitwise_xor, AstRef bitwise_and);
AstRef ast_make_bitwise_or_expression(AstRef expression);
AstRef ast_make_bitwise_or_operator_expression(
    AstRef bitwise_or, AstRef bitwise_xor);
AstRef ast_make_logical_and_expression(AstRef expression);
AstRef ast_make_logical_and_operator_expression(
    AstRef logical_and, AstRef bitwise_or);
AstRef ast_make_logical_or_expression(AstRef expression);
AstRef ast_make_logical_or_operator_expression(
    AstRef logical_or, AstRef logical_and);
AstRef ast_make_conditional_expression(AstRef expression);
AstRef ast_make_conditional_operator_expression(
    AstRef logical_or, AstRef expression, AstRef conditional);
AstRef ast_make_assignment_expression(AstRef expression);
AstRef ast_make_basic_assignment_expression(AstRef unary, AstRef assignment);
AstRef ast_make_multiplication_assignment_expression(
    AstRef unary, AstRef assignment);
AstRef ast_make_division_assignment_expression(AstRef unary, AstRef assignment);
AstRef ast_make_modulo_assignment_expression(AstRef unary, AstRef assignment);
AstRef ast_make_addition_assignment_expression(AstRef unary, AstRef assignment);
AstRef ast_make_subtraction_assignment_expression(
    AstRef unary, AstRef assignment);
AstRef ast_make_left_shift_assignment_expression(
    AstRef unary, AstRef assignment);
AstRef ast_make_right_shift_assignment_expression(
    AstRef unary, AstRef assignment);
AstRef ast_make_bitwise_and_assignment_expression(
    AstRef unary, AstRef assignment);
AstRef ast_make_bitwise_xor_assignment_expression(
    AstRef unary, AstRef assignment);
AstRef ast_make_bitwise_or_assignment_expression(
    AstRef unary, AstRef assignment);
AstRef ast_make_expression(AstRef expression);
AstRef ast_make_comma_expression(AstRef expression, AstRef assignment);
AstRef ast_make_constant_expression(AstRef conditional);

#endif  /* KMC_C90_COMPILER_AST_EXPRESSION_H */
