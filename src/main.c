#include <stdio.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include <llvm-c/Core.h>
#include "utility.h"

int main(int argc, char *argv[]) {
  UNUSED(argc);
  UNUSED(argv);
  LLVMModuleRef module = LLVMModuleCreateWithName("kmc89_module");
  /* int main() { return 0; } */
  LLVMTypeRef main_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, false);
  LLVMValueRef main_func = LLVMAddFunction(module, "main", main_type);
  LLVMBasicBlockRef main_entry = LLVMAppendBasicBlock(main_func, "main_entry");
  LLVMBuilderRef builder = LLVMCreateBuilder();
  LLVMPositionBuilderAtEnd(builder, main_entry);
  LLVMValueRef return_value = LLVMConstInt(LLVMInt32Type(), 0, false);
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
}
