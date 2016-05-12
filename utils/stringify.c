#include <stdio.h>

#define SINGLE_to_string(NAME, TYPE, MEMBER) \
  void NAME ## _to_string(TYPE val) {        \
    printf("TYPE : {\n");                    \
    vidualizer(val->MEMBER);                 \
    printf("}\n");                           \
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

void array_subscript_expression_to_string(AstArraySubscriptExpressionRef val) {
  printf("AstArraySubscriptExpressionRef: {\n");
  printf("array:");
  vidualizer(val->array);
  printf("subscript:");
  vidualizer(val->subscript);
  printf("}\n");
}

void function_call_expression_to_string(AstFunctionCallExpressionRef val) {
  printf("AstFunctionCallExpressionRef: {\n");
  printf("function:");
  vidualizer(val->function);
  printf("argument_list:");
  vidualizer(val->argument_list);
  printf("}\n");
}

void member_access_expression_to_string(AstMemberAccessExpressionRef val) {
  printf("AstMemberAccessExpressionRef: {\n");
  printf("object:");
  vidualizer(val->object);
  printf("member:");
  vidualizer(val->member);
  printf("}\n");
}

void member_access_through_pointer_expression_to_string(AstMemberAccessThroughPointerExpressionRef val) {
  printf("AstMemberAccessThroughPointerExpressionRef: {\n");
  printf("object:");
  vidualizer(val->object);
  printf("member:");
  vidualizer(val->member);
  printf("}\n");
}


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

type_cast_expression_to_string()

SINGLE_to_string(multiplicative_expression, AstMultiplicativeExpressionRef, expression)

product_expression_to_string()

division_expression_to_string()

modulo_expression_to_string()

SINGLE_to_string(additive_expression, AstAdditiveExpressionRef, expression)

addition_expression_to_string()

subtraction_expression_to_string()

SINGLE_to_string(shift_expression, AstShiftExpressionRef, expression)

left_shift_expression_to_string()
right_shift_expression_to_string()

SINGLE_to_string(relational_expression, AstRelationalExpressionRef, expression)

less_than_expression_to_string()
greater_than_expression_to_string()
less_than_or_equal_to_expression_to_string()
greater_than_or_equal_to_expression_to_string()

SINGLE_to_string(equality_expression, AstEqualityExpressionRef, expression)

equal_to_expression_to_string()
not_equal_to_expression_to_string()

SINGLE_to_string(bitwise_and_expression, AstBitwiseAndExpressionRef, expression)

bitwise_and_operator_expression_to_string()

SINGLE_to_string(bitwise_xor_expression, AstBitwiseXorExpressionRef, expression)

bitwise_xor_operator_expression_to_string()

SINGLE_to_string(bitwise_or_expression, AstBitwiseOrExpressionRef, expression)

bitwise_or_operator_expression_to_string()

SINGLE_to_string(logical_and_expression, AstLogicalAndExpressionRef, expression)

logical_and_operator_expression_to_string()

SINGLE_to_string(logical_or_expression, AstLogicalOrExpressionRef, expression)

logical_or_operator_expression_to_string()

SINGLE_to_string(conditional_expression, AstConditionalExpressionRef, expression)

conditional_operator_expression_to_string()

SINGLE_to_string(assignment_expression, AstAssignmentExpressionRef, expression)

basic_assignment_expression_to_string()

ion_to_stringmultiplication_assignment_expression_to_string↵

multiplication_assignment_expression_to_string()
division_assignment_expression_to_string()
modulo_assignment_expression_to_string()
addition_assignment_expression_to_string()
subtraction_assignment_expression_to_string()
left_shift_assignment_expression_to_string()
right_shift_assignment_expression_to_string()
bitwise_and_assignment_expression_to_string()
bitwise_xor_assignment_expression_to_string()
bitwise_or_assignment_expression_to_string()

SINGLE_to_string(expression, AstExpressionRef, expression)

comma_expression_to_string()

SINGLE_to_string(constant, AstConstantExpressionRef, conditional)

declaration_to_string()
declaration_specifier_list_to_string() // vector!!

SINGLE_to_string(declaration_specifier, AstDeclarationSpecifierRef, declaration_specifier)

init_declarator_list_to_string() // vec

SINGLE_to_string(init_declarator, AstInitDeclaratorRef, init_declarator)
declarator_with_initializer_to_string()

SINGLE_to_string(storage_class_specifier, AstStorageClassSpecifierRef, storage_class_specifier)
SINGLE_to_string(type_specifier, AstTypeSpecifierRef, type_specifier)
SINGLE_to_string(struct_or_union_specifier, AstStructOrUnionSpecifierRef, struct_or_union_specifier)
struct_or_union_definition_to_string()
struct_or_union_declaration_to_string()
SINGLE_to_string(struct_or_union, AstStructOrUnionRef, struct_or_union)
struct_declaration_list_to_string() // vec
struct_declaration_to_string()
specifier_qualifier_list_to_string() // vev
SINGLE_to_string(specifier_qualifier, AstSpecifierQualifierRef, specifier_qualifier)
struct_declarator_list_to_string()
SINGLE_to_string(struct_declarator, AstStructDeclaratorRef, struct_declarator)
bit_field_declarator_to_string()
SINGLE_to_string(enum_specifier, AstEnumSpecifierRef, enum_specifier)
enum_definition_to_string()
SINGLE_to_string(enum_declaration, AstEnumDeclarationRef, identifier)
enumerator_list_to_string() // vec
SINGLE_to_string(enumerator, AstEnumeratorRef, enumerator)
enumerator_with_initializer_to_string()
SINGLE_to_string(type_qualifier, AstTypeQualifierRef, type_qualifier)
declarator_to_string()
SINGLE_to_string(direct_declarator, AstDirectDeclaratorRef, direct_declarator)
array_declarator_to_string()
function_declarator_to_string()
old_style_function_declarator_to_string()
pointer_to_string()
type_qualifier_list_to_string() //vec
SINGLE_to_string(parameter_type_list, AstParameterTypeListRef, parameter_type_list)
SINGLE_to_string(variadic_parameter_list, AstVariadicParameterListRef, parameter_list)
parameter_list_to_string() // vec
SINGLE_to_string(parameter_declaration, AstParameterDeclarationRef, parameter_declaration)
parameter_concrete_declaration_to_string()
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
identifier_labeled_statement_to_string()
case_labeled_statement_to_string()
SINGLE_to_string(default_labeled_statement, AstDefaultLabeledStatementRef, statement)
compound_statement_to_string()
declaration_list_to_string() // vec
statement_list_to_string() // vec
expression_statement_to_string()
SINGLE_to_string(selection_statement, AstSelectionStatementRef, selection_statement)
if_statement_to_string()
if_else_statement_to_string()
switch_statement_to_string()
SINGLE_to_string(iteration_statement, AstIterationStatementRef, iteration_statement)
while_statement_to_string()
do_while_statement_to_string()
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
