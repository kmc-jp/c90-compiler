#ifndef KMC_C89_COMPILER_AST_DECLARATIONS_H
#define KMC_C89_COMPILER_AST_DECLARATIONS_H

#include "../ast.h"

AstRef ast_make_declaration();
AstRef ast_make_declaration_specifiers();
AstRef ast_make_init_declarator_list();
AstRef ast_make_init_declarator();
AstRef ast_make_storage_class_specifier();
AstRef ast_make_type_specifier();
AstRef ast_make_struct_or_union_specifier();
AstRef ast_make_struct_or_union();
AstRef ast_make_struct_declaration_list();
AstRef ast_make_struct_declaration();
AstRef ast_make_specifier_qualifier_list();
AstRef ast_make_struct_declarator_list();
AstRef ast_make_struct_declarator();
AstRef ast_make_enum_specifier();
AstRef ast_make_enumerator_list();
AstRef ast_make_enumerator();
AstRef ast_make_type_qualifier();
AstRef ast_make_declarator(AstRef pointer, AstRef direct_declarator);
AstRef ast_make_direct_declarator(AstRef direct_declarator);
AstRef ast_make_array_declarator(AstRef direct_declarator, AstRef constant_expression);
AstRef ast_make_function_declarator(AstRef direct_declarator, AstRef parameter_type_list);
AstRef ast_make_old_style_function_declarator(AstRef direct_declarator, AstRef identifier_list);
AstRef ast_make_pointer(AstRef type_qualifier_list, AstRef pointer);
AstRef ast_make_type_qualifier_list(AstRef type_qualifier_list, AstRef type_qualifier);
AstRef ast_make_parameter_type_list(AstRef parameter_type_list);
AstRef ast_make_variadic_parameter_list(AstRef parameter_list);
AstRef ast_make_parameter_list(AstRef parameter_list, AstRef parameter_declaration);
AstRef ast_make_parameter_declaration();
AstRef ast_make_parameter_abstract_declaration();
AstRef ast_make_identifier_list();
AstRef ast_make_type_name();
AstRef ast_make_abstract_declarator();
AstRef ast_make_direct_abstract_declarator();
AstRef ast_make_typedef_name();
AstRef ast_make_initializer();
AstRef ast_make_initializer_list();

#endif  /* KMC_C89_COMPILER_AST_DECLARATIONS_H */
