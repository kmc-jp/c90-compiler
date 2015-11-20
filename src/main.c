#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include <llvm-c/Core.h>
#include "parser.tab.h"
#include "utility.h"

LLVMTypeRef function_type(const struct AstFunctionDefinition* definition) {
  const LLVMTypeRef return_type = definition->type.llvm;
  const ASTVEC param_list = definition->parameter_list;
  const unsigned param_count = (unsigned)ASTFUNC(size)(param_list);
  if (param_count == 0 ||
      (param_count == 1 &&
       ASTFUNC(data)(param_list)->ast.declaration.specifier.tag ==
       AST_TYPE_VOID)) {
    return LLVMFunctionType(return_type, NULL, 0, false);
  } else {
    LLVMTypeRef* const param_type_list =
        safe_array_malloc(LLVMTypeRef, param_count);
    const AST* iter = ASTFUNC(begin)(param_list);
    unsigned i = 0;
    for (i = 0; i < param_count; ++i, ++iter) {
      assert(iter->tag == AST_DECLARATION);
      param_type_list[i] = iter->ast.declaration.specifier.llvm;
    }
    return LLVMFunctionType(return_type, param_type_list, param_count, false);
  }
}

void build_function_definition(LLVMModuleRef module, LLVMBuilderRef builder,
                               const struct AstFunctionDefinition* definition) {
  LLVMTypeRef type = function_type(definition);
  const char* const name = definition->identifier.symbol;
  LLVMValueRef func = LLVMAddFunction(module, name, type);
  LLVMBasicBlockRef entry = LLVMAppendBasicBlock(func, "entry");
  LLVMPositionBuilderAtEnd(builder, entry);
  LLVMBuildRetVoid(builder);
}

int main(int argc, char *argv[]) {
  LLVMModuleRef module = LLVMModuleCreateWithName("kmc89_module");
  LLVMBuilderRef builder = LLVMCreateBuilder();
  AST ast = parse(argv[1]);
  AST* iter = NULL;
  int i = 0;
  assert(ast.tag == AST_TRANSLATION_UNIT);
  for (iter = ASTFUNC(begin)(ast.ast.vec);
       iter != ASTFUNC(end)(ast.ast.vec); ++iter) {
    ++i;
    assert(iter->tag == AST_FUNCTION_DEFINITION);
    build_function_definition(module, builder, &iter->ast.function_definition);
  }
  {
    char *error = NULL;
    LLVMVerifyModule(module, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage(error);
  }
  if (LLVMWriteBitcodeToFile(module, "main.bc") != 0) {
    fputs("failed to write bitcode to file", stderr);
  }
  LLVMDisposeBuilder(builder);
  LLVMDisposeModule(module);
  return 0;
  UNUSED(argc);
}
