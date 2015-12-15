#include "get_method.h"
#include <assert.h>
#include "is_method.h"

AstIdentifierRef ast_get_identifier(AstRef ast) {
  assert(ast);
  if (ast_is_identifier(ast)) {
    return ast->data.identifier;
  }
  return NULL;
}

AstConstantRef ast_get_constant(AstRef ast) {
  assert(ast);
  if (ast_is_constant(ast)) {
    return ast->data.constant;
  }
  return NULL;
}

AstFloatingConstantRef ast_get_floating_constant(AstRef ast) {
  assert(ast);
  if (ast_is_floating_constant(ast)) {
    return ast->data.floating_constant;
  }
  return NULL;
}

AstIntegerConstantRef ast_get_integer_constant(AstRef ast) {
  assert(ast);
  if (ast_is_integer_constant(ast)) {
    return ast->data.integer_constant;
  }
  return NULL;
}

AstEnumerationConstantRef ast_get_enumeration_constant(AstRef ast) {
  assert(ast);
  if (ast_is_enumeration_constant(ast)) {
    return ast->data.enumeration_constant;
  }
  return NULL;
}

AstCharacterConstantRef ast_get_character_constant(AstRef ast) {
  assert(ast);
  if (ast_is_character_constant(ast)) {
    return ast->data.character_constant;
  }
  return NULL;
}

AstStringLiteralRef ast_get_string_literal(AstRef ast) {
  assert(ast);
  if (ast_is_string_literal(ast)) {
    return ast->data.string_literal;
  }
  return NULL;
}

AstPrimaryExpressionRef ast_get_primary_expression(AstRef ast) {
  assert(ast);
  if (ast_is_primary_expression(ast)) {
    return ast->data.primary_expression;
  }
  return NULL;
}

AstPostfixExpressionRef ast_get_postfix_expression(AstRef ast) {
  assert(ast);
  if (ast_is_postfix_expression(ast)) {
    return ast->data.postfix_expression;
  }
  return NULL;
}

AstArgumentExpressionListRef ast_get_argument_expression_list(AstRef ast) {
  assert(ast);
  if (ast_is_argument_expression_list(ast)) {
    return ast->data.argument_expression_list;
  }
  return NULL;
}

AstUnaryExpressionRef ast_get_unary_expression(AstRef ast) {
  assert(ast);
  if (ast_is_unary_expression(ast)) {
    return ast->data.unary_expression;
  }
  return NULL;
}

AstUnaryOperatorRef ast_get_unary_operator(AstRef ast) {
  assert(ast);
  if (ast_is_unary_operator(ast)) {
    return ast->data.unary_operator;
  }
  return NULL;
}

AstCastExpressionRef ast_get_cast_expression(AstRef ast) {
  assert(ast);
  if (ast_is_cast_expression(ast)) {
    return ast->data.cast_expression;
  }
  return NULL;
}

AstMultiplicativeExpressionRef ast_get_multiplicative_expression(AstRef ast) {
  assert(ast);
  if (ast_is_multiplicative_expression(ast)) {
    return ast->data.multiplicative_expression;
  }
  return NULL;
}

AstAdditiveExpressionRef ast_get_additive_expression(AstRef ast) {
  assert(ast);
  if (ast_is_additive_expression(ast)) {
    return ast->data.additive_expression;
  }
  return NULL;
}

AstShiftExpressionRef ast_get_shift_expression(AstRef ast) {
  assert(ast);
  if (ast_is_shift_expression(ast)) {
    return ast->data.shift_expression;
  }
  return NULL;
}

AstRelationalExpressionRef ast_get_relational_expression(AstRef ast) {
  assert(ast);
  if (ast_is_relational_expression(ast)) {
    return ast->data.relational_expression;
  }
  return NULL;
}

AstEqualityExpressionRef ast_get_equality_expression(AstRef ast) {
  assert(ast);
  if (ast_is_equality_expression(ast)) {
    return ast->data.equality_expression;
  }
  return NULL;
}

AstAndExpressionRef ast_get_and_expression(AstRef ast) {
  assert(ast);
  if (ast_is_and_expression(ast)) {
    return ast->data.and_expression;
  }
  return NULL;
}

AstExclusiveOrExpressionRef ast_get_exclusive_or_expression(AstRef ast) {
  assert(ast);
  if (ast_is_exclusive_or_expression(ast)) {
    return ast->data.exclusive_or_expression;
  }
  return NULL;
}

AstInclusiveOrExpressionRef ast_get_inclusive_or_expression(AstRef ast) {
  assert(ast);
  if (ast_is_inclusive_or_expression(ast)) {
    return ast->data.inclusive_or_expression;
  }
  return NULL;
}

AstLogicalAndExpressionRef ast_get_logical_and_expression(AstRef ast) {
  assert(ast);
  if (ast_is_logical_and_expression(ast)) {
    return ast->data.logical_and_expression;
  }
  return NULL;
}

AstLogicalOrExpressionRef ast_get_logical_or_expression(AstRef ast) {
  assert(ast);
  if (ast_is_logical_or_expression(ast)) {
    return ast->data.logical_or_expression;
  }
  return NULL;
}

AstConditionalExpressionRef ast_get_conditional_expression(AstRef ast) {
  assert(ast);
  if (ast_is_conditional_expression(ast)) {
    return ast->data.conditional_expression;
  }
  return NULL;
}

AstAssignmentExpressionRef ast_get_assignment_expression(AstRef ast) {
  assert(ast);
  if (ast_is_assignment_expression(ast)) {
    return ast->data.assignment_expression;
  }
  return NULL;
}

AstAssignmentOperatorRef ast_get_assignment_operator(AstRef ast) {
  assert(ast);
  if (ast_is_assignment_operator(ast)) {
    return ast->data.assignment_operator;
  }
  return NULL;
}

AstExpressionRef ast_get_expression(AstRef ast) {
  assert(ast);
  if (ast_is_expression(ast)) {
    return ast->data.expression;
  }
  return NULL;
}

AstConstantExpressionRef ast_get_constant_expression(AstRef ast) {
  assert(ast);
  if (ast_is_constant_expression(ast)) {
    return ast->data.constant_expression;
  }
  return NULL;
}

AstDeclarationRef ast_get_declaration(AstRef ast) {
  assert(ast);
  if (ast_is_declaration(ast)) {
    return ast->data.declaration;
  }
  return NULL;
}

AstDeclarationSpecifiersRef ast_get_declaration_specifiers(AstRef ast) {
  assert(ast);
  if (ast_is_declaration_specifiers(ast)) {
    return ast->data.declaration_specifiers;
  }
  return NULL;
}

AstInitDeclaratorListRef ast_get_init_declarator_list(AstRef ast) {
  assert(ast);
  if (ast_is_init_declarator_list(ast)) {
    return ast->data.init_declarator_list;
  }
  return NULL;
}

AstInitDeclaratorRef ast_get_init_declarator(AstRef ast) {
  assert(ast);
  if (ast_is_init_declarator(ast)) {
    return ast->data.init_declarator;
  }
  return NULL;
}

AstStorageClassSpecifierRef ast_get_storage_class_specifier(AstRef ast) {
  assert(ast);
  if (ast_is_storage_class_specifier(ast)) {
    return ast->data.storage_class_specifier;
  }
  return NULL;
}

AstTypeSpecifierRef ast_get_type_specifier(AstRef ast) {
  assert(ast);
  if (ast_is_type_specifier(ast)) {
    return ast->data.type_specifier;
  }
  return NULL;
}

AstStructOrUnionSpecifierRef ast_get_struct_or_union_specifier(AstRef ast) {
  assert(ast);
  if (ast_is_struct_or_union_specifier(ast)) {
    return ast->data.struct_or_union_specifier;
  }
  return NULL;
}

AstStructOrUnionRef ast_get_struct_or_union(AstRef ast) {
  assert(ast);
  if (ast_is_struct_or_union(ast)) {
    return ast->data.struct_or_union;
  }
  return NULL;
}

AstStructDeclarationListRef ast_get_struct_declaration_list(AstRef ast) {
  assert(ast);
  if (ast_is_struct_declaration_list(ast)) {
    return ast->data.struct_declaration_list;
  }
  return NULL;
}

AstStructDeclarationRef ast_get_struct_declaration(AstRef ast) {
  assert(ast);
  if (ast_is_struct_declaration(ast)) {
    return ast->data.struct_declaration;
  }
  return NULL;
}

AstSpecifierQualifierListRef ast_get_specifier_qualifier_list(AstRef ast) {
  assert(ast);
  if (ast_is_specifier_qualifier_list(ast)) {
    return ast->data.specifier_qualifier_list;
  }
  return NULL;
}

AstStructDeclaratorListRef ast_get_struct_declarator_list(AstRef ast) {
  assert(ast);
  if (ast_is_struct_declarator_list(ast)) {
    return ast->data.struct_declarator_list;
  }
  return NULL;
}

AstStructDeclaratorRef ast_get_struct_declarator(AstRef ast) {
  assert(ast);
  if (ast_is_struct_declarator(ast)) {
    return ast->data.struct_declarator;
  }
  return NULL;
}

AstEnumSpecifierRef ast_get_enum_specifier(AstRef ast) {
  assert(ast);
  if (ast_is_enum_specifier(ast)) {
    return ast->data.enum_specifier;
  }
  return NULL;
}

AstEnumeratorListRef ast_get_enumerator_list(AstRef ast) {
  assert(ast);
  if (ast_is_enumerator_list(ast)) {
    return ast->data.enumerator_list;
  }
  return NULL;
}

AstEnumeratorRef ast_get_enumerator(AstRef ast) {
  assert(ast);
  if (ast_is_enumerator(ast)) {
    return ast->data.enumerator;
  }
  return NULL;
}

AstTypeQualifierRef ast_get_type_qualifier(AstRef ast) {
  assert(ast);
  if (ast_is_type_qualifier(ast)) {
    return ast->data.type_qualifier;
  }
  return NULL;
}

AstDeclaratorRef ast_get_declarator(AstRef ast) {
  assert(ast);
  if (ast_is_declarator(ast)) {
    return ast->data.declarator;
  }
  return NULL;
}

AstDirectDeclaratorRef ast_get_direct_declarator(AstRef ast) {
  assert(ast);
  if (ast_is_direct_declarator(ast)) {
    return ast->data.direct_declarator;
  }
  return NULL;
}

AstPointerRef ast_get_pointer(AstRef ast) {
  assert(ast);
  if (ast_is_pointer(ast)) {
    return ast->data.pointer;
  }
  return NULL;
}

AstTypeQualifierListRef ast_get_type_qualifier_list(AstRef ast) {
  assert(ast);
  if (ast_is_type_qualifier_list(ast)) {
    return ast->data.type_qualifier_list;
  }
  return NULL;
}

AstParameterTypeListRef ast_get_parameter_type_list(AstRef ast) {
  assert(ast);
  if (ast_is_parameter_type_list(ast)) {
    return ast->data.parameter_type_list;
  }
  return NULL;
}

AstParameterListRef ast_get_parameter_list(AstRef ast) {
  assert(ast);
  if (ast_is_parameter_list(ast)) {
    return ast->data.parameter_list;
  }
  return NULL;
}

AstParameterDeclarationRef ast_get_parameter_declaration(AstRef ast) {
  assert(ast);
  if (ast_is_parameter_declaration(ast)) {
    return ast->data.parameter_declaration;
  }
  return NULL;
}

AstIdentifierListRef ast_get_identifier_list(AstRef ast) {
  assert(ast);
  if (ast_is_identifier_list(ast)) {
    return ast->data.identifier_list;
  }
  return NULL;
}

AstTypeNameRef ast_get_type_name(AstRef ast) {
  assert(ast);
  if (ast_is_type_name(ast)) {
    return ast->data.type_name;
  }
  return NULL;
}

AstAbstractDeclaratorRef ast_get_abstract_declarator(AstRef ast) {
  assert(ast);
  if (ast_is_abstract_declarator(ast)) {
    return ast->data.abstract_declarator;
  }
  return NULL;
}

AstDirectAbstractDeclaratorRef ast_get_direct_abstract_declarator(AstRef ast) {
  assert(ast);
  if (ast_is_direct_abstract_declarator(ast)) {
    return ast->data.direct_abstract_declarator;
  }
  return NULL;
}

AstTypedefNameRef ast_get_typedef_name(AstRef ast) {
  assert(ast);
  if (ast_is_typedef_name(ast)) {
    return ast->data.typedef_name;
  }
  return NULL;
}

AstInitializerRef ast_get_initializer(AstRef ast) {
  assert(ast);
  if (ast_is_initializer(ast)) {
    return ast->data.initializer;
  }
  return NULL;
}

AstInitializerListRef ast_get_initializer_list(AstRef ast) {
  assert(ast);
  if (ast_is_initializer_list(ast)) {
    return ast->data.initializer_list;
  }
  return NULL;
}

AstStatementRef ast_get_statement(AstRef ast) {
  assert(ast);
  if (ast_is_statement(ast)) {
    return ast->data.statement;
  }
  return NULL;
}

AstLabeledStatementRef ast_get_labeled_statement(AstRef ast) {
  assert(ast);
  if (ast_is_labeled_statement(ast)) {
    return ast->data.labeled_statement;
  }
  return NULL;
}

AstCompoundStatementRef ast_get_compound_statement(AstRef ast) {
  assert(ast);
  if (ast_is_compound_statement(ast)) {
    return ast->data.compound_statement;
  }
  return NULL;
}

AstDeclarationListRef ast_get_declaration_list(AstRef ast) {
  assert(ast);
  if (ast_is_declaration_list(ast)) {
    return ast->data.declaration_list;
  }
  return NULL;
}

AstStatementListRef ast_get_statement_list(AstRef ast) {
  assert(ast);
  if (ast_is_statement_list(ast)) {
    return ast->data.statement_list;
  }
  return NULL;
}

AstExpressionStatementRef ast_get_expression_statement(AstRef ast) {
  assert(ast);
  if (ast_is_expression_statement(ast)) {
    return ast->data.expression_statement;
  }
  return NULL;
}

AstSelectionStatementRef ast_get_selection_statement(AstRef ast) {
  assert(ast);
  if (ast_is_selection_statement(ast)) {
    return ast->data.selection_statement;
  }
  return NULL;
}

AstIterationStatementRef ast_get_iteration_statement(AstRef ast) {
  assert(ast);
  if (ast_is_iteration_statement(ast)) {
    return ast->data.iteration_statement;
  }
  return NULL;
}

AstJumpStatementRef ast_get_jump_statement(AstRef ast) {
  assert(ast);
  if (ast_is_jump_statement(ast)) {
    return ast->data.jump_statement;
  }
  return NULL;
}

AstTranslationUnitRef ast_get_translation_unit(AstRef ast) {
  assert(ast);
  if (ast_is_translation_unit(ast)) {
    return ast->data.translation_unit;
  }
  return NULL;
}

AstExternalDeclarationRef ast_get_external_declaration(AstRef ast) {
  assert(ast);
  if (ast_is_external_declaration(ast)) {
    return ast->data.external_declaration;
  }
  return NULL;
}

AstFunctionDefinitionRef ast_get_function_definition(AstRef ast) {
  assert(ast);
  if (ast_is_function_definition(ast)) {
    return ast->data.function_definition;
  }
  return NULL;
}
