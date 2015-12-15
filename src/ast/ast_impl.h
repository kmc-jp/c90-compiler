#ifndef KMC_C89_COMPILER_AST_AST_IMPL_H
#define KMC_C89_COMPILER_AST_AST_IMPL_H

struct Ast {
  enum AstTag tag;
  union AstData {
    char* token;
  } data;
};

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

#endif  /* KMC_C89_COMPILER_AST_AST_IMPL_H */
