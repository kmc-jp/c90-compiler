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
  /* int main() { return 0; } */
  LLVMTypeRef main_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, false);
  LLVMValueRef main_func = LLVMAddFunction(module, "main", main_type);
  LLVMBasicBlockRef main_entry = LLVMAppendBasicBlock(main_func, "main_entry");
  LLVMValueRef return_value = LLVMConstInt(LLVMInt32Type(), 0, false);
  LLVMBuilderRef builder = LLVMCreateBuilder();
  LLVMPositionBuilderAtEnd(builder, main_entry);
  LLVMBuildRet(builder, return_value);
  {
    char *error = NULL;
    LLVMVerifyModule(module, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage(error);
  }
  if (LLVMWriteBitcodeToFile(module, "main.bc") != 0) {
    fputs("failed to write bitcode to file\n", stderr);
  }
  LLVMDisposeBuilder(builder);
  LLVMDisposeModule(module);
  return 0;
  UNUSED(argc);
  UNUSED(argv);
}
