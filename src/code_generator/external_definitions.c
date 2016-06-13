#include "code_generator/external_definitions.h"
#include <assert.h>
#include "ast/external_definitions_impl.h"
#include "ast/get_method.h"
#include "ast/is_method.h"
#include "ast/pool.h"
#include "code_generator/generate.h"
#include "error.h"

void generate_translation_unit(AstTranslationUnitRef translation_unit) {
  assert(translation_unit);
  {
    const AstVectorRef vector = translation_unit->external_declaration_vector;
    const AstRef* const begin = AST_VECTOR_FUNC(begin)(vector);
    const AstRef* const end = AST_VECTOR_FUNC(end)(vector);
    const AstRef* iter = NULL;
    for (iter = begin; iter != end; ++iter) {
      if (ast_is_external_declaration(*iter)) {
        generate_code(*iter);
      } else {
        error("Not translation_unit");
      }
    }
  }
}

void generate_external_declaration(AstExternalDeclarationRef external_declaration) {
  assert(external_declaration);
  {
    const AstRef ast = external_declaration->external_declaration;
    if (ast_is_function_definition(ast) || ast_is_declaration(ast)) {
      generate_code(ast);
    } else {
      error("Not external_declaration");
    }
  }
}

void generate_function_definition(AstFunctionDefinitionRef function_definition) {
  assert(function_definition);
  {
    const AstRef specifiers = function_definition->declaration_specifier_list;
    const AstRef declarator = function_definition->declarator;
    /* Do not support old style function definition */
    const AstRef old_style = function_definition->declaration_list;
    const AstRef body = function_definition->compound_statement;
    if (ast_is_declaration_specifier_list(specifiers) &&
        ast_is_declarator(declarator) &&
        ast_is_declaration_list(old_style) &&
        ast_is_compound_statement(body)) {
      start_function(ast_get_declaration_specifier_list(specifiers),
                     ast_get_declarator(declarator));
      generate_code(body);
      finish_function();
    } else {
      error("Not function_definition");
    }
  }
}
