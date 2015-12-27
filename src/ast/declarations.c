#include "declarations.h"
#include "declarations_impl.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

AstRef ast_make_declaration(AstRef declaration_specifier_list, AstRef init_declarator_list) {
  AstRef self = NULL;
  if (ast_is_declaration_specifier_list(declaration_specifier_list) &&
      ast_is_init_declarator_list(init_declarator_list)) {
    AstDeclarationRef data = ast_palloc(struct AstDeclaration);
    data->declaration_specifier_list = declaration_specifier_list;
    data->init_declarator_list = init_declarator_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_DECLARATION;
    self->data.declaration = data;
  }
  return self;
}

AstRef ast_make_declaration_specifier_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstDeclarationSpecifierListRef data = ast_palloc(struct AstDeclarationSpecifierList);
  data->declaration_specifier_vector = ast_make_vector();
  self->tag = AST_DECLARATION_SPECIFIER_LIST;
  self->data.declaration_specifier_list = data;
  return self;
}

AstRef ast_push_declaration_specifier_list(
    AstRef declaration_specifier_list, AstRef declaration_specifier) {
  AstRef self = NULL;
  if (ast_is_declaration_specifier_list(declaration_specifier_list) &&
      ast_is_declaration_specifier(declaration_specifier)) {
    AstDeclarationSpecifierListRef data =
        ast_get_declaration_specifier_list(declaration_specifier_list);
    ast_push_vector(data->declaration_specifier_vector, declaration_specifier);
    self = declaration_specifier_list;
  }
  return self;
}

AstRef ast_make_declaration_specifier(AstRef declaration_specifier) {
  AstRef self = NULL;
  if (ast_is_storage_class_specifier(declaration_specifier) ||
      ast_is_type_specifier(declaration_specifier) ||
      ast_is_type_qualifier(declaration_specifier)) {
    AstDeclarationSpecifierRef data = ast_palloc(struct AstDeclarationSpecifier);
    data->declaration_specifier = declaration_specifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_DECLARATION_SPECIFIER;
    self->data.declaration_specifier = data;
  }
  return self;
}

AstRef ast_make_init_declarator_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstInitDeclaratorListRef data = ast_palloc(struct AstInitDeclaratorList);
  data->init_declarator_vector = ast_make_vector();
  self->tag = AST_INIT_DECLARATOR_LIST;
  self->data.init_declarator_list = data;
  return self;
}

AstRef ast_push_init_declarator_list(
    AstRef init_declarator_list, AstRef init_declarator) {
  AstRef self = NULL;
  if (ast_is_init_declarator_list(init_declarator_list) &&
      ast_is_init_declarator(init_declarator)) {
    AstInitDeclaratorListRef data = ast_get_init_declarator_list(init_declarator_list);
    ast_push_vector(data->init_declarator_vector, init_declarator);
    self = init_declarator_list;
  }
  return self;
}

AstRef ast_make_init_declarator(AstRef init_declarator) {
  AstRef self = NULL;
  if (ast_is_declarator(init_declarator) ||
      ast_is_declarator_with_initializer(init_declarator)) {
    AstInitDeclaratorRef data = ast_palloc(struct AstInitDeclarator);
    data->init_declarator = init_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_INIT_DECLARATOR;
    self->data.init_declarator = data;
  }
  return self;
}

AstRef ast_make_declarator_with_initializer(
    AstRef declarator, AstRef initializer) {
  AstRef self = NULL;
  if (ast_is_declarator(declarator) && ast_is_initializer(initializer)) {
    AstDeclaratorWithInitializerRef data = ast_palloc(struct AstDeclaratorWithInitializer);
    data->declarator = declarator;
    data->initializer = initializer;
    self = ast_palloc(struct Ast);
    self->tag = AST_DECLARATOR_WITH_INITIALIZER;
    self->data.declarator_with_initializer = data;
  }
  return self;
}

AstRef ast_make_storage_class_specifier(AstRef storage_class_specifier) {
  AstRef self = NULL;
  if (ast_is_token(storage_class_specifier)) {
    AstStorageClassSpecifierRef data = ast_palloc(struct AstStorageClassSpecifier);
    data->storage_class_specifier = storage_class_specifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_STORAGE_CLASS_SPECIFIER;
    self->data.storage_class_specifier = data;
  }
  return self;
}

AstRef ast_make_type_specifier(AstRef type_specifier) {
  AstRef self = NULL;
  if (ast_is_token(type_specifier) ||
      ast_is_struct_or_union_specifier(type_specifier) ||
      ast_is_enum_specifier(type_specifier) ||
      ast_is_typedef_name(type_specifier)) {
    AstTypeSpecifierRef data = ast_palloc(struct AstTypeSpecifier);
    data->type_specifier = type_specifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_TYPE_SPECIFIER;
    self->data.type_specifier = data;
  }
  return self;
}

AstRef ast_make_struct_or_union_specifier(AstRef struct_or_union_specifier) {
  AstRef self = NULL;
  if (ast_is_struct_or_union_definition(struct_or_union_specifier) ||
      ast_is_struct_or_union_declaration(struct_or_union_specifier)) {
    AstStructOrUnionSpecifierRef data = ast_palloc(struct AstStructOrUnionSpecifier);
    data->struct_or_union_specifier = struct_or_union_specifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_STRUCT_OR_UNION_SPECIFIER;
    self->data.struct_or_union_specifier = data;
  }
  return self;
}

AstRef ast_make_struct_or_union_definition(
    AstRef struct_or_union, AstNullableRef identifier, AstRef struct_declaration_list) {
  AstRef self = NULL;
  if (ast_is_struct_or_union(struct_or_union) &&
      (identifier == NULL ||
       ast_is_identifier(identifier)) &&
      ast_is_struct_declaration_list(struct_declaration_list)) {
    AstStructOrUnionDefinitionRef data = ast_palloc(struct AstStructOrUnionDefinition);
    data->struct_or_union = struct_or_union;
    data->identifier = identifier;
    data->struct_declaration_list = struct_declaration_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_STRUCT_OR_UNION_DEFINITION;
    self->data.struct_or_union_definition = data;
  }
  return self;
}

AstRef ast_make_struct_or_union_declaration(
    AstRef struct_or_union, AstRef identifier) {
  AstRef self = NULL;
  if (ast_is_struct_or_union(struct_or_union) &&
      ast_is_identifier(identifier)) {
    AstStructOrUnionDeclarationRef data = ast_palloc(struct AstStructOrUnionDeclaration);
    data->struct_or_union = struct_or_union;
    data->identifier = identifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_STRUCT_OR_UNION_DECLARATION;
    self->data.struct_or_union_declaration = data;
  }
  return self;
}

AstRef ast_make_struct_or_union(AstRef struct_or_union) {
  AstRef self = NULL;
  if (ast_is_token(struct_or_union)) {
    AstStructOrUnionRef data = ast_palloc(struct AstStructOrUnion);
    data->struct_or_union = struct_or_union;
    self = ast_palloc(struct Ast);
    self->tag = AST_STRUCT_OR_UNION;
    self->data.struct_or_union = data;
  }
  return self;
}

AstRef ast_make_struct_declaration_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstStructDeclarationListRef data = ast_palloc(struct AstStructDeclarationList);
  data->struct_declaration_vector = ast_make_vector();
  self->tag = AST_STRUCT_DECLARATION_LIST;
  self->data.struct_declaration_list = data;
  return self;
}

AstRef ast_push_struct_declaration_list(
    AstRef struct_declaration_list, AstRef struct_declaration) {
  AstRef self = NULL;
  if (ast_is_struct_declaration_list(struct_declaration_list) &&
      ast_is_struct_declaration(struct_declaration)) {
    AstStructDeclarationListRef data = ast_get_struct_declaration_list(struct_declaration_list);
    ast_push_vector(data->struct_declaration_vector, struct_declaration);
    self = struct_declaration_list;
  }
  return self;
}

AstRef ast_make_struct_declaration(
    AstRef specifier_qualifier_list, AstRef struct_declarator_list) {
  AstRef self = NULL;
  if (ast_is_specifier_qualifier_list(specifier_qualifier_list) &&
      ast_is_struct_declarator_list(struct_declarator_list)) {
    AstStructDeclarationRef data = ast_palloc(struct AstStructDeclaration);
    data->specifier_qualifier_list = specifier_qualifier_list;
    data->struct_declarator_list = struct_declarator_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_STRUCT_DECLARATION;
    self->data.struct_declaration = data;
  }
  return self;
}

AstRef ast_make_specifier_qualifier_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstSpecifierQualifierListRef data = ast_palloc(struct AstSpecifierQualifierList);
  data->specifier_qualifier_vector = ast_make_vector();
  self->tag = AST_SPECIFIER_QUALIFIER_LIST;
  self->data.specifier_qualifier_list = data;
  return self;
}

AstRef ast_push_specifier_qualifier_list(
    AstRef specifier_qualifier, AstRef specifier_qualifier_list) {
  AstRef self = NULL;
  if (ast_is_specifier_qualifier(specifier_qualifier) &&
      ast_is_specifier_qualifier_list(specifier_qualifier_list)) {
    AstSpecifierQualifierListRef data = ast_get_specifier_qualifier_list(specifier_qualifier_list);
    ast_push_vector(data->specifier_qualifier_vector, specifier_qualifier);
    self = specifier_qualifier_list;
  }
  return self;
}

AstRef ast_make_specifier_qualifier(AstRef specifier_qualifier) {
  AstRef self = NULL;
  if (ast_is_type_specifier(specifier_qualifier) ||
      ast_is_type_qualifier(specifier_qualifier)) {
    AstSpecifierQualifierRef data = ast_palloc(struct AstSpecifierQualifier);
    data->specifier_qualifier = specifier_qualifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_SPECIFIER_QUALIFIER;
    self->data.specifier_qualifier = data;
  }
  return self;
}

AstRef ast_make_struct_declarator_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstStructDeclaratorListRef data = ast_palloc(struct AstStructDeclaratorList);
  data->struct_declarator_vector = ast_make_vector();
  self->tag = AST_STRUCT_DECLARATOR_LIST;
  self->data.struct_declarator_list = data;
  return self;
}

AstRef ast_push_struct_declarator_list(
    AstRef struct_declarator_list, AstRef struct_declarator) {
  AstRef self = NULL;
  if (ast_is_struct_declarator_list(struct_declarator_list) &&
      ast_is_struct_declarator(struct_declarator)) {
    AstStructDeclaratorListRef data = ast_get_struct_declarator_list(struct_declarator_list);
    ast_push_vector(data->struct_declarator_vector, struct_declarator);
    self = struct_declarator_list;
  }
  return self;
}

AstRef ast_make_struct_declarator(AstRef struct_declarator) {
  AstRef self = NULL;
  if (ast_is_declarator(struct_declarator) ||
      ast_is_bit_field_declarator(struct_declarator)) {
    AstStructDeclaratorRef data = ast_palloc(struct AstStructDeclarator);
    data->struct_declarator = struct_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_STRUCT_DECLARATOR;
    self->data.struct_declarator = data;
  }
  return self;
}

AstRef ast_make_bit_field_declarator(
    AstNullableRef declarator, AstRef constant_expression) {
  AstRef self = NULL;
  if ((declarator == NULL || ast_is_declarator(declarator)) &&
       ast_is_constant_expression(constant_expression)) {
    AstBitFieldDeclaratorRef data = ast_palloc(struct AstBitFieldDeclarator);
    data->declarator = declarator;
    data->constant_expression = constant_expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_BIT_FIELD_DECLARATOR;
    self->data.bit_field_declarator = data;
  }
  return self;
}

AstRef ast_make_enum_specifier(AstRef enum_specifier) {
  AstRef self = NULL;
  if (ast_is_enum_definition(enum_specifier) ||
      ast_is_enum_declaration(enum_specifier)) {
    AstEnumSpecifierRef data = ast_palloc(struct AstEnumSpecifier);
    data->enum_specifier = enum_specifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_ENUM_SPECIFIER;
    self->data.enum_specifier = data;
  }
  return self;
}

AstRef ast_make_enum_definition(AstNullableRef identifier, AstRef enumerator_list) {
  AstRef self = NULL;
  if ((identifier == NULL || ast_is_identifier(identifier)) &&
      ast_is_enumerator_list(enumerator_list)) {
    AstEnumDefinitionRef data = ast_palloc(struct AstEnumDefinition);
    data->identifier = identifier;
    data->enumerator_list = enumerator_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_ENUM_DEFINITION;
    self->data.enum_definition = data;
  }
  return self;
}

AstRef ast_make_enum_declaration(AstRef identifier) {
  AstRef self = NULL;
  if (ast_is_identifier(identifier)) {
    AstEnumDeclarationRef data = ast_palloc(struct AstEnumDeclaration);
    data->identifier = identifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_ENUM_DECLARATION;
    self->data.enum_declaration = data;
  }
  return self;
}

AstRef ast_make_enumerator_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstEnumeratorListRef data = ast_palloc(struct AstEnumeratorList);
  data->enumerator_vector = ast_make_vector();
  self->tag = AST_ENUMERATOR_LIST;
  self->data.enumerator_list = data;
  return self;
}

AstRef ast_push_enumerator_list(AstRef enumerator_list, AstRef enumerator) {
  AstRef self = NULL;
  if (ast_is_enumerator_list(enumerator_list) &&
      ast_is_enumerator(enumerator)) {
    AstEnumeratorListRef data = ast_get_enumerator_list(enumerator_list);
    ast_push_vector(data->enumerator_vector, enumerator);
    self = enumerator_list;
  }
  return self;
}

AstRef ast_make_enumerator(AstRef enumerator) {
  AstRef self = NULL;
  if (ast_is_enumeration_constant(enumerator) ||
      ast_is_enumerator_with_initializer(enumerator)) {
    AstEnumeratorRef data = ast_palloc(struct AstEnumerator);
    data->enumerator = enumerator;
    self = ast_palloc(struct Ast);
    self->tag = AST_ENUMERATOR;
    self->data.enumerator = data;
  }
  return self;
}

AstRef ast_make_enumerator_with_initializer(
    AstRef enumeration_constant, AstRef constant_expression) {
  AstRef self = NULL;
  if (ast_is_identifier(enumeration_constant) &&
      ast_is_constant_expression(constant_expression)) {
    AstEnumeratorWithInitializerRef data = ast_palloc(struct AstEnumeratorWithInitializer);
    data->enumeration_constant = enumeration_constant;
    data->constant_expression = constant_expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_ENUMERATOR_WITH_INITIALIZER;
    self->data.enumerator_with_initializer = data;
  }
  return self;
}

AstRef ast_make_type_qualifier(AstRef type_qualifier) {
  AstRef self = NULL;
  if (ast_is_token(type_qualifier)) {
    AstTypeQualifierRef data = ast_palloc(struct AstTypeQualifier);
    data->type_qualifier = type_qualifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_TYPE_QUALIFIER;
    self->data.type_qualifier = data;
  }
  return self;
}

AstRef ast_make_declarator(AstNullableRef pointer, AstRef direct_declarator) {
  AstRef self = NULL;
  if ((pointer == NULL ||
       ast_is_pointer(pointer)) &&
      ast_is_direct_declarator(direct_declarator)) {
    AstDeclaratorRef data = ast_palloc(struct AstDeclarator);
    data->pointer = pointer;
    data->direct_declarator = direct_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_DECLARATOR;
    self->data.declarator = data;
  }
  return self;
}

AstRef ast_make_direct_declarator(AstRef direct_declarator) {
  AstRef self = NULL;
  if (ast_is_identifier(direct_declarator) ||
      ast_is_declarator(direct_declarator) ||
      ast_is_array_declarator(direct_declarator) ||
      ast_is_function_declarator(direct_declarator) ||
      ast_is_old_style_function_declarator(direct_declarator)) {
    AstDirectDeclaratorRef data = ast_palloc(struct AstDirectDeclarator);
    data->direct_declarator = direct_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_DIRECT_DECLARATOR;
    self->data.direct_declarator = data;
  }
  return self;
}

AstRef ast_make_array_declarator(
    AstRef direct_declarator, AstNullableRef constant_expression) {
  AstRef self = NULL;
  if (ast_is_direct_declarator(direct_declarator) &&
      (constant_expression == NULL ||
       ast_is_constant_expression(constant_expression))) {
    AstArrayDeclaratorRef data = ast_palloc(struct AstArrayDeclarator);
    data->direct_declarator = direct_declarator;
    data->constant_expression = constant_expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_ARRAY_DECLARATOR;
    self->data.array_declarator = data;
  }
  return self;
}

AstRef ast_make_function_declarator(
    AstRef direct_declarator, AstRef parameter_type_list) {
  AstRef self = NULL;
  if (ast_is_direct_declarator(direct_declarator) &&
      ast_is_parameter_type_list(parameter_type_list)) {
    AstFunctionDeclaratorRef data = ast_palloc(struct AstFunctionDeclarator);
    data->direct_declarator = direct_declarator;
    data->parameter_type_list = parameter_type_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_FUNCTION_DECLARATOR;
    self->data.function_declarator = data;
  }
  return self;
}

AstRef ast_make_old_style_function_declarator(
    AstRef direct_declarator, AstNullableRef identifier_list) {
  AstRef self = NULL;
  if (ast_is_direct_declarator(direct_declarator) &&
      (identifier_list == NULL ||
       ast_is_identifier_list(identifier_list))) {
    AstOldStyleFunctionDeclaratorRef data = ast_palloc(struct AstOldStyleFunctionDeclarator);
    data->direct_declarator = direct_declarator;
    data->identifier_list = identifier_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_OLD_STYLE_FUNCTION_DECLARATOR;
    self->data.old_style_function_declarator = data;
  }
  return self;
}

AstRef ast_make_pointer(
    AstNullableRef type_qualifier_list, AstNullableRef pointer) {
  AstRef self = NULL;
  if ((type_qualifier_list == NULL ||
       ast_is_type_qualifier_list(type_qualifier_list)) &&
      (pointer == NULL ||
       ast_is_pointer(pointer))) {
    AstPointerRef data = ast_palloc(struct AstPointer);
    data->type_qualifier_list = type_qualifier_list;
    data->pointer = pointer;
    self = ast_palloc(struct Ast);
    self->tag = AST_POINTER;
    self->data.pointer = data;
  }
  return self;
}

AstRef ast_make_type_qualifier_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstTypeQualifierListRef data = ast_palloc(struct AstTypeQualifierList);
  data->type_qualifier_vector = ast_make_vector();
  self->tag = AST_TYPE_QUALIFIER_LIST;
  self->data.type_qualifier_list = data;
  return self;
}

AstRef ast_push_type_qualifier_list(
    AstRef type_qualifier_list, AstRef type_qualifier) {
  AstRef self = NULL;
  if (ast_is_type_qualifier_list(type_qualifier_list) &&
      ast_is_type_qualifier(type_qualifier)) {
    AstTypeQualifierListRef data = ast_get_type_qualifier_list(type_qualifier_list);
    ast_push_vector(data->type_qualifier_vector, type_qualifier);
    self = type_qualifier_list;
  }
  return self;
}

AstRef ast_make_parameter_type_list(AstRef parameter_type_list) {
  AstRef self = NULL;
  if (ast_is_variadic_parameter_list(parameter_type_list) ||
      ast_is_parameter_list(parameter_type_list)) {
    AstParameterTypeListRef data = ast_palloc(struct AstParameterTypeList);
    data->parameter_type_list = parameter_type_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_PARAMETER_TYPE_LIST;
    self->data.parameter_type_list = data;
  }
  return self;
}

AstRef ast_make_variadic_parameter_list(AstRef parameter_list) {
  AstRef self = NULL;
  if (ast_is_parameter_list(parameter_list)) {
    AstVariadicParameterListRef data =
      ast_palloc(struct AstVariadicParameterList);
    data->parameter_list = parameter_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_VARIADIC_PARAMETER_LIST;
    self->data.variadic_parameter_list = data;
  }
  return self;
}

AstRef ast_make_parameter_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstParameterListRef data = ast_palloc(struct AstParameterList);
  data->parameter_declaration_vector = ast_make_vector();
  self->tag = AST_PARAMETER_LIST;
  self->data.parameter_list = data;
  return self;
}

AstRef ast_push_parameter_list(
    AstRef parameter_list, AstRef parameter_declaration) {
  AstRef self = NULL;
  if (ast_is_parameter_list(parameter_list) &&
      ast_is_parameter_declaration(parameter_declaration)) {
    AstParameterListRef data = ast_get_parameter_list(parameter_list);
    ast_push_vector(data->parameter_declaration_vector, parameter_declaration);
    self = parameter_list;
  }
  return self;
}

AstRef ast_make_parameter_declaration(AstRef parameter_declaration) {
  AstRef self = NULL;
  if (ast_is_parameter_concrete_declaration(parameter_declaration) ||
      ast_is_parameter_abstract_declaration(parameter_declaration)) {
    AstParameterDeclarationRef data = ast_palloc(struct AstParameterDeclaration);
    data->parameter_declaration = parameter_declaration;
    self = ast_palloc(struct Ast);
    self->tag = AST_PARAMETER_DECLARATION;
    self->data.parameter_declaration = data;
  }
  return self;
}

AstRef ast_make_parameter_concrete_declaration(
    AstRef declaration_specifier_list, AstRef declarator) {
  AstRef self = NULL;
  if (ast_is_declaration_specifier_list(declaration_specifier_list) &&
      ast_is_declarator(declarator)) {
    AstParameterConcreteDeclarationRef data = ast_palloc(struct AstParameterConcreteDeclaration);
    data->declaration_specifier_list = declaration_specifier_list;
    data->declarator = declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_PARAMETER_CONCRETE_DECLARATION;
    self->data.parameter_concrete_declaration = data;
  }
  return self;
}

AstRef ast_make_parameter_abstract_declaration(
    AstRef declaration_specifier_list, AstNullableRef abstract_declarator) {
  AstRef self = NULL;
  if (ast_is_declaration_specifier_list(declaration_specifier_list) &&
      (abstract_declarator == NULL ||
       ast_is_abstract_declarator(abstract_declarator))) {
    AstParameterAbstractDeclarationRef data = ast_palloc(struct AstParameterAbstractDeclaration);
    data->declaration_specifier_list = declaration_specifier_list;
    data->abstract_declarator = abstract_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_PARAMETER_ABSTRACT_DECLARATION;
    self->data.parameter_abstract_declaration = data;
  }
  return self;
}

AstRef ast_make_identifier_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstIdentifierListRef data = ast_palloc(struct AstIdentifierList);
  data->identifier_vector = ast_make_vector();
  self->tag = AST_IDENTIFIER_LIST;
  self->data.identifier_list = data;
  return self;
}

AstRef ast_push_identifier_list(AstRef identifier_list, AstRef identifier) {
  AstRef self = NULL;
  if (ast_is_identifier_list(identifier_list) &&
      ast_is_identifier(identifier)) {
    AstIdentifierListRef data = ast_get_identifier_list(identifier_list);
    ast_push_vector(data->identifier_vector, identifier);
    self = identifier_list;
  }
  return self;
}

AstRef ast_make_type_name(
    AstRef specifier_qualifier_list, AstNullableRef abstract_declarator) {
  AstRef self = NULL;
  if (ast_is_specifier_qualifier_list(specifier_qualifier_list) &&
      (abstract_declarator == NULL ||
       ast_is_abstract_declarator(abstract_declarator))) {
    AstTypeNameRef data = ast_palloc(struct AstTypeName);
    data->specifier_qualifier_list = specifier_qualifier_list;
    data->abstract_declarator = abstract_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_TYPE_NAME;
    self->data.type_name = data;
  }
  return self;
}

AstRef ast_make_abstract_declarator(AstRef abstract_declarator) {
  AstRef self = NULL;
  if (ast_is_pointer(abstract_declarator) ||
      ast_is_pointer_abstract_declarator(abstract_declarator)) {
    AstAbstractDeclaratorRef data = ast_palloc(struct AstAbstractDeclarator);
    data->abstract_declarator = abstract_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_ABSTRACT_DECLARATOR;
    self->data.abstract_declarator = data;
  }
  return self;
}

AstRef ast_make_pointer_abstract_declarator(
    AstNullableRef pointer, AstRef direct_abstract_declarator) {
  AstRef self = NULL;
  if ((pointer == NULL || ast_is_pointer(pointer)) &&
      ast_is_direct_abstract_declarator(direct_abstract_declarator)) {
    AstPointerAbstractDeclaratorRef data = ast_palloc(struct AstPointerAbstractDeclarator);
    data->pointer = pointer;
    data->direct_abstract_declarator = direct_abstract_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_POINTER_ABSTRACT_DECLARATOR;
    self->data.pointer_abstract_declarator = data;
  }
  return self;
}

AstRef ast_make_direct_abstract_declarator(AstRef direct_abstract_declarator) {
  AstRef self = NULL;
  if (ast_is_abstract_declarator(direct_abstract_declarator) ||
      ast_is_array_abstract_declarator(direct_abstract_declarator) ||
      ast_is_function_abstract_declarator(direct_abstract_declarator)) {
    AstDirectAbstractDeclaratorRef data = ast_palloc(struct AstDirectAbstractDeclarator);
    data->direct_abstract_declarator = direct_abstract_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_DIRECT_ABSTRACT_DECLARATOR;
    self->data.direct_abstract_declarator = data;
  }
  return self;
}

AstRef ast_make_array_abstract_declarator(
    AstNullableRef direct_abstract_declarator,
    AstNullableRef constant_expression) {
  AstRef self = NULL;
  if ((direct_abstract_declarator == NULL ||
       ast_is_direct_abstract_declarator(direct_abstract_declarator)) &&
      (constant_expression == NULL ||
       ast_is_constant_expression(constant_expression))) {
    AstArrayAbstractDeclaratorRef data = ast_palloc(struct AstArrayAbstractDeclarator);
    data->direct_abstract_declarator = direct_abstract_declarator;
    data->constant_expression = constant_expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_ARRAY_ABSTRACT_DECLARATOR;
    self->data.array_abstract_declarator = data;
  }
  return self;
}

AstRef ast_make_function_abstract_declarator(
    AstNullableRef direct_abstract_declarator, AstNullableRef parameter_type_list) {
  AstRef self = NULL;
  if ((direct_abstract_declarator == NULL ||
       ast_is_direct_abstract_declarator(direct_abstract_declarator)) &&
      (parameter_type_list == NULL ||
       ast_is_parameter_type_list(parameter_type_list))) {
    AstFunctionAbstractDeclaratorRef data = ast_palloc(struct AstFunctionAbstractDeclarator);
    data->direct_abstract_declarator = direct_abstract_declarator;
    data->parameter_type_list = parameter_type_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_FUNCTION_ABSTRACT_DECLARATOR;
    self->data.function_abstract_declarator = data;
  }
  return self;
}

AstRef ast_make_typedef_name(AstRef identifier) {
  AstRef self = NULL;
  if (ast_is_identifier(identifier)) {
    AstTypedefNameRef data = ast_palloc(struct AstTypedefName);
    data->identifier = identifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_TYPEDEF_NAME;
    self->data.typedef_name = data;
  }
  return self;
}

AstRef ast_make_initializer(AstRef initializer) {
  AstRef self = NULL;
  if (ast_is_assignment_expression(initializer) ||
      ast_is_initializer_list(initializer)) {
    AstInitializerRef data = ast_palloc(struct AstInitializer);
    data->initializer = initializer;
    self = ast_palloc(struct Ast);
    self->tag = AST_INITIALIZER;
    self->data.initializer = data;
  }
  return self;
}

AstRef ast_make_initializer_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstInitializerListRef data = ast_palloc(struct AstInitializerList);
  data->initializer_vector = ast_make_vector();
  self->tag = AST_INITIALIZER_LIST;
  self->data.initializer_list = data;
  return self;
}

AstRef ast_push_initializer_list(AstRef initializer_list, AstRef initializer) {
  AstRef self = NULL;
  if (ast_is_initializer_list(initializer_list) &&
      ast_is_initializer(initializer)) {
    AstInitializerListRef data = ast_get_initializer_list(initializer_list);
    ast_push_vector(data->initializer_vector, initializer);
    self = initializer_list;
  }
  return self;
}
