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
  AstRef type_specifier;
};

struct AstStructOrUnionSpecifier {
  AstRef struct_or_union;
  AstRef identifier;
  AstRef struct_declaration_list;
};

struct AstStructOrUnionDefinition {
};

struct AstStructOrUnionDeclaration {
  AstRef struct_or_union;
  AstRef identifier;
};

struct AstStructOrUnion {
  AstRef struct_or_union;
};

struct AstStructDeclarationList {
  AstVectorRef struct_declaration_vector;
};

struct AstStructDeclaration {
  AstRef specifier_qualifier_list;
  AstRef struct_declarator_list;
};

struct AstSpecifierQualifierList {
  AstRef specifier_qualifier;
  AstRef specifier_qualifier_list; /* NULLABLE */
};

struct AstSpecifierQualifier {
};

struct AstStructDeclaratorList {
};

struct AstStructDeclarator {
};

struct AstBitFieldDeclarator {
};

struct AstEnumSpecifier {
};

struct AstEnumDefinition {
};

struct AstEnumDeclaration {
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

AstRef ast_make_struct_or_union_definition(AstRef struct_or_union,
    AstRef identifier, AstRef struct_declaration_list) {
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

AstRef ast_make_struct_or_union_declaration(AstRef struct_or_union,
    AstRef identifier) {
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

AstRef ast_make_struct_declaration_list(AstRef struct_declaration_list,
    AstRef struct_declaration) {
  AstRef self = NULL;
  if (struct_declaration_list == NULL) {
    AstStructDeclarationListRef data = ast_palloc(struct AstStructDeclarationList);
    data->struct_declaration_vector = ast_make_vector();
    struct_declaration_list = ast_palloc(struct Ast);
    struct_declaration_list->tag = AST_STRUCT_DECLARATION_LIST;
    struct_declaration_list->data.struct_declaration_list = data;
  }
  if (ast_is_struct_declaration_list(struct_declaration_list) &&
      ast_is_struct_declaration(struct_declaration)) {
    AstStructDeclarationListRef data = ast_get_struct_declaration_list(struct_declaration_list);
    ast_push_vector(data->struct_declaration_vector, struct_declaration);
    self = struct_declaration_list;
  }
  return self;
}

AstRef ast_make_struct_declaration(AstRef specifier_qualifier_list,
    AstRef struct_declarator_list) {
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

AstRef ast_make_specifier_qualifier_list(AstRef specifier_qualifier,
    AstRef specifier_qualifier_list) {
  AstRef self = NULL;
  if (ast_is_specifier_qualifier(specifier_qualifier) &&
      (specifier_qualifier_list == NULL ||
       ast_is_specifier_qualifier_list(specifier_qualifier_list))) {
    AstSpecifierQualifierListRef data = ast_palloc(struct AstSpecifierQualifierList);
    data->specifier_qualifier = specifier_qualifier;
    data->specifier_qualifier_list = specifier_qualifier_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_SPECIFIER_QUALIFIER_LIST;
    self->data.specifier_qualifier_list = data;
  }
  return self;
}
