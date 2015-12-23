#ifndef KMC_C89_COMPILER_AST_IS_METHOD_H
#define KMC_C89_COMPILER_AST_IS_METHOD_H

#include "../ast.h"
#include "../utility.h"

bool ast_is_identifier(AstRef ast);
bool ast_is_constant(AstRef ast);
bool ast_is_floating_constant(AstRef ast);
bool ast_is_integer_constant(AstRef ast);
bool ast_is_enumeration_constant(AstRef ast);
bool ast_is_character_constant(AstRef ast);
bool ast_is_string_literal(AstRef ast);
bool ast_is_primary_expression(AstRef ast);
bool ast_is_postfix_expression(AstRef ast);
bool ast_is_argument_expression_list(AstRef ast);
bool ast_is_unary_expression(AstRef ast);
bool ast_is_unary_operator(AstRef ast);
bool ast_is_cast_expression(AstRef ast);
bool ast_is_multiplicative_expression(AstRef ast);
bool ast_is_additive_expression(AstRef ast);
bool ast_is_shift_expression(AstRef ast);
bool ast_is_relational_expression(AstRef ast);
bool ast_is_equality_expression(AstRef ast);
bool ast_is_and_expression(AstRef ast);
bool ast_is_exclusive_or_expression(AstRef ast);
bool ast_is_inclusive_or_expression(AstRef ast);
bool ast_is_logical_and_expression(AstRef ast);
bool ast_is_logical_or_expression(AstRef ast);
bool ast_is_conditional_expression(AstRef ast);
bool ast_is_assignment_expression(AstRef ast);
bool ast_is_assignment_operator(AstRef ast);
bool ast_is_expression(AstRef ast);
bool ast_is_constant_expression(AstRef ast);
bool ast_is_declaration(AstRef ast);
bool ast_is_declaration_specifiers(AstRef ast);
bool ast_is_init_declarator_list(AstRef ast);
bool ast_is_init_declarator(AstRef ast);
bool ast_is_storage_class_specifier(AstRef ast);
bool ast_is_type_specifier(AstRef ast);
bool ast_is_struct_or_union_specifier(AstRef ast);
bool ast_is_struct_or_union_definition(AstRef ast);
bool ast_is_struct_or_union_declaration(AstRef ast);
bool ast_is_struct_or_union(AstRef ast);
bool ast_is_struct_declaration_list(AstRef ast);
bool ast_is_struct_declaration(AstRef ast);
bool ast_is_specifier_qualifier_list(AstRef ast);
bool ast_is_specifier_qualifier(AstRef ast);
bool ast_is_struct_declarator_list(AstRef ast);
bool ast_is_struct_declarator(AstRef ast);
bool ast_is_bit_field_declarator(AstRef ast);
bool ast_is_enum_specifier(AstRef ast);
bool ast_is_enum_definition(AstRef ast);
bool ast_is_enum_declaration(AstRef ast);
bool ast_is_enumerator_list(AstRef ast);
bool ast_is_enumerator(AstRef ast);
bool ast_is_type_qualifier(AstRef ast);
bool ast_is_declarator(AstRef ast);
bool ast_is_direct_declarator(AstRef ast);
bool ast_is_pointer(AstRef ast);
bool ast_is_type_qualifier_list(AstRef ast);
bool ast_is_parameter_type_list(AstRef ast);
bool ast_is_parameter_list(AstRef ast);
bool ast_is_parameter_declaration(AstRef ast);
bool ast_is_identifier_list(AstRef ast);
bool ast_is_type_name(AstRef ast);
bool ast_is_abstract_declarator(AstRef ast);
bool ast_is_direct_abstract_declarator(AstRef ast);
bool ast_is_typedef_name(AstRef ast);
bool ast_is_initializer(AstRef ast);
bool ast_is_initializer_list(AstRef ast);
bool ast_is_statement(AstRef ast);
bool ast_is_labeled_statement(AstRef ast);
bool ast_is_compound_statement(AstRef ast);
bool ast_is_declaration_list(AstRef ast);
bool ast_is_statement_list(AstRef ast);
bool ast_is_expression_statement(AstRef ast);
bool ast_is_selection_statement(AstRef ast);
bool ast_is_iteration_statement(AstRef ast);
bool ast_is_jump_statement(AstRef ast);
bool ast_is_translation_unit(AstRef ast);
bool ast_is_external_declaration(AstRef ast);
bool ast_is_function_definition(AstRef ast);

bool ast_is_vector(AstRef ast);
bool ast_is_token(AstRef ast);

#endif  /* KMC_C89_COMPILER_AST_IS_METHOD_H */
