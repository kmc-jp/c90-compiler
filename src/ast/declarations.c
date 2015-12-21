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
  AstRef pointer; /* NULLABLE */
  AstRef direct_declarator;
};

struct AstDirectDeclarator {
  AstRef direct_declarator;
};

struct AstArrayDeclarator {
  AstRef direct_declarator;
  AstRef constant_expression; /* NULLABLE */
};

struct AstFunctionDeclarator {
  AstRef direct_declarator;
  AstRef parameter_type_list;
};

struct AstOldStyleFunctionDeclarator {
  AstRef direct_declarator;
  AstRef identifier_list; /* NULLABLE */
};

struct AstPointer {
  AstRef type_qualifier_list; /* NULLABLE */
  AstRef pointer; /* NULLABLE */
};

struct AstTypeQualifierList {
  AstRef type_qualifier_list; /* NULLABLE */
  AstRef type_qualifier;
};

struct AstParameterTypeList {
  AstRef parameter_type_list;
};

struct AstVariadicParameterList {
  AstRef parameter_list;
};

struct AstParameterList {
  AstVectorRef parameter_declaration_vector;
};

struct AstParameterDeclaration {
  AstRef declaration_specifier_list;
  AstRef declarator;
};

struct AstParameterAbstractDeclaration {
  AstRef declaration_specifier_list;
  AstRef abstract_declarator; /* NULLABLE */
};

struct AstIdentifierList {
  AstVectorRef identifier_vector;
};

struct AstTypeName {
};

struct AstAbstractDeclarator {
};

struct AstDirectAbstractDeclarator {
};

struct AstTypedefName {
};

struct AstInitializer {
};

struct AstInitializerList {
};

AstRef ast_make_declarator(AstRef pointer, AstRef direct_declarator) {
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
      ast_is_function_declarator(direct_declarator)) {
    AstDirectDeclaratorRef data = ast_palloc(struct AstDirectDeclarator);
    data->direct_declarator = direct_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_DIRECT_DECLARATOR;
    self->data.direct_declarator = data;
  }
  return self;
}

AstRef ast_make_array_declarator(AstRef direct_declarator,
    AstRef constant_expression) {
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

AstRef ast_make_function_declarator(AstRef direct_declarator,
    AstRef parameter_type_list) {
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

AstRef ast_make_old_style_function_declarator(AstRef direct_declarator,
    AstRef identifier_list) {
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

AstRef ast_make_pointer(AstRef type_qualifier_list, AstRef pointer) {
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

AstRef ast_make_type_qualifier_list(AstRef type_qualifier_list,
    AstRef type_qualifier) {
  AstRef self = NULL;
  if ((type_qualifier_list == NULL ||
       ast_is_type_qualifier_list(type_qualifier_list)) &&
      ast_is_type_qualifier(type_qualifier)) {
    AstTypeQualifierListRef data = ast_palloc(struct AstTypeQualifierList);
    data->type_qualifier_list = type_qualifier_list;
    data->type_qualifier = type_qualifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_TYPE_QUALIFIER_LIST;
    self->data.type_qualifier_list = data;
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

AstRef ast_make_variadic_parameter_list(
    AstRef parameter_list) {
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

AstRef ast_make_parameter_list(AstRef parameter_list,
    AstRef parameter_declaration) {
  AstRef self = NULL;
  if (parameter_list == NULL) {
    AstParameterListRef data = ast_palloc(struct AstParameterList);
    data->parameter_declaration_vector = ast_make_vector();
    parameter_list = ast_palloc(struct Ast);
    parameter_list->tag = AST_PARAMETER_LIST;
    parameter_list->data.parameter_list = data;
  }
  if (ast_is_parameter_list(parameter_list) &&
      (ast_is_parameter_declaration(parameter_declaration) ||
       ast_is_parameter_abstract_declaration(parameter_declaration))) {
    AstParameterListRef data = ast_get_parameter_list(parameter_list);
    ast_push_vector(data->parameter_declaration_vector, parameter_declaration);
    self = parameter_list;
  }
  return self;
}

AstRef ast_make_parameter_declaration(AstRef declaration_specifier_list,
    AstRef declarator) {
  AstRef self = NULL;
  if (ast_is_declaration_specifiers(declaration_specifier_list) &&
      ast_is_declarator(declarator)) {
    AstParameterDeclarationRef data = ast_palloc(struct AstParameterDeclaration);
    data->declaration_specifier_list = declaration_specifier_list;
    data->declarator = declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_PARAMETER_DECLARATION;
    self->data.parameter_declaration = data;
  }
  return self;
}

AstRef ast_make_parameter_abstract_declaration(AstRef declaration_specifier_list,
    AstRef abstract_declarator) {
  AstRef self = NULL;
  if (ast_is_declaration_specifiers(declaration_specifier_list) &&
      ast_is_abstract_declarator(abstract_declarator)) {
    AstParameterAbstractDeclarationRef data = ast_palloc(struct AstParameterAbstractDeclaration);
    data->declaration_specifier_list = declaration_specifier_list;
    data->abstract_declarator = abstract_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_PARAMETER_ABSTRACT_DECLARATION;
    self->data.parameter_abstract_declaration = data;
  }
  return self;
}

AstRef ast_make_identifier_list(AstRef identifier_list, AstRef identifier) {
  AstRef self = NULL;
  if (identifier_list == NULL) {
    AstIdentifierListRef data = ast_palloc(struct AstIdentifierList);
    data->identifier_vector = ast_make_vector();
    identifier_list = ast_palloc(struct Ast);
    identifier_list->tag = AST_IDENTIFIER_LIST;
    identifier_list->data.identifier_list = data;
  }
  if (ast_is_identifier_list(identifier_list) &&
      ast_is_identifier(identifier)) {
    AstIdentifierListRef data = ast_get_identifier_list(identifier_list);
    ast_push_vector(data->identifier_vector, identifier);
    self = identifier_list;
  }
  return self;
}
