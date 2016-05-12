#ifndef KMC_C90_COMPILER_AST_H
#define KMC_C90_COMPILER_AST_H

#include "vector.h"

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
  AST_ARRAY_SUBSCRIPT_EXPRESSION,
  AST_FUNCTION_CALL_EXPRESSION,
  AST_MEMBER_ACCESS_EXPRESSION,
  AST_MEMBER_ACCESS_THROUGH_POINTER_EXPRESSION,
  AST_POSTFIX_INCREMENT_EXPRESSION,
  AST_POSTFIX_DECREMENT_EXPRESSION,
  AST_ARGUMENT_EXPRESSION_LIST,
  AST_UNARY_EXPRESSION,
  AST_PREFIX_INCREMENT_EXPRESSION,
  AST_PREFIX_DECREMENT_EXPRESSION,
  AST_ADDRESS_OF_EXPRESSION,
  AST_POINTER_DEREFERENCE_EXPRESSION,
  AST_UNARY_PLUS_EXPRESSION,
  AST_UNARY_MINUS_EXPRESSION,
  AST_BITWISE_NOT_EXPRESSION,
  AST_LOGICAL_NOT_EXPRESSION,
  AST_SIZEOF_EXPRESSION,
  AST_SIZEOF_TYPE_EXPRESSION,
  AST_CAST_EXPRESSION,
  AST_TYPE_CAST_EXPRESSION,
  AST_MULTIPLICATIVE_EXPRESSION,
  AST_PRODUCT_EXPRESSION,
  AST_DIVISION_EXPRESSION,
  AST_MODULO_EXPRESSION,
  AST_ADDITIVE_EXPRESSION,
  AST_ADDITION_EXPRESSION,
  AST_SUBTRACTION_EXPRESSION,
  AST_SHIFT_EXPRESSION,
  AST_LEFT_SHIFT_EXPRESSION,
  AST_RIGHT_SHIFT_EXPRESSION,
  AST_RELATIONAL_EXPRESSION,
  AST_LESS_THAN_EXPRESSION,
  AST_GREATER_THAN_EXPRESSION,
  AST_LESS_THAN_OR_EQUAL_TO_EXPRESSION,
  AST_GREATER_THAN_OR_EQUAL_TO_EXPRESSION,
  AST_EQUALITY_EXPRESSION,
  AST_EQUAL_TO_EXPRESSION,
  AST_NOT_EQUAL_TO_EXPRESSION,
  AST_BITWISE_AND_EXPRESSION,
  AST_BITWISE_AND_OPERATOR_EXPRESSION,
  AST_BITWISE_XOR_EXPRESSION,
  AST_BITWISE_XOR_OPERATOR_EXPRESSION,
  AST_BITWISE_OR_EXPRESSION,
  AST_BITWISE_OR_OPERATOR_EXPRESSION,
  AST_LOGICAL_AND_EXPRESSION,
  AST_LOGICAL_AND_OPERATOR_EXPRESSION,
  AST_LOGICAL_OR_EXPRESSION,
  AST_LOGICAL_OR_OPERATOR_EXPRESSION,
  AST_CONDITIONAL_EXPRESSION,
  AST_CONDITIONAL_OPERATOR_EXPRESSION,
  AST_ASSIGNMENT_EXPRESSION,
  AST_BASIC_ASSIGNMENT_EXPRESSION,
  AST_MULTIPLICATION_ASSIGNMENT_EXPRESSION,
  AST_DIVISION_ASSIGNMENT_EXPRESSION,
  AST_MODULO_ASSIGNMENT_EXPRESSION,
  AST_ADDITION_ASSIGNMENT_EXPRESSION,
  AST_SUBTRACTION_ASSIGNMENT_EXPRESSION,
  AST_LEFT_SHIFT_ASSIGNMENT_EXPRESSION,
  AST_RIGHT_SHIFT_ASSIGNMENT_EXPRESSION,
  AST_BITWISE_AND_ASSIGNMENT_EXPRESSION,
  AST_BITWISE_XOR_ASSIGNMENT_EXPRESSION,
  AST_BITWISE_OR_ASSIGNMENT_EXPRESSION,
  AST_EXPRESSION,
  AST_COMMA_EXPRESSION,
  AST_CONSTANT_EXPRESSION,
  AST_DECLARATION,
  AST_DECLARATION_SPECIFIER_LIST,
  AST_DECLARATION_SPECIFIER,
  AST_INIT_DECLARATOR_LIST,
  AST_INIT_DECLARATOR,
  AST_DECLARATOR_WITH_INITIALIZER,
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
  AST_ENUM_DEFINITION,
  AST_ENUM_DECLARATION,
  AST_ENUMERATOR_LIST,
  AST_ENUMERATOR,
  AST_ENUMERATOR_WITH_INITIALIZER,
  AST_TYPE_QUALIFIER,
  AST_DECLARATOR,
  AST_DIRECT_DECLARATOR,
  AST_ARRAY_DECLARATOR,
  AST_FUNCTION_DECLARATOR,
  AST_OLD_STYLE_FUNCTION_DECLARATOR,
  AST_POINTER,
  AST_TYPE_QUALIFIER_LIST,
  AST_PARAMETER_TYPE_LIST,
  AST_VARIADIC_PARAMETER_LIST,
  AST_PARAMETER_LIST,
  AST_PARAMETER_DECLARATION,
  AST_PARAMETER_CONCRETE_DECLARATION,
  AST_PARAMETER_ABSTRACT_DECLARATION,
  AST_IDENTIFIER_LIST,
  AST_TYPE_NAME,
  AST_ABSTRACT_DECLARATOR,
  AST_POINTER_ABSTRACT_DECLARATOR,
  AST_DIRECT_ABSTRACT_DECLARATOR,
  AST_ARRAY_ABSTRACT_DECLARATOR,
  AST_FUNCTION_ABSTRACT_DECLARATOR,
  AST_TYPEDEF_NAME,
  AST_INITIALIZER,
  AST_INITIALIZER_LIST,
  AST_STATEMENT,
  AST_LABELED_STATEMENT,
  AST_IDENTIFIER_LABELED_STATEMENT,
  AST_CASE_LABELED_STATEMENT,
  AST_DEFAULT_LABELED_STATEMENT,
  AST_COMPOUND_STATEMENT,
  AST_DECLARATION_LIST,
  AST_STATEMENT_LIST,
  AST_EXPRESSION_STATEMENT,
  AST_SELECTION_STATEMENT,
  AST_IF_STATEMENT,
  AST_IF_ELSE_STATEMENT,
  AST_SWITCH_STATEMENT,
  AST_ITERATION_STATEMENT,
  AST_WHILE_STATEMENT,
  AST_DO_WHILE_STATEMENT,
  AST_FOR_STATEMENT,
  AST_JUMP_STATEMENT,
  AST_GOTO_JUMP_STATEMENT,
  AST_CONTINUE_JUMP_STATEMENT,
  AST_BREAK_JUMP_STATEMENT,
  AST_RETURN_JUMP_STATEMENT,
  AST_VOID_RETURN_JUMP_STATEMENT,
  AST_TRANSLATION_UNIT,
  AST_EXTERNAL_DECLARATION,
  AST_FUNCTION_DEFINITION,

  AST_TOKEN,
  AST_TAG_ENUM_END
};

typedef struct Ast* AstRef;  /* NOT NULLABLE */
typedef AstRef AstNullableRef;  /* NULLABLE */

typedef struct AstIdentifier* AstIdentifierRef;
typedef struct AstConstant* AstConstantRef;
typedef struct AstFloatingConstant* AstFloatingConstantRef;
typedef struct AstIntegerConstant* AstIntegerConstantRef;
typedef struct AstEnumerationConstant* AstEnumerationConstantRef;
typedef struct AstCharacterConstant* AstCharacterConstantRef;
typedef struct AstStringLiteral* AstStringLiteralRef;
typedef struct AstPrimaryExpression* AstPrimaryExpressionRef;
typedef struct AstPostfixExpression* AstPostfixExpressionRef;
typedef struct AstArraySubscriptExpression* AstArraySubscriptExpressionRef;
typedef struct AstFunctionCallExpression* AstFunctionCallExpressionRef;
typedef struct AstMemberAccessExpression* AstMemberAccessExpressionRef;
typedef struct AstMemberAccessThroughPointerExpression* AstMemberAccessThroughPointerExpressionRef;
typedef struct AstPostfixIncrementExpression* AstPostfixIncrementExpressionRef;
typedef struct AstPostfixDecrementExpression* AstPostfixDecrementExpressionRef;
typedef struct AstArgumentExpressionList* AstArgumentExpressionListRef;
typedef struct AstUnaryExpression* AstUnaryExpressionRef;
typedef struct AstPrefixIncrementExpression* AstPrefixIncrementExpressionRef;
typedef struct AstPrefixDecrementExpression* AstPrefixDecrementExpressionRef;
typedef struct AstAddressOfExpression* AstAddressOfExpressionRef;
typedef struct AstPointerDereferenceExpression* AstPointerDereferenceExpressionRef;
typedef struct AstUnaryPlusExpression* AstUnaryPlusExpressionRef;
typedef struct AstUnaryMinusExpression* AstUnaryMinusExpressionRef;
typedef struct AstBitwiseNotExpression* AstBitwiseNotExpressionRef;
typedef struct AstLogicalNotExpression* AstLogicalNotExpressionRef;
typedef struct AstSizeofExpression* AstSizeofExpressionRef;
typedef struct AstSizeofTypeExpression* AstSizeofTypeExpressionRef;
typedef struct AstCastExpression* AstCastExpressionRef;
typedef struct AstTypeCastExpression* AstTypeCastExpressionRef;
typedef struct AstMultiplicativeExpression* AstMultiplicativeExpressionRef;
typedef struct AstProductExpression* AstProductExpressionRef;
typedef struct AstDivisionExpression* AstDivisionExpressionRef;
typedef struct AstModuloExpression* AstModuloExpressionRef;
typedef struct AstAdditiveExpression* AstAdditiveExpressionRef;
typedef struct AstAdditionExpression* AstAdditionExpressionRef;
typedef struct AstSubtractionExpression* AstSubtractionExpressionRef;
typedef struct AstShiftExpression* AstShiftExpressionRef;
typedef struct AstLeftShiftExpression* AstLeftShiftExpressionRef;
typedef struct AstRightShiftExpression* AstRightShiftExpressionRef;
typedef struct AstRelationalExpression* AstRelationalExpressionRef;
typedef struct AstLessThanExpression* AstLessThanExpressionRef;
typedef struct AstGreaterThanExpression* AstGreaterThanExpressionRef;
typedef struct AstLessThanOrEqualToExpression* AstLessThanOrEqualToExpressionRef;
typedef struct AstGreaterThanOrEqualToExpression* AstGreaterThanOrEqualToExpressionRef;
typedef struct AstEqualityExpression* AstEqualityExpressionRef;
typedef struct AstEqualToExpression* AstEqualToExpressionRef;
typedef struct AstNotEqualToExpression* AstNotEqualToExpressionRef;
typedef struct AstBitwiseAndExpression* AstBitwiseAndExpressionRef;
typedef struct AstBitwiseAndOperatorExpression* AstBitwiseAndOperatorExpressionRef;
typedef struct AstBitwiseXorExpression* AstBitwiseXorExpressionRef;
typedef struct AstBitwiseXorOperatorExpression* AstBitwiseXorOperatorExpressionRef;
typedef struct AstBitwiseOrExpression* AstBitwiseOrExpressionRef;
typedef struct AstBitwiseOrOperatorExpression* AstBitwiseOrOperatorExpressionRef;
typedef struct AstLogicalAndExpression* AstLogicalAndExpressionRef;
typedef struct AstLogicalAndOperatorExpression* AstLogicalAndOperatorExpressionRef;
typedef struct AstLogicalOrExpression* AstLogicalOrExpressionRef;
typedef struct AstLogicalOrOperatorExpression* AstLogicalOrOperatorExpressionRef;
typedef struct AstConditionalExpression* AstConditionalExpressionRef;
typedef struct AstConditionalOperatorExpression* AstConditionalOperatorExpressionRef;
typedef struct AstAssignmentExpression* AstAssignmentExpressionRef;
typedef struct AstBasicAssignmentExpression* AstBasicAssignmentExpressionRef;
typedef struct AstMultiplicationAssignmentExpression* AstMultiplicationAssignmentExpressionRef;
typedef struct AstDivisionAssignmentExpression* AstDivisionAssignmentExpressionRef;
typedef struct AstModuloAssignmentExpression* AstModuloAssignmentExpressionRef;
typedef struct AstAdditionAssignmentExpression* AstAdditionAssignmentExpressionRef;
typedef struct AstSubtractionAssignmentExpression* AstSubtractionAssignmentExpressionRef;
typedef struct AstLeftShiftAssignmentExpression* AstLeftShiftAssignmentExpressionRef;
typedef struct AstRightShiftAssignmentExpression* AstRightShiftAssignmentExpressionRef;
typedef struct AstBitwiseAndAssignmentExpression* AstBitwiseAndAssignmentExpressionRef;
typedef struct AstBitwiseXorAssignmentExpression* AstBitwiseXorAssignmentExpressionRef;
typedef struct AstBitwiseOrAssignmentExpression* AstBitwiseOrAssignmentExpressionRef;
typedef struct AstExpression* AstExpressionRef;
typedef struct AstCommaExpression* AstCommaExpressionRef;
typedef struct AstConstantExpression* AstConstantExpressionRef;
typedef struct AstDeclaration* AstDeclarationRef;
typedef struct AstDeclarationSpecifierList* AstDeclarationSpecifierListRef;
typedef struct AstDeclarationSpecifier* AstDeclarationSpecifierRef;
typedef struct AstInitDeclaratorList* AstInitDeclaratorListRef;
typedef struct AstInitDeclarator* AstInitDeclaratorRef;
typedef struct AstDeclaratorWithInitializer* AstDeclaratorWithInitializerRef;
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
typedef struct AstEnumDefinition* AstEnumDefinitionRef;
typedef struct AstEnumDeclaration* AstEnumDeclarationRef;
typedef struct AstEnumeratorList* AstEnumeratorListRef;
typedef struct AstEnumerator* AstEnumeratorRef;
typedef struct AstEnumeratorWithInitializer* AstEnumeratorWithInitializerRef;
typedef struct AstTypeQualifier* AstTypeQualifierRef;
typedef struct AstDeclarator* AstDeclaratorRef;
typedef struct AstDirectDeclarator* AstDirectDeclaratorRef;
typedef struct AstArrayDeclarator* AstArrayDeclaratorRef;
typedef struct AstFunctionDeclarator* AstFunctionDeclaratorRef;
typedef struct AstOldStyleFunctionDeclarator* AstOldStyleFunctionDeclaratorRef;
typedef struct AstPointer* AstPointerRef;
typedef struct AstTypeQualifierList* AstTypeQualifierListRef;
typedef struct AstParameterTypeList* AstParameterTypeListRef;
typedef struct AstVariadicParameterList* AstVariadicParameterListRef;
typedef struct AstParameterList* AstParameterListRef;
typedef struct AstParameterDeclaration* AstParameterDeclarationRef;
typedef struct AstParameterConcreteDeclaration* AstParameterConcreteDeclarationRef;
typedef struct AstParameterAbstractDeclaration* AstParameterAbstractDeclarationRef;
typedef struct AstIdentifierList* AstIdentifierListRef;
typedef struct AstTypeName* AstTypeNameRef;
typedef struct AstAbstractDeclarator* AstAbstractDeclaratorRef;
typedef struct AstPointerAbstractDeclarator* AstPointerAbstractDeclaratorRef;
typedef struct AstDirectAbstractDeclarator* AstDirectAbstractDeclaratorRef;
typedef struct AstArrayAbstractDeclarator* AstArrayAbstractDeclaratorRef;
typedef struct AstFunctionAbstractDeclarator* AstFunctionAbstractDeclaratorRef;
typedef struct AstTypedefName* AstTypedefNameRef;
typedef struct AstInitializer* AstInitializerRef;
typedef struct AstInitializerList* AstInitializerListRef;
typedef struct AstStatement* AstStatementRef;
typedef struct AstLabeledStatement* AstLabeledStatementRef;
typedef struct AstIdentifierLabeledStatement* AstIdentifierLabeledStatementRef;
typedef struct AstCaseLabeledStatement* AstCaseLabeledStatementRef;
typedef struct AstDefaultLabeledStatement* AstDefaultLabeledStatementRef;
typedef struct AstCompoundStatement* AstCompoundStatementRef;
typedef struct AstDeclarationList* AstDeclarationListRef;
typedef struct AstStatementList* AstStatementListRef;
typedef struct AstExpressionStatement* AstExpressionStatementRef;
typedef struct AstSelectionStatement* AstSelectionStatementRef;
typedef struct AstIfStatement* AstIfStatementRef;
typedef struct AstIfElseStatement* AstIfElseStatementRef;
typedef struct AstSwitchStatement* AstSwitchStatementRef;
typedef struct AstIterationStatement* AstIterationStatementRef;
typedef struct AstWhileStatement* AstWhileStatementRef;
typedef struct AstDoWhileStatement* AstDoWhileStatementRef;
typedef struct AstForStatement* AstForStatementRef;
typedef struct AstJumpStatement* AstJumpStatementRef;
typedef struct AstGotoJumpStatement* AstGotoJumpStatementRef;
typedef struct AstContinueJumpStatement* AstContinueJumpStatementRef;
typedef struct AstBreakJumpStatement* AstBreakJumpStatementRef;
typedef struct AstReturnJumpStatement* AstReturnJumpStatementRef;
typedef struct AstVoidReturnJumpStatement* AstVoidReturnJumpStatementRef;
typedef struct AstTranslationUnit* AstTranslationUnitRef;
typedef struct AstExternalDeclaration* AstExternalDeclarationRef;
typedef struct AstFunctionDefinition* AstFunctionDefinitionRef;

typedef struct String* AstTokenRef;
typedef struct VECTOR(AstRef)* AstVectorRef;

#endif  /* KMC_C90_COMPILER_AST_H */
