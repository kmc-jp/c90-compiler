#include "is_method.h"
#include <assert.h>
#include "ast_impl.h"

#define DEFINE_AST_IS_METHOD(lower, upper) \
  bool ast_is_ ## lower(AstRef ast) { \
    assert(ast); \
    return ast->tag == AST_ ## upper; \
  }

DEFINE_AST_IS_METHOD(identifier, IDENTIFIER)
DEFINE_AST_IS_METHOD(constant, CONSTANT)
DEFINE_AST_IS_METHOD(floating_constant, FLOATING_CONSTANT)
DEFINE_AST_IS_METHOD(integer_constant, INTEGER_CONSTANT)
DEFINE_AST_IS_METHOD(enumeration_constant, ENUMERATION_CONSTANT)
DEFINE_AST_IS_METHOD(character_constant, CHARACTER_CONSTANT)
DEFINE_AST_IS_METHOD(string_literal, STRING_LITERAL)
DEFINE_AST_IS_METHOD(primary_expression, PRIMARY_EXPRESSION)
DEFINE_AST_IS_METHOD(postfix_expression, POSTFIX_EXPRESSION)
DEFINE_AST_IS_METHOD(array_subscript_expression, ARRAY_SUBSCRIPT_EXPRESSION)
DEFINE_AST_IS_METHOD(function_call_expression, FUNCTION_CALL_EXPRESSION)
DEFINE_AST_IS_METHOD(member_access_expression, MEMBER_ACCESS_EXPRESSION)
DEFINE_AST_IS_METHOD(member_access_through_pointer_expression, MEMBER_ACCESS_THROUGH_POINTER_EXPRESSION)
DEFINE_AST_IS_METHOD(postfix_increment_expression, POSTFIX_INCREMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(postfix_decrement_expression, POSTFIX_DECREMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(argument_expression_list, ARGUMENT_EXPRESSION_LIST)
DEFINE_AST_IS_METHOD(unary_expression, UNARY_EXPRESSION)
DEFINE_AST_IS_METHOD(prefix_increment_expression, PREFIX_INCREMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(prefix_decrement_expression, PREFIX_DECREMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(address_of_expression, ADDRESS_OF_EXPRESSION)
DEFINE_AST_IS_METHOD(pointer_dereference_expression, POINTER_DEREFERENCE_EXPRESSION)
DEFINE_AST_IS_METHOD(unary_plus_expression, UNARY_PLUS_EXPRESSION)
DEFINE_AST_IS_METHOD(unary_minus_expression, UNARY_MINUS_EXPRESSION)
DEFINE_AST_IS_METHOD(bitwise_not_expression, BITWISE_NOT_EXPRESSION)
DEFINE_AST_IS_METHOD(logical_not_expression, LOGICAL_NOT_EXPRESSION)
DEFINE_AST_IS_METHOD(sizeof_expression, SIZEOF_EXPRESSION)
DEFINE_AST_IS_METHOD(sizeof_type_expression, SIZEOF_TYPE_EXPRESSION)
DEFINE_AST_IS_METHOD(cast_expression, CAST_EXPRESSION)
DEFINE_AST_IS_METHOD(type_cast_expression, TYPE_CAST_EXPRESSION)
DEFINE_AST_IS_METHOD(multiplicative_expression, MULTIPLICATIVE_EXPRESSION)
DEFINE_AST_IS_METHOD(product_expression, PRODUCT_EXPRESSION)
DEFINE_AST_IS_METHOD(division_expression, DIVISION_EXPRESSION)
DEFINE_AST_IS_METHOD(modulo_expression, MODULO_EXPRESSION)
DEFINE_AST_IS_METHOD(additive_expression, ADDITIVE_EXPRESSION)
DEFINE_AST_IS_METHOD(addition_expression, ADDITION_EXPRESSION)
DEFINE_AST_IS_METHOD(subtraction_expression, SUBTRACTION_EXPRESSION)
DEFINE_AST_IS_METHOD(shift_expression, SHIFT_EXPRESSION)
DEFINE_AST_IS_METHOD(left_shift_expression, LEFT_SHIFT_EXPRESSION)
DEFINE_AST_IS_METHOD(right_shift_expression, RIGHT_SHIFT_EXPRESSION)
DEFINE_AST_IS_METHOD(relational_expression, RELATIONAL_EXPRESSION)
DEFINE_AST_IS_METHOD(less_than_expression, LESS_THAN_EXPRESSION)
DEFINE_AST_IS_METHOD(greater_than_expression, GREATER_THAN_EXPRESSION)
DEFINE_AST_IS_METHOD(less_than_or_equal_to_expression, LESS_THAN_OR_EQUAL_TO_EXPRESSION)
DEFINE_AST_IS_METHOD(greater_than_or_equal_to_expression, GREATER_THAN_OR_EQUAL_TO_EXPRESSION)
DEFINE_AST_IS_METHOD(equality_expression, EQUALITY_EXPRESSION)
DEFINE_AST_IS_METHOD(equal_to_expression, EQUAL_TO_EXPRESSION)
DEFINE_AST_IS_METHOD(not_equal_to_expression, NOT_EQUAL_TO_EXPRESSION)
DEFINE_AST_IS_METHOD(bitwise_and_expression, BITWISE_AND_EXPRESSION)
DEFINE_AST_IS_METHOD(bitwise_and_operator_expression, BITWISE_AND_OPERATOR_EXPRESSION)
DEFINE_AST_IS_METHOD(bitwise_xor_expression, BITWISE_XOR_EXPRESSION)
DEFINE_AST_IS_METHOD(bitwise_xor_operator_expression, BITWISE_XOR_OPERATOR_EXPRESSION)
DEFINE_AST_IS_METHOD(bitwise_or_expression, BITWISE_OR_EXPRESSION)
DEFINE_AST_IS_METHOD(bitwise_or_operator_expression, BITWISE_OR_OPERATOR_EXPRESSION)
DEFINE_AST_IS_METHOD(logical_and_expression, LOGICAL_AND_EXPRESSION)
DEFINE_AST_IS_METHOD(logical_and_operator_expression, LOGICAL_AND_OPERATOR_EXPRESSION)
DEFINE_AST_IS_METHOD(logical_or_expression, LOGICAL_OR_EXPRESSION)
DEFINE_AST_IS_METHOD(logical_or_operator_expression, LOGICAL_OR_OPERATOR_EXPRESSION)
DEFINE_AST_IS_METHOD(conditional_expression, CONDITIONAL_EXPRESSION)
DEFINE_AST_IS_METHOD(conditional_operator_expression, CONDITIONAL_OPERATOR_EXPRESSION)
DEFINE_AST_IS_METHOD(assignment_expression, ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(basic_assignment_expression, BASIC_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(multiplication_assignment_expression, MULTIPLICATION_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(division_assignment_expression, DIVISION_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(modulo_assignment_expression, MODULO_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(addition_assignment_expression, ADDITION_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(subtraction_assignment_expression, SUBTRACTION_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(left_shift_assignment_expression, LEFT_SHIFT_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(right_shift_assignment_expression, RIGHT_SHIFT_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(bitwise_and_assignment_expression, BITWISE_AND_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(bitwise_xor_assignment_expression, BITWISE_XOR_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(bitwise_or_assignment_expression, BITWISE_OR_ASSIGNMENT_EXPRESSION)
DEFINE_AST_IS_METHOD(expression, EXPRESSION)
DEFINE_AST_IS_METHOD(comma_expression, COMMA_EXPRESSION)
DEFINE_AST_IS_METHOD(constant_expression, CONSTANT_EXPRESSION)
DEFINE_AST_IS_METHOD(declaration, DECLARATION)
DEFINE_AST_IS_METHOD(declaration_specifier_list, DECLARATION_SPECIFIER_LIST)
DEFINE_AST_IS_METHOD(declaration_specifier, DECLARATION_SPECIFIER)
DEFINE_AST_IS_METHOD(init_declarator_list, INIT_DECLARATOR_LIST)
DEFINE_AST_IS_METHOD(init_declarator, INIT_DECLARATOR)
DEFINE_AST_IS_METHOD(declarator_with_initializer, DECLARATOR_WITH_INITIALIZER)
DEFINE_AST_IS_METHOD(storage_class_specifier, STORAGE_CLASS_SPECIFIER)
DEFINE_AST_IS_METHOD(type_specifier, TYPE_SPECIFIER)
DEFINE_AST_IS_METHOD(struct_or_union_specifier, STRUCT_OR_UNION_SPECIFIER)
DEFINE_AST_IS_METHOD(struct_or_union_definition, STRUCT_OR_UNION_DEFINITION)
DEFINE_AST_IS_METHOD(struct_or_union_declaration, STRUCT_OR_UNION_DECLARATION)
DEFINE_AST_IS_METHOD(struct_or_union, STRUCT_OR_UNION)
DEFINE_AST_IS_METHOD(struct_declaration_list, STRUCT_DECLARATION_LIST)
DEFINE_AST_IS_METHOD(struct_declaration, STRUCT_DECLARATION)
DEFINE_AST_IS_METHOD(specifier_qualifier_list, SPECIFIER_QUALIFIER_LIST)
DEFINE_AST_IS_METHOD(specifier_qualifier, SPECIFIER_QUALIFIER)
DEFINE_AST_IS_METHOD(struct_declarator_list, STRUCT_DECLARATOR_LIST)
DEFINE_AST_IS_METHOD(struct_declarator, STRUCT_DECLARATOR)
DEFINE_AST_IS_METHOD(bit_field_declarator, BIT_FIELD_DECLARATOR)
DEFINE_AST_IS_METHOD(enum_specifier, ENUM_SPECIFIER)
DEFINE_AST_IS_METHOD(enum_definition, ENUM_DEFINITION)
DEFINE_AST_IS_METHOD(enum_declaration, ENUM_DECLARATION)
DEFINE_AST_IS_METHOD(enumerator_list, ENUMERATOR_LIST)
DEFINE_AST_IS_METHOD(enumerator, ENUMERATOR)
DEFINE_AST_IS_METHOD(enumerator_with_initializer, ENUMERATOR_WITH_INITIALIZER)
DEFINE_AST_IS_METHOD(type_qualifier, TYPE_QUALIFIER)
DEFINE_AST_IS_METHOD(declarator, DECLARATOR)
DEFINE_AST_IS_METHOD(direct_declarator, DIRECT_DECLARATOR)
DEFINE_AST_IS_METHOD(array_declarator, ARRAY_DECLARATOR)
DEFINE_AST_IS_METHOD(function_declarator, FUNCTION_DECLARATOR)
DEFINE_AST_IS_METHOD(old_style_function_declarator, OLD_STYLE_FUNCTION_DECLARATOR)
DEFINE_AST_IS_METHOD(pointer, POINTER)
DEFINE_AST_IS_METHOD(type_qualifier_list, TYPE_QUALIFIER_LIST)
DEFINE_AST_IS_METHOD(parameter_type_list, PARAMETER_TYPE_LIST)
DEFINE_AST_IS_METHOD(variadic_parameter_list, VARIADIC_PARAMETER_LIST)
DEFINE_AST_IS_METHOD(parameter_list, PARAMETER_LIST)
DEFINE_AST_IS_METHOD(parameter_declaration, PARAMETER_DECLARATION)
DEFINE_AST_IS_METHOD(parameter_concrete_declaration, PARAMETER_CONCRETE_DECLARATION)
DEFINE_AST_IS_METHOD(parameter_abstract_declaration, PARAMETER_ABSTRACT_DECLARATION)
DEFINE_AST_IS_METHOD(identifier_list, IDENTIFIER_LIST)
DEFINE_AST_IS_METHOD(type_name, TYPE_NAME)
DEFINE_AST_IS_METHOD(abstract_declarator, ABSTRACT_DECLARATOR)
DEFINE_AST_IS_METHOD(pointer_abstract_declarator, POINTER_ABSTRACT_DECLARATOR)
DEFINE_AST_IS_METHOD(direct_abstract_declarator, DIRECT_ABSTRACT_DECLARATOR)
DEFINE_AST_IS_METHOD(array_abstract_declarator, ARRAY_ABSTRACT_DECLARATOR)
DEFINE_AST_IS_METHOD(function_abstract_declarator, FUNCTION_ABSTRACT_DECLARATOR)
DEFINE_AST_IS_METHOD(typedef_name, TYPEDEF_NAME)
DEFINE_AST_IS_METHOD(initializer, INITIALIZER)
DEFINE_AST_IS_METHOD(initializer_list, INITIALIZER_LIST)
DEFINE_AST_IS_METHOD(statement, STATEMENT)
DEFINE_AST_IS_METHOD(labeled_statement, LABELED_STATEMENT)
DEFINE_AST_IS_METHOD(identifier_labeled_statement, IDENTIFIER_LABELED_STATEMENT)
DEFINE_AST_IS_METHOD(case_labeled_statement, CASE_LABELED_STATEMENT)
DEFINE_AST_IS_METHOD(default_labeled_statement, DEFAULT_LABELED_STATEMENT)
DEFINE_AST_IS_METHOD(compound_statement, COMPOUND_STATEMENT)
DEFINE_AST_IS_METHOD(declaration_list, DECLARATION_LIST)
DEFINE_AST_IS_METHOD(statement_list, STATEMENT_LIST)
DEFINE_AST_IS_METHOD(expression_statement, EXPRESSION_STATEMENT)
DEFINE_AST_IS_METHOD(selection_statement, SELECTION_STATEMENT)
DEFINE_AST_IS_METHOD(if_statement, IF_STATEMENT)
DEFINE_AST_IS_METHOD(if_else_statement, IF_ELSE_STATEMENT)
DEFINE_AST_IS_METHOD(switch_statement, SWITCH_STATEMENT)
DEFINE_AST_IS_METHOD(iteration_statement, ITERATION_STATEMENT)
DEFINE_AST_IS_METHOD(while_statement, WHILE_STATEMENT)
DEFINE_AST_IS_METHOD(do_while_statement, DO_WHILE_STATEMENT)
DEFINE_AST_IS_METHOD(for_statement, FOR_STATEMENT)
DEFINE_AST_IS_METHOD(jump_statement, JUMP_STATEMENT)
DEFINE_AST_IS_METHOD(goto_jump_statement, GOTO_JUMP_STATEMENT)
DEFINE_AST_IS_METHOD(continue_jump_statement, CONTINUE_JUMP_STATEMENT)
DEFINE_AST_IS_METHOD(break_jump_statement, BREAK_JUMP_STATEMENT)
DEFINE_AST_IS_METHOD(return_jump_statement, RETURN_JUMP_STATEMENT)
DEFINE_AST_IS_METHOD(void_return_jump_statement, VOID_RETURN_JUMP_STATEMENT)
DEFINE_AST_IS_METHOD(translation_unit, TRANSLATION_UNIT)
DEFINE_AST_IS_METHOD(external_declaration, EXTERNAL_DECLARATION)
DEFINE_AST_IS_METHOD(function_definition, FUNCTION_DEFINITION)
DEFINE_AST_IS_METHOD(vector, VECTOR)
DEFINE_AST_IS_METHOD(token, TOKEN)
