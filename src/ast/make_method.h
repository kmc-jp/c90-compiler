#ifndef KMC_C89_COMPILER_AST_MAKE_METHOD_H
#define KMC_C89_COMPILER_AST_MAKE_METHOD_H

#include "../ast.h"
#include "../utility.h"

AstRef ast_make_identifier(AstRef token);
AstRef ast_make_constant(AstRef constant);
AstRef ast_make_floating_constant(AstRef token);
AstRef ast_make_integer_constant(AstRef token);
AstRef ast_make_enumeration_constant(AstRef identifier);
AstRef ast_make_character_constant(AstRef token);
AstRef ast_make_string_literal(AstRef token);
AstRef ast_make_primary_expression();
AstRef ast_make_postfix_expression();
AstRef ast_make_argument_expression_list();
AstRef ast_make_unary_expression();
AstRef ast_make_unary_operator();
AstRef ast_make_cast_expression();
AstRef ast_make_multiplicative_expression();
AstRef ast_make_additive_expression();
AstRef ast_make_shift_expression();
AstRef ast_make_relational_expression();
AstRef ast_make_equality_expression();
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
AstRef ast_make_declaration();
AstRef ast_make_declaration_specifiers();
AstRef ast_make_init_declarator_list();
AstRef ast_make_init_declarator();
AstRef ast_make_storage_class_specifier();
AstRef ast_make_type_specifier();
AstRef ast_make_struct_or_union_specifier();
AstRef ast_make_struct_or_union();
AstRef ast_make_struct_declaration_list();
AstRef ast_make_struct_declaration();
AstRef ast_make_specifier_qualifier_list();
AstRef ast_make_struct_declarator_list();
AstRef ast_make_struct_declarator();
AstRef ast_make_enum_specifier();
AstRef ast_make_enumerator_list();
AstRef ast_make_enumerator();
AstRef ast_make_type_qualifier();
AstRef ast_make_declarator();
AstRef ast_make_direct_declarator();
AstRef ast_make_pointer();
AstRef ast_make_type_qualifier_list();
AstRef ast_make_parameter_type_list();
AstRef ast_make_parameter_list();
AstRef ast_make_parameter_declaration();
AstRef ast_make_identifier_list();
AstRef ast_make_type_name();
AstRef ast_make_abstract_declarator();
AstRef ast_make_direct_abstract_declarator();
AstRef ast_make_typedef_name();
AstRef ast_make_initializer();
AstRef ast_make_initializer_list();
AstRef ast_make_statement();
AstRef ast_make_labeled_statement();
AstRef ast_make_compound_statement();
AstRef ast_make_declaration_list();
AstRef ast_make_statement_list();
AstRef ast_make_expression_statement();
AstRef ast_make_selection_statement();
AstRef ast_make_iteration_statement();
AstRef ast_make_jump_statement();
AstRef ast_make_translation_unit();
AstRef ast_make_external_declaration();
AstRef ast_make_function_definition();

AstRef ast_make_vector(void);
AstRef ast_push_vector(AstRef vector, AstRef element);
AstRef ast_make_token(const char* src, size_t length);

#endif  /* KMC_C89_COMPILER_AST_MAKE_METHOD_H */
