#include "declarations.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

struct AstDeclaration {
};

struct AstDeclarationSpecifiers {
};

struct AstInitDeclaratorList {
};

struct AstInitDeclarator {
};

struct AstStorageClassSpecifier {
  AstRef storage_class_specifier;
};

struct AstTypeSpecifier {
};

struct AstStructOrUnionSpecifier {
};

struct AstStructOrUnion {
};

struct AstStructDeclarationList {
};

struct AstStructDeclaration {
};

struct AstSpecifierQualifierList {
};

struct AstStructDeclaratorList {
};

struct AstStructDeclarator {
};

struct AstEnumSpecifier {
};

struct AstEnumeratorList {
};

struct AstEnumerator {
};

struct AstTypeQualifier {
};

struct AstDeclarator {
};

struct AstDirectDeclarator {
};

struct AstPointer {
};

struct AstTypeQualifierList {
};

struct AstParameterTypeList {
};

struct AstParameterList {
};

struct AstParameterDeclaration {
};

struct AstIdentifierList {
};

struct AstTypeName {
  AstRef specifier_qualifier_list;
  AstNullableRef abstract_declarator;
};

struct AstAbstractDeclarator {
  AstRef abstract_declarator;
};

struct AstNotPurePointerAbstractDeclarator {
  AstRef pointer;
  AstRef direct_abstract_declarator;
};

struct AstDirectAbstractDeclarator {
  AstRef direct_abstract_declarator;
};

struct AstArrayAbstractDeclarator {
  AstNullableRef direct_abstract_declarator;
  AstNullableRef constant_expression;
};

struct AstFunctionAbstractDeclarator {
  AstNullableRef direct_abstract_declarator;
  AstNullableRef parameter_type_list;
};

struct AstTypedefName {
};

struct AstInitializer {
};

struct AstInitializerList {
};

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

AstRef ast_make_type_name(
    AstRef specifier_qualifier_list, AstNullableRef abstract_declarator) {
  AstRef self = NULL;
  if (ast_is_specifier_qualifier_list(specifier_qualifier_list) &&
      ast_is_abstract_declarator(abstract_declarator)) {
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
      ast_is_not_pure_pointer_abstract_declarator(abstract_declarator)) {
    AstAbstractDeclaratorRef data = ast_palloc(struct AstAbstractDeclarator);
    data->abstract_declarator = abstract_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_ABSTRACT_DECLARATOR;
    self->data.abstract_declarator = data;
  }
  return self;
}

AstRef ast_make_not_pure_pointer_abstract_declarator(
    AstRef pointer, AstRef direct_abstract_declarator) {
  AstRef self = NULL;
  if ((pointer == NULL || ast_is_pointer(pointer)) &&
      ast_is_direct_abstract_declarator(direct_abstract_declarator)) {
    AstNotPurePointerAbstractDeclaratorRef data = ast_palloc(struct AstNotPurePointerAbstractDeclarator);
    data->pointer = pointer;
    data->direct_abstract_declarator = direct_abstract_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_NOT_PURE_POINTER_ABSTRACT_DECLARATOR;
    self->data.not_pure_pointer_abstract_declarator = data;
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
    AstRef direct_abstract_declarator, AstRef parameter_type_list) {
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
