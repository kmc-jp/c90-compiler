#include "is_method.h"
#include <assert.h>
#include "ast_impl.h"

bool ast_is_identifier(AstRef ast) {
  assert(ast);
  return ast->tag == AST_IDENTIFIER;
}

bool ast_is_constant(AstRef ast) {
  assert(ast);
  return ast->tag == AST_CONSTANT;
}

bool ast_is_floating_constant(AstRef ast) {
  assert(ast);
  return ast->tag == AST_FLOATING_CONSTANT;
}

bool ast_is_integer_constant(AstRef ast) {
  assert(ast);
  return ast->tag == AST_INTEGER_CONSTANT;
}

bool ast_is_enumeration_constant(AstRef ast) {
  assert(ast);
  return ast->tag == AST_ENUMERATION_CONSTANT;
}

bool ast_is_character_constant(AstRef ast) {
  assert(ast);
  return ast->tag == AST_CHARACTER_CONSTANT;
}

bool ast_is_string_literal(AstRef ast) {
  assert(ast);
  return ast->tag == AST_STRING_LITERAL;
}

bool ast_is_primary_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_PRIMARY_EXPRESSION;
}

bool ast_is_postfix_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_POSTFIX_EXPRESSION;
}

bool ast_is_argument_expression_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_ARGUMENT_EXPRESSION_LIST;
}

bool ast_is_unary_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_UNARY_EXPRESSION;
}

bool ast_is_unary_operator(AstRef ast) {
  assert(ast);
  return ast->tag == AST_UNARY_OPERATOR;
}

bool ast_is_cast_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_CAST_EXPRESSION;
}

bool ast_is_multiplicative_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_MULTIPLICATIVE_EXPRESSION;
}

bool ast_is_additive_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_ADDITIVE_EXPRESSION;
}

bool ast_is_shift_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_SHIFT_EXPRESSION;
}

bool ast_is_relational_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_RELATIONAL_EXPRESSION;
}

bool ast_is_equality_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_EQUALITY_EXPRESSION;
}

bool ast_is_and_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_AND_EXPRESSION;
}

bool ast_is_exclusive_or_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_EXCLUSIVE_OR_EXPRESSION;
}

bool ast_is_inclusive_or_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_INCLUSIVE_OR_EXPRESSION;
}

bool ast_is_logical_and_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_LOGICAL_AND_EXPRESSION;
}

bool ast_is_logical_or_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_LOGICAL_OR_EXPRESSION;
}

bool ast_is_conditional_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_CONDITIONAL_EXPRESSION;
}

bool ast_is_assignment_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_ASSIGNMENT_EXPRESSION;
}

bool ast_is_assignment_operator(AstRef ast) {
  assert(ast);
  return ast->tag == AST_ASSIGNMENT_OPERATOR;
}

bool ast_is_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_EXPRESSION;
}

bool ast_is_constant_expression(AstRef ast) {
  assert(ast);
  return ast->tag == AST_CONSTANT_EXPRESSION;
}

bool ast_is_declaration(AstRef ast) {
  assert(ast);
  return ast->tag == AST_DECLARATION;
}

bool ast_is_declaration_specifiers(AstRef ast) {
  assert(ast);
  return ast->tag == AST_DECLARATION_SPECIFIERS;
}

bool ast_is_init_declarator_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_INIT_DECLARATOR_LIST;
}

bool ast_is_init_declarator(AstRef ast) {
  assert(ast);
  return ast->tag == AST_INIT_DECLARATOR;
}

bool ast_is_storage_class_specifier(AstRef ast) {
  assert(ast);
  return ast->tag == AST_STORAGE_CLASS_SPECIFIER;
}

bool ast_is_type_specifier(AstRef ast) {
  assert(ast);
  return ast->tag == AST_TYPE_SPECIFIER;
}

bool ast_is_struct_or_union_specifier(AstRef ast) {
  assert(ast);
  return ast->tag == AST_STRUCT_OR_UNION_SPECIFIER;
}

bool ast_is_struct_or_union(AstRef ast) {
  assert(ast);
  return ast->tag == AST_STRUCT_OR_UNION;
}

bool ast_is_struct_declaration_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_STRUCT_DECLARATION_LIST;
}

bool ast_is_struct_declaration(AstRef ast) {
  assert(ast);
  return ast->tag == AST_STRUCT_DECLARATION;
}

bool ast_is_specifier_qualifier_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_SPECIFIER_QUALIFIER_LIST;
}

bool ast_is_struct_declarator_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_STRUCT_DECLARATOR_LIST;
}

bool ast_is_struct_declarator(AstRef ast) {
  assert(ast);
  return ast->tag == AST_STRUCT_DECLARATOR;
}

bool ast_is_enum_specifier(AstRef ast) {
  assert(ast);
  return ast->tag == AST_ENUM_SPECIFIER;
}

bool ast_is_enumerator_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_ENUMERATOR_LIST;
}

bool ast_is_enumerator(AstRef ast) {
  assert(ast);
  return ast->tag == AST_ENUMERATOR;
}

bool ast_is_type_qualifier(AstRef ast) {
  assert(ast);
  return ast->tag == AST_TYPE_QUALIFIER;
}

bool ast_is_declarator(AstRef ast) {
  assert(ast);
  return ast->tag == AST_DECLARATOR;
}

bool ast_is_direct_declarator(AstRef ast) {
  assert(ast);
  return ast->tag == AST_DIRECT_DECLARATOR;
}

bool ast_is_pointer(AstRef ast) {
  assert(ast);
  return ast->tag == AST_POINTER;
}

bool ast_is_type_qualifier_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_TYPE_QUALIFIER_LIST;
}

bool ast_is_parameter_type_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_PARAMETER_TYPE_LIST;
}

bool ast_is_parameter_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_PARAMETER_LIST;
}

bool ast_is_parameter_declaration(AstRef ast) {
  assert(ast);
  return ast->tag == AST_PARAMETER_DECLARATION;
}

bool ast_is_identifier_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_IDENTIFIER_LIST;
}

bool ast_is_type_name(AstRef ast) {
  assert(ast);
  return ast->tag == AST_TYPE_NAME;
}

bool ast_is_abstract_declarator(AstRef ast) {
  assert(ast);
  return ast->tag == AST_ABSTRACT_DECLARATOR;
}

bool ast_is_direct_abstract_declarator(AstRef ast) {
  assert(ast);
  return ast->tag == AST_DIRECT_ABSTRACT_DECLARATOR;
}

bool ast_is_typedef_name(AstRef ast) {
  assert(ast);
  return ast->tag == AST_TYPEDEF_NAME;
}

bool ast_is_initializer(AstRef ast) {
  assert(ast);
  return ast->tag == AST_INITIALIZER;
}

bool ast_is_initializer_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_INITIALIZER_LIST;
}

bool ast_is_statement(AstRef ast) {
  assert(ast);
  return ast->tag == AST_STATEMENT;
}

bool ast_is_labeled_statement(AstRef ast) {
  assert(ast);
  return ast->tag == AST_LABELED_STATEMENT;
}

bool ast_is_compound_statement(AstRef ast) {
  assert(ast);
  return ast->tag == AST_COMPOUND_STATEMENT;
}

bool ast_is_declaration_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_DECLARATION_LIST;
}

bool ast_is_statement_list(AstRef ast) {
  assert(ast);
  return ast->tag == AST_STATEMENT_LIST;
}

bool ast_is_expression_statement(AstRef ast) {
  assert(ast);
  return ast->tag == AST_EXPRESSION_STATEMENT;
}

bool ast_is_selection_statement(AstRef ast) {
  assert(ast);
  return ast->tag == AST_SELECTION_STATEMENT;
}

bool ast_is_iteration_statement(AstRef ast) {
  assert(ast);
  return ast->tag == AST_ITERATION_STATEMENT;
}

bool ast_is_jump_statement(AstRef ast) {
  assert(ast);
  return ast->tag == AST_JUMP_STATEMENT;
}

bool ast_is_translation_unit(AstRef ast) {
  assert(ast);
  return ast->tag == AST_TRANSLATION_UNIT;
}

bool ast_is_external_declaration(AstRef ast) {
  assert(ast);
  return ast->tag == AST_EXTERNAL_DECLARATION;
}

bool ast_is_function_definition(AstRef ast) {
  assert(ast);
  return ast->tag == AST_FUNCTION_DEFINITION;
}

bool ast_is_vector(AstRef ast) {
  assert(ast);
  return ast->tag == AST_VECTOR;
}
