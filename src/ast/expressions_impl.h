#ifndef KMC_C90_COMPILER_AST_EXPRESSION_IMPL_H
#define KMC_C90_COMPILER_AST_EXPRESSION_IMPL_H

#include "ast.h"

struct AstPrimaryExpression {
  AstRef primary_expression;
};

struct AstPostfixExpression {
  AstRef postfix;
};

struct AstArraySubscriptExpression {
  AstRef array;
  AstRef subscript;
};

struct AstFunctionCallExpression {
  AstRef function;
  AstRef argument_list;
};

struct AstMemberAccessExpression {
  AstRef object;
  AstRef member;
};

struct AstMemberAccessThroughPointerExpression {
  AstRef object;
  AstRef member;
};

struct AstPostfixIncrementExpression {
  AstRef postfix;
};

struct AstPostfixDecrementExpression {
  AstRef postfix;
};

struct AstArgumentExpressionList {
  AstVectorRef argument_list;
};

struct AstUnaryExpression {
  AstRef unary;
};

struct AstPrefixIncrementExpression {
  AstRef unary;
};

struct AstPrefixDecrementExpression {
  AstRef unary;
};

struct AstAddressOfExpression {
  AstRef cast;
};

struct AstPointerDereferenceExpression {
  AstRef cast;
};

struct AstUnaryPlusExpression {
  AstRef cast;
};

struct AstUnaryMinusExpression {
  AstRef cast;
};

struct AstBitwiseNotExpression {
  AstRef cast;
};

struct AstLogicalNotExpression {
  AstRef cast;
};

struct AstSizeofExpression {
  AstRef unary;
};

struct AstSizeofTypeExpression {
  AstRef type_name;
};

struct AstCastExpression {
  AstRef cast;
};

struct AstTypeCastExpression {
  AstRef type_name;
  AstRef expression;
};

struct AstMultiplicativeExpression {
  AstRef expression;
};

struct AstProductExpression {
  AstRef multiplicative;
  AstRef cast;
};

struct AstDivisionExpression {
  AstRef multiplicative;
  AstRef cast;
};

struct AstModuloExpression {
  AstRef multiplicative;
  AstRef cast;
};

struct AstAdditiveExpression {
  AstRef expression;
};

struct AstAdditionExpression {
  AstRef additive;
  AstRef multiplicative;
};

struct AstSubtractionExpression {
  AstRef additive;
  AstRef multiplicative;
};

struct AstShiftExpression {
  AstRef expression;
};

struct AstLeftShiftExpression {
  AstRef shift;
  AstRef additive;
};

struct AstRightShiftExpression {
  AstRef shift;
  AstRef additive;
};

struct AstRelationalExpression {
  AstRef expression;
};

struct AstLessThanExpression {
  AstRef relational;
  AstRef shift;
};

struct AstGreaterThanExpression {
  AstRef relational;
  AstRef shift;
};

struct AstLessThanOrEqualToExpression {
  AstRef relational;
  AstRef shift;
};

struct AstGreaterThanOrEqualToExpression {
  AstRef relational;
  AstRef shift;
};

struct AstEqualityExpression {
  AstRef expression;
};

struct AstEqualToExpression {
  AstRef equality;
  AstRef relational;
};

struct AstNotEqualToExpression {
  AstRef equality;
  AstRef relational;
};

struct AstBitwiseAndExpression {
  AstRef expression;
};

struct AstBitwiseAndOperatorExpression {
  AstRef bitwise_and;
  AstRef equality;
};

struct AstBitwiseXorExpression {
  AstRef expression;
};

struct AstBitwiseXorOperatorExpression {
  AstRef bitwise_xor;
  AstRef bitwise_and;
};

struct AstBitwiseOrExpression {
  AstRef expression;
};

struct AstBitwiseOrOperatorExpression {
  AstRef bitwise_or;
  AstRef bitwise_xor;
};

struct AstLogicalAndExpression {
  AstRef expression;
};

struct AstLogicalAndOperatorExpression {
  AstRef logical_and;
  AstRef bitwise_or;
};

struct AstLogicalOrExpression {
  AstRef expression;
};

struct AstLogicalOrOperatorExpression {
  AstRef logical_or;
  AstRef logical_and;
};

struct AstConditionalExpression {
  AstRef expression;
};

struct AstConditionalOperatorExpression {
  AstRef logical_or;
  AstRef expression;
  AstRef conditional;
};

struct AstAssignmentExpression {
  AstRef expression;
};

struct AstBasicAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstMultiplicationAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstDivisionAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstModuloAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstAdditionAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstSubtractionAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstLeftShiftAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstRightShiftAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstBitwiseAndAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstBitwiseXorAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstBitwiseOrAssignmentExpression {
  AstRef unary;
  AstRef assignment;
};

struct AstExpression {
  AstRef expression;
};

struct AstCommaExpression {
  AstRef expression;
  AstRef assignment;
};

struct AstConstantExpression {
  AstRef conditional;
};

#endif  /* KMC_C90_COMPILER_AST_EXPRESSION_IMPL_H */
