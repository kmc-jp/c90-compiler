#include "get_method.h"
#include "is_method.h"

#define DEFINE_AST_GET_METHOD(lower, camel) \
  Ast ## camel ## Ref ast_get_ ## lower(AstRef ast) { \
    if (ast_is_ ## lower(ast)) { \
      return ast->data.lower; \
    } \
    return NULL; \
  }

DEFINE_AST_GET_METHOD(identifier, Identifier)
DEFINE_AST_GET_METHOD(constant, Constant)
DEFINE_AST_GET_METHOD(floating_constant, FloatingConstant)
DEFINE_AST_GET_METHOD(integer_constant, IntegerConstant)
DEFINE_AST_GET_METHOD(enumeration_constant, EnumerationConstant)
DEFINE_AST_GET_METHOD(character_constant, CharacterConstant)
DEFINE_AST_GET_METHOD(string_literal, StringLiteral)
DEFINE_AST_GET_METHOD(primary_expression, PrimaryExpression)
DEFINE_AST_GET_METHOD(postfix_expression, PostfixExpression)
DEFINE_AST_GET_METHOD(array_subscript_expression, ArraySubscriptExpression)
DEFINE_AST_GET_METHOD(function_call_expression, FunctionCallExpression)
DEFINE_AST_GET_METHOD(member_access_expression, MemberAccessExpression)
DEFINE_AST_GET_METHOD(member_access_through_pointer_expression, MemberAccessThroughPointerExpression)
DEFINE_AST_GET_METHOD(postfix_increment_expression, PostfixIncrementExpression)
DEFINE_AST_GET_METHOD(postfix_decrement_expression, PostfixDecrementExpression)
DEFINE_AST_GET_METHOD(argument_expression_list, ArgumentExpressionList)
DEFINE_AST_GET_METHOD(unary_expression, UnaryExpression)
DEFINE_AST_GET_METHOD(prefix_increment_expression, PrefixIncrementExpression)
DEFINE_AST_GET_METHOD(prefix_decrement_expression, PrefixDecrementExpression)
DEFINE_AST_GET_METHOD(address_of_expression, AddressOfExpression)
DEFINE_AST_GET_METHOD(pointer_dereference_expression, PointerDereferenceExpression)
DEFINE_AST_GET_METHOD(unary_plus_expression, UnaryPlusExpression)
DEFINE_AST_GET_METHOD(unary_minus_expression, UnaryMinusExpression)
DEFINE_AST_GET_METHOD(bitwise_not_expression, BitwiseNotExpression)
DEFINE_AST_GET_METHOD(logical_not_expression, LogicalNotExpression)
DEFINE_AST_GET_METHOD(sizeof_expression, SizeofExpression)
DEFINE_AST_GET_METHOD(sizeof_type_expression, SizeofTypeExpression)
DEFINE_AST_GET_METHOD(cast_expression, CastExpression)
DEFINE_AST_GET_METHOD(type_cast_expression, TypeCastExpression)
DEFINE_AST_GET_METHOD(multiplicative_expression, MultiplicativeExpression)
DEFINE_AST_GET_METHOD(product_expression, ProductExpression)
DEFINE_AST_GET_METHOD(division_expression, DivisionExpression)
DEFINE_AST_GET_METHOD(modulo_expression, ModuloExpression)
DEFINE_AST_GET_METHOD(additive_expression, AdditiveExpression)
DEFINE_AST_GET_METHOD(addition_expression, AdditionExpression)
DEFINE_AST_GET_METHOD(subtraction_expression, SubtractionExpression)
DEFINE_AST_GET_METHOD(shift_expression, ShiftExpression)
DEFINE_AST_GET_METHOD(left_shift_expression, LeftShiftExpression)
DEFINE_AST_GET_METHOD(right_shift_expression, RightShiftExpression)
DEFINE_AST_GET_METHOD(relational_expression, RelationalExpression)
DEFINE_AST_GET_METHOD(less_than_expression, LessThanExpression)
DEFINE_AST_GET_METHOD(greater_than_expression, GreaterThanExpression)
DEFINE_AST_GET_METHOD(less_than_or_equal_to_expression, LessThanOrEqualToExpression)
DEFINE_AST_GET_METHOD(greater_than_or_equal_to_expression, GreaterThanOrEqualToExpression)
DEFINE_AST_GET_METHOD(equality_expression, EqualityExpression)
DEFINE_AST_GET_METHOD(and_expression, AndExpression)
DEFINE_AST_GET_METHOD(exclusive_or_expression, ExclusiveOrExpression)
DEFINE_AST_GET_METHOD(inclusive_or_expression, InclusiveOrExpression)
DEFINE_AST_GET_METHOD(logical_and_expression, LogicalAndExpression)
DEFINE_AST_GET_METHOD(logical_or_expression, LogicalOrExpression)
DEFINE_AST_GET_METHOD(conditional_expression, ConditionalExpression)
DEFINE_AST_GET_METHOD(assignment_expression, AssignmentExpression)
DEFINE_AST_GET_METHOD(assignment_operator, AssignmentOperator)
DEFINE_AST_GET_METHOD(expression, Expression)
DEFINE_AST_GET_METHOD(constant_expression, ConstantExpression)
DEFINE_AST_GET_METHOD(declaration, Declaration)
DEFINE_AST_GET_METHOD(declaration_specifiers, DeclarationSpecifiers)
DEFINE_AST_GET_METHOD(init_declarator_list, InitDeclaratorList)
DEFINE_AST_GET_METHOD(init_declarator, InitDeclarator)
DEFINE_AST_GET_METHOD(storage_class_specifier, StorageClassSpecifier)
DEFINE_AST_GET_METHOD(type_specifier, TypeSpecifier)
DEFINE_AST_GET_METHOD(struct_or_union_specifier, StructOrUnionSpecifier)
DEFINE_AST_GET_METHOD(struct_or_union, StructOrUnion)
DEFINE_AST_GET_METHOD(struct_declaration_list, StructDeclarationList)
DEFINE_AST_GET_METHOD(struct_declaration, StructDeclaration)
DEFINE_AST_GET_METHOD(specifier_qualifier_list, SpecifierQualifierList)
DEFINE_AST_GET_METHOD(struct_declarator_list, StructDeclaratorList)
DEFINE_AST_GET_METHOD(struct_declarator, StructDeclarator)
DEFINE_AST_GET_METHOD(enum_specifier, EnumSpecifier)
DEFINE_AST_GET_METHOD(enumerator_list, EnumeratorList)
DEFINE_AST_GET_METHOD(enumerator, Enumerator)
DEFINE_AST_GET_METHOD(type_qualifier, TypeQualifier)
DEFINE_AST_GET_METHOD(declarator, Declarator)
DEFINE_AST_GET_METHOD(direct_declarator, DirectDeclarator)
DEFINE_AST_GET_METHOD(pointer, Pointer)
DEFINE_AST_GET_METHOD(type_qualifier_list, TypeQualifierList)
DEFINE_AST_GET_METHOD(parameter_type_list, ParameterTypeList)
DEFINE_AST_GET_METHOD(parameter_list, ParameterList)
DEFINE_AST_GET_METHOD(parameter_declaration, ParameterDeclaration)
DEFINE_AST_GET_METHOD(identifier_list, IdentifierList)
DEFINE_AST_GET_METHOD(type_name, TypeName)
DEFINE_AST_GET_METHOD(abstract_declarator, AbstractDeclarator)
DEFINE_AST_GET_METHOD(direct_abstract_declarator, DirectAbstractDeclarator)
DEFINE_AST_GET_METHOD(typedef_name, TypedefName)
DEFINE_AST_GET_METHOD(initializer, Initializer)
DEFINE_AST_GET_METHOD(initializer_list, InitializerList)
DEFINE_AST_GET_METHOD(statement, Statement)
DEFINE_AST_GET_METHOD(labeled_statement, LabeledStatement)
DEFINE_AST_GET_METHOD(compound_statement, CompoundStatement)
DEFINE_AST_GET_METHOD(declaration_list, DeclarationList)
DEFINE_AST_GET_METHOD(statement_list, StatementList)
DEFINE_AST_GET_METHOD(expression_statement, ExpressionStatement)
DEFINE_AST_GET_METHOD(selection_statement, SelectionStatement)
DEFINE_AST_GET_METHOD(iteration_statement, IterationStatement)
DEFINE_AST_GET_METHOD(jump_statement, JumpStatement)
DEFINE_AST_GET_METHOD(translation_unit, TranslationUnit)
DEFINE_AST_GET_METHOD(external_declaration, ExternalDeclaration)
DEFINE_AST_GET_METHOD(function_definition, FunctionDefinition)
DEFINE_AST_GET_METHOD(vector, Vector)
DEFINE_AST_GET_METHOD(token, Token)
