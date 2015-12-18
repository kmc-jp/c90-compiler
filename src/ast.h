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
  AST_INDEX_ACCESS_EXPRESSION,
  AST_FUNCTION_CALL_EXPRESSION,
  AST_DOT_ACCESS_EXPRESSION,
  AST_ARROW_ACCESS_EXPRESSION,
  AST_POSTFIX_INCREMENT_EXPRESSION,
  AST_POSTFIX_DECREMENT_EXPRESSION,
  AST_ARGUMENT_EXPRESSION_LIST,
  AST_UNARY_EXPRESSION,
  AST_PREFIX_INCREMENT_EXPRESSION,
  AST_PREFIX_DECREMENT_EXPRESSION,
  AST_UNARY_OPERATOR_EXPRESSION,
  AST_SIZEOF_EXPRESSION,
  AST_SIZEOF_TYPE_EXPRESSION,
  AST_ADDRESS_EXPRESSION,
  AST_DEREFERENCE_EXPRESSION,
  AST_UNARY_PLUS_EXPRESSION,
  AST_UNARY_MINUS_EXPRESSION,
  AST_COMPLEMENT_EXPRESSION,
  AST_LOGICAL_NEGATE_EXPRESSION,
  AST_CAST_OR_UNARY_EXPRESSION,
  AST_CAST_EXPRESSION,
  AST_MULTIPLICATIVE_EXPRESSION,
  AST_MULTIPLY_EXPRESSION,
  AST_DIVIDE_EXPRESSION,
  AST_MODULO_EXPRESSION,
  AST_ADDITIVE_EXPRESSION,
  AST_ADD_EXPRESSION,
  AST_SUBTRACT_EXPRESSION,
  AST_SHIFT_EXPRESSION,
  AST_RELATIONAL_EXPRESSION,
  AST_EQUALITY_EXPRESSION,
  AST_AND_EXPRESSION,
  AST_EXCLUSIVE_OR_EXPRESSION,
  AST_INCLUSIVE_OR_EXPRESSION,
  AST_LOGICAL_AND_EXPRESSION,
  AST_LOGICAL_OR_EXPRESSION,
  AST_LOGICAL_OR_OPERATOR_EXPRESSION,
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
  AST_STRUCT_OR_UNION,
  AST_STRUCT_DECLARATION_LIST,
  AST_STRUCT_DECLARATION,
  AST_SPECIFIER_QUALIFIER_LIST,
  AST_STRUCT_DECLARATOR_LIST,
  AST_STRUCT_DECLARATOR,
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
typedef struct AstIndexAccessExpression* AstIndexAccessExpressionRef;
typedef struct AstFunctionCallExpression* AstFunctionCallExpressionRef;
typedef struct AstDotAccessExpression* AstDotAccessExpressionRef;
typedef struct AstArrowAccessExpression* AstArrowAccessExpressionRef;
typedef struct AstPostfixIncrementExpression* AstPostfixIncrementExpressionRef;
typedef struct AstPostfixDecrementExpression* AstPostfixDecrementExpressionRef;
typedef struct AstArgumentExpressionList* AstArgumentExpressionListRef;
typedef struct AstUnaryExpression* AstUnaryExpressionRef;
typedef struct AstPrefixIncrementExpression* AstPrefixIncrementExpressionRef;
typedef struct AstPrefixDecrementExpression* AstPrefixDecrementExpressionRef;
typedef struct AstUnaryOperatorExpression* AstUnaryOperatorExpressionRef;
typedef struct AstSizeofExpression* AstSizeofExpressionRef;
typedef struct AstSizeofTypeExpression* AstSizeofTypeExpressionRef;
typedef struct AstAddressExpression* AstAddressExpressionRef;
typedef struct AstDereferenceExpression* AstDereferenceExpressionRef;
typedef struct AstUnaryPlusExpression* AstUnaryPlusExpressionRef;
typedef struct AstUnaryMinusExpression* AstUnaryMinusExpressionRef;
typedef struct AstComplementExpression* AstComplementExpressionRef;
typedef struct AstLogicalNegateExpression* AstLogicalNegateExpressionRef;
typedef struct AstCastOrUnaryExpression* AstCastOrUnaryExpressionRef;
typedef struct AstCastExpression* AstCastExpressionRef;
typedef struct AstMultiplicativeExpression* AstMultiplicativeExpressionRef;
typedef struct AstMultiplyExpression* AstMultiplyExpressionRef;
typedef struct AstDivideExpression* AstDivideExpressionRef;
typedef struct AstModuloExpression* AstModuloExpressionRef;
typedef struct AstAdditiveExpression* AstAdditiveExpressionRef;
typedef struct AstAddExpression* AstAddExpressionRef;
typedef struct AstSubtractExpression* AstSubtractExpressionRef;
typedef struct AstShiftExpression* AstShiftExpressionRef;
typedef struct AstRelationalExpression* AstRelationalExpressionRef;
typedef struct AstEqualityExpression* AstEqualityExpressionRef;
typedef struct AstAndExpression* AstAndExpressionRef;
typedef struct AstExclusiveOrExpression* AstExclusiveOrExpressionRef;
typedef struct AstInclusiveOrExpression* AstInclusiveOrExpressionRef;
typedef struct AstLogicalAndExpression* AstLogicalAndExpressionRef;
typedef struct AstLogicalOrExpression* AstLogicalOrExpressionRef;
typedef struct AstLogicalOrOperatorExpression* AstLogicalOrOperatorExpressionRef;
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
typedef struct AstStructOrUnion* AstStructOrUnionRef;
typedef struct AstStructDeclarationList* AstStructDeclarationListRef;
typedef struct AstStructDeclaration* AstStructDeclarationRef;
typedef struct AstSpecifierQualifierList* AstSpecifierQualifierListRef;
typedef struct AstStructDeclaratorList* AstStructDeclaratorListRef;
typedef struct AstStructDeclarator* AstStructDeclaratorRef;
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
