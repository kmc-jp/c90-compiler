#ifndef KMC_C89_COMPILER_AST_AST_IMPL_H
#define KMC_C89_COMPILER_AST_AST_IMPL_H

#include "../ast.h"
#include "ast_vector.h"
#include "ast_string.h"

struct Ast {
  enum AstTag tag;
  union AstData {
    AstIdentifierRef identifier;
    AstConstantRef constant;
    AstFloatingConstantRef floating_constant;
    AstIntegerConstantRef integer_constant;
    AstEnumerationConstantRef enumeration_constant;
    AstCharacterConstantRef character_constant;
    AstStringLiteralRef string_literal;
    AstPrimaryExpressionRef primary_expression;
    AstPostfixExpressionRef postfix_expression;
    AstArgumentExpressionListRef argument_expression_list;
    AstUnaryExpressionRef unary_expression;
    AstUnaryOperatorRef unary_operator;
    AstCastExpressionRef cast_expression;
    AstMultiplicativeExpressionRef multiplicative_expression;
    AstAdditiveExpressionRef additive_expression;
    AstShiftExpressionRef shift_expression;
    AstRelationalExpressionRef relational_expression;
    AstEqualityExpressionRef equality_expression;
    AstAndExpressionRef and_expression;
    AstExclusiveOrExpressionRef exclusive_or_expression;
    AstInclusiveOrExpressionRef inclusive_or_expression;
    AstLogicalAndExpressionRef logical_and_expression;
    AstLogicalOrExpressionRef logical_or_expression;
    AstConditionalExpressionRef conditional_expression;
    AstAssignmentExpressionRef assignment_expression;
    AstAssignmentOperatorRef assignment_operator;
    AstExpressionRef expression;
    AstConstantExpressionRef constant_expression;
    AstDeclarationRef declaration;
    AstDeclarationSpecifiersRef declaration_specifiers;
    AstInitDeclaratorListRef init_declarator_list;
    AstInitDeclaratorRef init_declarator;
    AstStorageClassSpecifierRef storage_class_specifier;
    AstTypeSpecifierRef type_specifier;
    AstStructOrUnionSpecifierRef struct_or_union_specifier;
    AstStructOrUnionDefinitionRef struct_or_union_definition;
    AstStructOrUnionDeclarationRef struct_or_union_declaration;
    AstStructOrUnionRef struct_or_union;
    AstStructDeclarationListRef struct_declaration_list;
    AstStructDeclarationRef struct_declaration;
    AstSpecifierQualifierListRef specifier_qualifier_list;
    AstSpecifierQualifierRef specifier_qualifier;
    AstStructDeclaratorListRef struct_declarator_list;
    AstStructDeclaratorRef struct_declarator;
    AstEnumSpecifierRef enum_specifier;
    AstEnumeratorListRef enumerator_list;
    AstEnumeratorRef enumerator;
    AstTypeQualifierRef type_qualifier;
    AstDeclaratorRef declarator;
    AstDirectDeclaratorRef direct_declarator;
    AstPointerRef pointer;
    AstTypeQualifierListRef type_qualifier_list;
    AstParameterTypeListRef parameter_type_list;
    AstParameterListRef parameter_list;
    AstParameterDeclarationRef parameter_declaration;
    AstIdentifierListRef identifier_list;
    AstTypeNameRef type_name;
    AstAbstractDeclaratorRef abstract_declarator;
    AstDirectAbstractDeclaratorRef direct_abstract_declarator;
    AstTypedefNameRef typedef_name;
    AstInitializerRef initializer;
    AstInitializerListRef initializer_list;
    AstStatementRef statement;
    AstLabeledStatementRef labeled_statement;
    AstCompoundStatementRef compound_statement;
    AstDeclarationListRef declaration_list;
    AstStatementListRef statement_list;
    AstExpressionStatementRef expression_statement;
    AstSelectionStatementRef selection_statement;
    AstIterationStatementRef iteration_statement;
    AstJumpStatementRef jump_statement;
    AstTranslationUnitRef translation_unit;
    AstExternalDeclarationRef external_declaration;
    AstFunctionDefinitionRef function_definition;

    AstVectorRef vector;
    AstTokenRef token;
  } data;
};

#endif  /* KMC_C89_COMPILER_AST_AST_IMPL_H */
