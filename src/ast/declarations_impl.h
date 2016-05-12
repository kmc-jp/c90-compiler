#ifndef KMC_C90_COMPILER_AST_DECLARATIONS_IMPL_H
#define KMC_C90_COMPILER_AST_DECLARATIONS_IMPL_H

#include "ast.h"

struct AstDeclaration {
  AstRef declaration_specifier_list;
  AstRef init_declarator_list;
};

struct AstDeclarationSpecifierList {
  AstVectorRef declaration_specifier_vector;
};

struct AstDeclarationSpecifier {
  AstRef declaration_specifier;
};

struct AstInitDeclaratorList {
  AstVectorRef init_declarator_vector;
};

struct AstInitDeclarator {
  AstRef init_declarator;
};

struct AstDeclaratorWithInitializer {
  AstRef declarator;
  AstRef initializer;
};

struct AstStorageClassSpecifier {
  AstRef storage_class_specifier;
};

struct AstTypeSpecifier {
  AstRef type_specifier;
};

struct AstStructOrUnionSpecifier {
  AstRef struct_or_union_specifier;
};

struct AstStructOrUnionDefinition {
  AstRef struct_or_union;
  AstNullableRef identifier;
  AstRef struct_declaration_list;
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
  AstVectorRef specifier_qualifier_vector;
};

struct AstSpecifierQualifier {
  AstRef specifier_qualifier;
};

struct AstStructDeclaratorList {
  AstVectorRef struct_declarator_vector;
};

struct AstStructDeclarator {
  AstRef struct_declarator;
};

struct AstBitFieldDeclarator {
  AstNullableRef declarator;
  AstRef constant_expression;
};

struct AstEnumSpecifier {
  AstRef enum_specifier;
};

struct AstEnumDefinition {
  AstNullableRef identifier;
  AstRef enumerator_list;
};

struct AstEnumDeclaration {
  AstRef identifier;
};

struct AstEnumeratorList {
  AstVectorRef enumerator_vector;
};

struct AstEnumerator {
  AstRef enumerator;
};

struct AstEnumeratorWithInitializer {
  AstRef enumeration_constant;
  AstRef constant_expression;
};

struct AstTypeQualifier {
  AstRef type_qualifier;
};

struct AstDeclarator {
  AstNullableRef pointer;
  AstRef direct_declarator;
};

struct AstDirectDeclarator {
  AstRef direct_declarator;
};

struct AstArrayDeclarator {
  AstRef direct_declarator;
  AstNullableRef constant_expression;
};

struct AstFunctionDeclarator {
  AstRef direct_declarator;
  AstRef parameter_type_list;
};

struct AstOldStyleFunctionDeclarator {
  AstRef direct_declarator;
  AstNullableRef identifier_list;
};

struct AstPointer {
  AstNullableRef type_qualifier_list;
  AstNullableRef pointer;
};

struct AstTypeQualifierList {
  AstVectorRef type_qualifier_vector;
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
  AstRef parameter_declaration;
};

struct AstParameterConcreteDeclaration {
  AstRef declaration_specifier_list;
  AstRef declarator;
};

struct AstParameterAbstractDeclaration {
  AstRef declaration_specifier_list;
  AstNullableRef abstract_declarator;
};

struct AstIdentifierList {
  AstVectorRef identifier_vector;
};

struct AstTypeName {
  AstRef specifier_qualifier_list;
  AstNullableRef abstract_declarator;
};

struct AstAbstractDeclarator {
  AstRef abstract_declarator;
};

struct AstPointerAbstractDeclarator {
  AstNullableRef pointer;
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
  AstRef identifier;
};

struct AstInitializer {
  AstRef initializer;
};

struct AstInitializerList {
  AstVectorRef initializer_vector;
};

#endif  /* KMC_C90_COMPILER_AST_DECLARATIONS_IMPL_H */
