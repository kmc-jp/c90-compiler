#ifndef KMC_C89_COMPILER_AST_H
#define KMC_C89_COMPILER_AST_H

enum AstTag {
  AST_IDENTIFIER,
  AST_CONSTANT,
  AST_FLOATING_CONSTANT,
  AST_INTEGER_CONSTANT,
  AST_ENUMERATION_CONSTANT,
  AST_CHARACTER_CONSTANT,
  AST_STRING_LITERAL,
  AST_PRIMARY_EXPRESSION,
  AST_POSTFIX_EXPRESSION,
  AST_ARGUMENT_EXPRESSION_LIST,
  AST_UNARY_EXPRESSION,
  AST_UNARY_OPERATOR,
  AST_CAST_EXPRESSION,
  AST_MULTIPLICATIVE_EXPRESSION,
  AST_ADDITIVE_EXPRESSION,
  AST_SHIFT_EXPRESSION,
  AST_RELATIONAL_EXPRESSION,
  AST_EQUALITY_EXPRESSION,
  AST_AND_EXPRESSION,
  AST_EXCLUSIVE_OR_EXPRESSION,
  AST_INCLUSIVE_OR_EXPRESSION,
  AST_LOGICAL_AND_EXPRESSION,
  AST_LOGICAL_OR_EXPRESSION,
  AST_CONDITIONAL_EXPRESSION,
  AST_ASSIGNMENT_EXPRESSION,
  AST_ASSIGNMENT_OPERATOR,
  AST_EXPRESSION,
  AST_CONSTANT_EXPRESSION,
  AST_DECLARATION,
  AST_DECLARATION_SPECIFIERS,
  AST_INIT_DECLARATOR_LIST,
  AST_INIT_DECLARATOR,
  AST_STORAGE_CLASS_SPECIFIER,
  AST_TYPE_SPECIFIER,
  AST_STRUCT_OR_UNION_SPECIFIER,
  AST_STRUCT_OR_UNION_DEFINITION,
  AST_STRUCT_OR_UNION_DECLARATION,
  AST_STRUCT_OR_UNION,
  AST_STRUCT_DECLARATION_LIST,
  AST_STRUCT_DECLARATION,
  AST_SPECIFIER_QUALIFIER_LIST,
  AST_SPECIFIER_QUALIFIER,
  AST_STRUCT_DECLARATOR_LIST,
  AST_STRUCT_DECLARATOR,
  AST_BIT_FIELD_DECLARATOR,
  AST_ENUM_SPECIFIER,
  AST_ENUMERATOR_LIST,
  AST_ENUMERATOR,
  AST_TYPE_QUALIFIER,
  AST_DECLARATOR,
  AST_DIRECT_DECLARATOR,
  AST_POINTER,
  AST_TYPE_QUALIFIER_LIST,
  AST_PARAMETER_TYPE_LIST,
  AST_PARAMETER_LIST,
  AST_PARAMETER_DECLARATION,
  AST_IDENTIFIER_LIST,
  AST_TYPE_NAME,
  AST_ABSTRACT_DECLARATOR,
  AST_DIRECT_ABSTRACT_DECLARATOR,
  AST_TYPEDEF_NAME,
  AST_INITIALIZER,
  AST_INITIALIZER_LIST,
  AST_STATEMENT,
  AST_LABELED_STATEMENT,
  AST_COMPOUND_STATEMENT,
  AST_DECLARATION_LIST,
  AST_STATEMENT_LIST,
  AST_EXPRESSION_STATEMENT,
  AST_SELECTION_STATEMENT,
  AST_ITERATION_STATEMENT,
  AST_JUMP_STATEMENT,
  AST_TRANSLATION_UNIT,
  AST_EXTERNAL_DECLARATION,
  AST_FUNCTION_DEFINITION,

  AST_VECTOR,
  AST_TOKEN,
  AST_TAG_ENUM_END
};

typedef struct Ast* AstRef;

typedef struct AstIdentifier* AstIdentifierRef;
typedef struct AstConstant* AstConstantRef;
typedef struct AstFloatingConstant* AstFloatingConstantRef;
typedef struct AstIntegerConstant* AstIntegerConstantRef;
typedef struct AstEnumerationConstant* AstEnumerationConstantRef;
typedef struct AstCharacterConstant* AstCharacterConstantRef;
typedef struct AstStringLiteral* AstStringLiteralRef;
typedef struct AstPrimaryExpression* AstPrimaryExpressionRef;
typedef struct AstPostfixExpression* AstPostfixExpressionRef;
typedef struct AstArgumentExpressionList* AstArgumentExpressionListRef;
typedef struct AstUnaryExpression* AstUnaryExpressionRef;
typedef struct AstUnaryOperator* AstUnaryOperatorRef;
typedef struct AstCastExpression* AstCastExpressionRef;
typedef struct AstMultiplicativeExpression* AstMultiplicativeExpressionRef;
typedef struct AstAdditiveExpression* AstAdditiveExpressionRef;
typedef struct AstShiftExpression* AstShiftExpressionRef;
typedef struct AstRelationalExpression* AstRelationalExpressionRef;
typedef struct AstEqualityExpression* AstEqualityExpressionRef;
typedef struct AstAndExpression* AstAndExpressionRef;
typedef struct AstExclusiveOrExpression* AstExclusiveOrExpressionRef;
typedef struct AstInclusiveOrExpression* AstInclusiveOrExpressionRef;
typedef struct AstLogicalAndExpression* AstLogicalAndExpressionRef;
typedef struct AstLogicalOrExpression* AstLogicalOrExpressionRef;
typedef struct AstConditionalExpression* AstConditionalExpressionRef;
typedef struct AstAssignmentExpression* AstAssignmentExpressionRef;
typedef struct AstAssignmentOperator* AstAssignmentOperatorRef;
typedef struct AstExpression* AstExpressionRef;
typedef struct AstConstantExpression* AstConstantExpressionRef;
typedef struct AstDeclaration* AstDeclarationRef;
typedef struct AstDeclarationSpecifiers* AstDeclarationSpecifiersRef;
typedef struct AstInitDeclaratorList* AstInitDeclaratorListRef;
typedef struct AstInitDeclarator* AstInitDeclaratorRef;
typedef struct AstStorageClassSpecifier* AstStorageClassSpecifierRef;
typedef struct AstTypeSpecifier* AstTypeSpecifierRef;
typedef struct AstStructOrUnionSpecifier* AstStructOrUnionSpecifierRef;
typedef struct AstStructOrUnionDefinition* AstStructOrUnionDefinitionRef;
typedef struct AstStructOrUnionDeclaration* AstStructOrUnionDeclarationRef;
typedef struct AstStructOrUnion* AstStructOrUnionRef;
typedef struct AstStructDeclarationList* AstStructDeclarationListRef;
typedef struct AstStructDeclaration* AstStructDeclarationRef;
typedef struct AstSpecifierQualifierList* AstSpecifierQualifierListRef;
typedef struct AstSpecifierQualifier* AstSpecifierQualifierRef;
typedef struct AstStructDeclaratorList* AstStructDeclaratorListRef;
typedef struct AstStructDeclarator* AstStructDeclaratorRef;
typedef struct AstBitFieldDeclarator* AstBitFieldDeclaratorRef;
typedef struct AstEnumSpecifier* AstEnumSpecifierRef;
typedef struct AstEnumeratorList* AstEnumeratorListRef;
typedef struct AstEnumerator* AstEnumeratorRef;
typedef struct AstTypeQualifier* AstTypeQualifierRef;
typedef struct AstDeclarator* AstDeclaratorRef;
typedef struct AstDirectDeclarator* AstDirectDeclaratorRef;
typedef struct AstPointer* AstPointerRef;
typedef struct AstTypeQualifierList* AstTypeQualifierListRef;
typedef struct AstParameterTypeList* AstParameterTypeListRef;
typedef struct AstParameterList* AstParameterListRef;
typedef struct AstParameterDeclaration* AstParameterDeclarationRef;
typedef struct AstIdentifierList* AstIdentifierListRef;
typedef struct AstTypeName* AstTypeNameRef;
typedef struct AstAbstractDeclarator* AstAbstractDeclaratorRef;
typedef struct AstDirectAbstractDeclarator* AstDirectAbstractDeclaratorRef;
typedef struct AstTypedefName* AstTypedefNameRef;
typedef struct AstInitializer* AstInitializerRef;
typedef struct AstInitializerList* AstInitializerListRef;
typedef struct AstStatement* AstStatementRef;
typedef struct AstLabeledStatement* AstLabeledStatementRef;
typedef struct AstCompoundStatement* AstCompoundStatementRef;
typedef struct AstDeclarationList* AstDeclarationListRef;
typedef struct AstStatementList* AstStatementListRef;
typedef struct AstExpressionStatement* AstExpressionStatementRef;
typedef struct AstSelectionStatement* AstSelectionStatementRef;
typedef struct AstIterationStatement* AstIterationStatementRef;
typedef struct AstJumpStatement* AstJumpStatementRef;
typedef struct AstTranslationUnit* AstTranslationUnitRef;
typedef struct AstExternalDeclaration* AstExternalDeclarationRef;
typedef struct AstFunctionDefinition* AstFunctionDefinitionRef;

#endif  /* KMC_C89_COMPILER_AST_H */
