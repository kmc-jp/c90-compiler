#include <stdio.h>

#define SINGLE_to_string(NAME, TYPE, MEMBER) \
  void NAME ## _to_string(TYPE val) {        \
    printf("TYPE : {\n");                    \
    vidualizer(val->MEMBER);                 \
    printf("}\n");                           \
  }

#define DOUBLE_to_string(NAME, TYPE, MEMBER1, MEMBER2) \
  void NAME ## _to_string(TYPE val) {                  \
    printf("TYPE : {\n");                              \
    printf("MEMBER1 :");                               \
    vidualizer(val->MEMBER1);                          \
    printf("MEMBER2 :");                               \
    vidualizer(val->MEMBER2);                          \
    printf("}\n");                                     \
  }

SINGLE_to_string(identifier, AstIdentifierRef, token)
SINGLE_to_string(constant, AstConstantRef, constant)
SINGLE_to_string(floating_constant, AstFloatingConstantRef, token)
SINGLE_to_string(integer_constant, AstIntegerConstantRef, token)
SINGLE_to_string(enumeration_constant, AstEnumerationConstantRef, identifier)
SINGLE_to_string(character_constant, AstCharacterConstantRef, token)
SINGLE_to_string(character_constant, AstCharacterConstantRef, token)
SINGLE_to_string(string_literal, AstStringLiteralRef, token)
SINGLE_to_string(primary_expression, AstPrimaryExpressionRef, primary_expression)
SINGLE_to_string(postfix_expression, AstPostfixExpressionRef, postfix)
DOUBLE_to_string(array_subscript_expression, AstArraySubscriptExpressionRef, array, subscript)
DOUBLE_to_string(function_call_expression, AstFunctionCallExpressionRef, function, argument_list)
DOUBLE_to_string(member_access_expression, AstMemberAccessExpressionRef, object, member)
DOUBLE_to_string(member_access_through_pointer, AstMemberAccessThroughPointerExpressionRef, object, member)
SINGLE_to_string(postfix_increment_expression, AstPostfixIncrementExpressionRef, postfix)
SINGLE_to_string(postfix_decrement_expression, AstPostfixDecrementExpressionRef, postfix)

void argument_expression_list_to_string(AstArgumentExpressionListRef val) {
  printf("AstArgumentExpressionListRef: {\n");
//////////////////////  vidualizer(val->postfix);
  //////
  printf("}\n");
}


SINGLE_to_string(unary_expression, AstUnaryExpressionRef, unary)
SINGLE_to_string(prefix_increment_expression, AstPrefixIncrementExpressionRef, unary)
SINGLE_to_string(prefix_decrement_expression, AstPrefixDecrementExpressionRef, unary)
SINGLE_to_string(address_of_expression, AstAddressOfExpressionRef, cast)
SINGLE_to_string(pointer_dereference_expression, AstPointerDereferenceExpressionRef, cast)
SINGLE_to_string(unary_plus_expression, AstUnaryPlusExpressionRef, cast)
SINGLE_to_string(unary_minus_expression, AstUnaryMinusExpressionRef, cast)
SINGLE_to_string(bitwise_not_expression, AstBitwiseNotExpressionRef, cast)
SINGLE_to_string(logical_not_expression, AstLogicalNotExpressionRef, cast)
SINGLE_to_string(sizeof_expression, AstSizeofExpressionRef, unary)
SINGLE_to_string(sizeof_type_expression, AstSizeofTypeExpressionRef, type_name)
SINGLE_to_string(cast_expression, AstCastExpressionRef, cast)

DOUBLE_to_string(type_cast_expression, AstTypeCastExpressionRef, type_name, expression)

SINGLE_to_string(multiplicative_expression, AstMultiplicativeExpressionRef, expression)

DOUBLE_to_string(product_expression, AstProductExpressionRef, multiplicative, cast)
DOUBLE_to_string(division_expression, AstDivisionExpressionRef, multiplicative, cast)
DOUBLE_to_string(modulo_expression, AstModuloExpressionRef, multiplicative, cast)

SINGLE_to_string(additive_expression, AstAdditiveExpressionRef, expression)

DOUBLE_to_string(addition_expression, AstAdditionExpressionRef, additive, multiplicative)
DOUBLE_to_string(subtraction_expression, AstSubtractionExpressionRef, additive, multiplicative)
SINGLE_to_string(shift_expression, AstShiftExpressionRef, expression)

DOUBLE_to_string(left_shift_expression, AstLeftShiftExpressionRef, shift, additive)
DOUBLE_to_string(right_shift_expression, AstRightShiftExpressionRef, shift, additive)

SINGLE_to_string(relational_expression, AstRelationalExpressionRef, expression)

DOUBLE_to_string(less_than_expression, AstLessThanExpressionRef, relational, shift)
DOUBLE_to_string(greater_than_expression, AstGreaterThanExpressionRef, relational, shift)
DOUBLE_to_string(less_than_or_equal_to_expression, AstLessThanOrEqualToExpressionRef, relational, shift)
DOUBLE_to_string(greater_than_or_equal_to_expression, AstGreaterThanOrEqualToExpressionRef, relational, shift)

SINGLE_to_string(equality_expression, AstEqualityExpressionRef, expression)

DOUBLE_to_string(equal_to_expression, AstEqualToExpressionRef, equality, relational)
DOUBLE_to_string(not_equal_to_expression, AstNotEqualToExpressionRef, equality, relational)

SINGLE_to_string(bitwise_and_expression, AstBitwiseAndExpressionRef, expression)
DOUBLE_to_string(bitwise_and_operator_expression, AstBitwiseAndOperatorExpressionRef, bitwise_and, equality)
SINGLE_to_string(bitwise_xor_expression, AstBitwiseXorExpressionRef, expression)
DOUBLE_to_string(bitwise_xor_operator_expression, AstBitwiseXorOperatorExpressionRef, bitwise_xor, bitwise_and)
SINGLE_to_string(bitwise_or_expression, AstBitwiseOrExpressionRef, expression)
DOUBLE_to_string(bitwise_or_operator_expression, AstBitwiseOrOperatorExpressionRef, bitwise_or, bitwise_xor)

SINGLE_to_string(logical_and_expression, AstLogicalAndExpressionRef, expression)
DOUBLE_to_string(logical_and_operator_expression, AstLogicalAndOperatorExpressionRef, logical_and, bitwise_or)
SINGLE_to_string(logical_or_expression, AstLogicalOrExpressionRef, expression)
DOUBLE_to_string(logical_or_operator_expression, AstLogicalOrOperatorExpressionRef, logical_or, logical_and)

SINGLE_to_string(conditional_expression, AstConditionalExpressionRef, expression)

conditional_operator_expression_to_string()

SINGLE_to_string(assignment_expression, AstAssignmentExpressionRef, expression)

DOUBLE_to_string(basic_assignment_expression, AstBasicAssignmentExpressionRef, unary, assignment)

DOUBLE_to_string(multiplication_assignment_expression, AstMultiplicationAssignmentExpressionRef, unary, assignment)
DOUBLE_to_string(division_assignment_expression, AstDivisionAssignmentExpressionRef, unary, assignment)
DOUBLE_to_string(modulo_assignment_expression, AstModuloAssignmentExpressionRef, unary, assignment)
DOUBLE_to_string(addition_assignment_expression, AstAdditionAssignmentExpressionRef, unary, assignment)
DOUBLE_to_string(subtraction_assignment_expression, AstSubtractionAssignmentExpressionRef, unary, assignment)
DOUBLE_to_string(left_shift_assignment_expression, AstLeftShiftAssignmentExpressionRef, unary, assignment)
DOUBLE_to_string(right_shift_assignment_expression, AstRightShiftAssignmentExpressionRef, unary, assignment)
DOUBLE_to_string(bitwise_and_assignment_expression, AstBitwiseAndAssignmentExpressionRef, unary, assignment)
DOUBLE_to_string(bitwise_xor_assignment_expression, AstBitwiseXorAssignmentExpressionRef, unary, assignment)
DOUBLE_to_string(bitwise_or_assignment_expression, AstBitwiseOrAssignmentExpressionRef, unary, assignment)

SINGLE_to_string(expression, AstExpressionRef, expression)
DOUBLE_to_string(comma_expression, AstCommaExpressionRef, expression, assignment)

SINGLE_to_string(constant, AstConstantExpressionRef, conditional)

DOUBLE_to_string(declaration, AstDeclarationRef, declaration_specifier_list, init_declarator_list)
declaration_specifier_list_to_string() // vector!!

SINGLE_to_string(declaration_specifier, AstDeclarationSpecifierRef, declaration_specifier)

init_declarator_list_to_string() // vec

SINGLE_to_string(init_declarator, AstInitDeclaratorRef, init_declarator)
DOUBLE_to_string(declarator_with_initializer, AstDeclaratorWithInitializerRef, declarator, initializer)

SINGLE_to_string(storage_class_specifier, AstStorageClassSpecifierRef, storage_class_specifier)
SINGLE_to_string(type_specifier, AstTypeSpecifierRef, type_specifier)
SINGLE_to_string(struct_or_union_specifier, AstStructOrUnionSpecifierRef, struct_or_union_specifier)
struct_or_union_definition_to_string()
DOUBLE_to_string(struct_or_union_declaration, AstStructOrUnionDeclarationRef, struct_or_union, identifier)
SINGLE_to_string(struct_or_union, AstStructOrUnionRef, struct_or_union)
struct_declaration_list_to_string() // vec
DOUBLE_to_string(struct_declaration, AstStructDeclarationRef, specifier_qualifier_list, struct_declarator_list)
specifier_qualifier_list_to_string() // vev
SINGLE_to_string(specifier_qualifier, AstSpecifierQualifierRef, specifier_qualifier)
struct_declarator_list_to_string()
SINGLE_to_string(struct_declarator, AstStructDeclaratorRef, struct_declarator)
bit_field_declarator_to_string()
SINGLE_to_string(enum_specifier, AstEnumSpecifierRef, enum_specifier)
ppenum_definition_to_string()
SINGLE_to_string(enum_declaration, AstEnumDeclarationRef, identifier)
enumerator_list_to_string() // vec
SINGLE_to_string(enumerator, AstEnumeratorRef, enumerator)
DOUBLE_to_string(enumerator_with_initializer, AstEnumeratorWithInitializerRef, enumeration_constant, constant_expression)
SINGLE_to_string(type_qualifier, AstTypeQualifierRef, type_qualifier)
declarator_to_string()
SINGLE_to_string(direct_declarator, AstDirectDeclaratorRef, direct_declarator)
array_declarator_to_string()
DOUBLE_to_string(function_declarator, AstFunctionDeclaratorRef, direct_declarator, parameter_type_list)
old_style_function_declarator_to_string()
pointer_to_string()
type_qualifier_list_to_string() //vec
SINGLE_to_string(parameter_type_list, AstParameterTypeListRef, parameter_type_list)
SINGLE_to_string(variadic_parameter_list, AstVariadicParameterListRef, parameter_list)
parameter_list_to_string() // vec
SINGLE_to_string(parameter_declaration, AstParameterDeclarationRef, parameter_declaration)
DOUBLE_to_string(parameter_concrete_declaration, AstParameterConcreteDeclarationRef, declaration_specifier_list, declarator)
parameter_abstract_declaration_to_string()
identifier_list_to_string()
type_name_to_string()
SINGLE_to_string(abstract_declarator, AstAbstractDeclaratorRef, abstract_declarator)
pointer_abstract_declarator_to_string()
SINGLE_to_string(direct_abstract_declarator, AstDirectAbstractDeclaratorRef, direct_abstract_declarator)
array_abstract_declarator_to_string()
function_abstract_declarator_to_string()
SINGLE_to_string(typedef_name, AstTypedefNameRef, identifier)
SINGLE_to_string(initializer, AstInitializerRef, initializer)
initializer_list_to_string() // vec
SINGLE_to_string(statement, AstStatementRef, statement)
SINGLE_to_string(labeled_statement, AstLabeledStatementRef, labeled_statement)
DOUBLE_to_string(identifier_labeled_statement, AstIdentifierLabeledStatementRef, identifier, statement)
DOUBLE_to_string(case_labeled_statement, AstCaseLabeledStatementRef, constant_expression, statement)
SINGLE_to_string(default_labeled_statement, AstDefaultLabeledStatementRef, statement)
DOUBLE_to_string(compound_statement, AstCompoundStatementRef, declaration_list, statement_list)
declaration_list_to_string() // vec
statement_list_to_string() // vec
expression_statement_to_string()
SINGLE_to_string(selection_statement, AstSelectionStatementRef, selection_statement)
DOUBLE_to_string(if_statement, AstIfStatementRef, expression, statement)
if_else_statement_to_string()
DOUBLE_to_string(switch_statement, AstSwitchStatementRef, expression, statement)
SINGLE_to_string(iteration_statement, AstIterationStatementRef, iteration_statement)
DOUBLE_to_string(while_statement, AstWhileStatementRef, expression, statement)
DOUBLE_to_string(do_while_statement, AstDoWhileStatementRef, expression, statement)
for_statement_to_string()
SINGLE_to_string(jump_statement, AstJumpStatementRef, jump_statement)
SINGLE_to_string(goto_jump_statement, AstGotoJumpStatementRef, identifier)
SINGLE_to_string(continue_jump_statement, AstContinueJumpStatementRef, self)
SINGLE_to_string(break_jump_statement, AstBreakJumpStatementRef, self)
SINGLE_to_string(return_jump_statement, AstReturnJumpStatementRef, expression)
SINGLE_to_string(void_return_jump_statement, AstVoidReturnJumpStatementRef, self)
translation_unit_to_string() // vec
SINGLE_to_string(external_declaration, AstExternalDeclarationRef, external_declaration)
function_definition_to_string()
token_to_string() // typedef struct String* AstTokenRef;
