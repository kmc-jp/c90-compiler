#include "code_generator.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

void build_block(LLVMModuleRef module, LLVMBuilderRef builder, AstRef ast) {
  switch (ast->tag) {
    case AST_COMPOUND_STATEMENT:
    default:
  }
}
