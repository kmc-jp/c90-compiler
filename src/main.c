#include <llvm-c/Core.h>

int main(int argc, char *argv[]) {
  LLVMModuleRef module = LLVMModuleCreateWithName("kmc89_module");
  LLVMDisposeModule(module);
  return 0;
}
