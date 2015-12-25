#ifndef KMC_C89_COMPILER_AST_DECLARATIONS_H
#define KMC_C89_COMPILER_AST_DECLARATIONS_H

#include "../ast.h"

AstRef ast_make_declaration(AstRef declaration_specifier_list, AstRef init_declarator_list);
AstRef ast_make_declaration_specifier_list(void);
AstRef ast_push_declaration_specifier_list(AstRef declaration_specifier_list, AstRef declaration_specifier);
AstRef ast_make_declaration_specifier(AstRef declaration_specifier);
AstRef ast_make_init_declarator_list(void);
AstRef ast_push_init_declarator_list(AstRef init_declarator_list, AstRef init_declarator);
AstRef ast_make_init_declarator(AstRef init_declarator);
AstRef ast_make_declarator_with_initializer(AstRef declarator, AstRef initializer);
AstRef ast_make_storage_class_specifier();
AstRef ast_make_type_specifier(AstRef type_specifier);
AstRef ast_make_struct_or_union_specifier(AstRef struct_or_union_specifier);
AstRef ast_make_struct_or_union_definition(AstRef struct_or_union, AstRef identifier, AstRef struct_declaration_list);
AstRef ast_make_struct_or_union_declaration(AstRef struct_or_union, AstRef identifier);
AstRef ast_make_struct_or_union(AstRef struct_or_union);
AstRef ast_make_struct_declaration_list(void);
AstRef ast_push_struct_declaration_list(AstRef struct_declaration_list, AstRef struct_declaration);
AstRef ast_make_struct_declaration(AstRef specifier_qualifier_list, AstRef struct_declarator_list);
AstRef ast_make_specifier_qualifier_list(void);
AstRef ast_push_specifier_qualifier_list(AstRef specifier_qualifier, AstRef specifier_qualifier_list);
AstRef ast_make_specifier_qualifier(AstRef specifier_qualifier);
AstRef ast_make_struct_declarator_list(void);
AstRef ast_push_struct_declarator_list(AstRef struct_declarator_list, AstRef struct_declarator);
AstRef ast_make_struct_declarator(AstRef struct_declarator);
AstRef ast_make_bit_field_declarator(AstNullableRef declarator, AstRef bit_field_declarator);
AstRef ast_make_enum_specifier(AstRef enum_specifier);
AstRef ast_make_enum_definition(AstNullableRef identifier, AstRef enumerator_list);
AstRef ast_make_enum_declaration(AstRef identifier);
AstRef ast_make_enumerator_list(void);
AstRef ast_push_enumerator_list(AstRef enumerator_list, AstRef enumerator);
AstRef ast_make_enumerator(AstRef enumeration_constant, AstNullableRef constant_expression);
AstRef ast_make_type_qualifier();
AstRef ast_make_declarator();
AstRef ast_make_direct_declarator();
AstRef ast_make_pointer();
AstRef ast_make_type_qualifier_list();
AstRef ast_make_parameter_type_list();
AstRef ast_make_parameter_list();
AstRef ast_make_parameter_declaration();
AstRef ast_make_identifier_list();
AstRef ast_make_type_name();
AstRef ast_make_abstract_declarator();
AstRef ast_make_direct_abstract_declarator();
AstRef ast_make_typedef_name();
AstRef ast_make_initializer();
AstRef ast_make_initializer_list();

#endif  /* KMC_C89_COMPILER_AST_DECLARATIONS_H */
