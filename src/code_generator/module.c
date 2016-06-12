#include "module.h"
#include <assert.h>

static LLVMModuleRef g_module = NULL;

void module_ctor(const char* module_name) {
  assert(!g_module);
  g_module = LLVMModuleCreateWithName(module_name);
}

void module_dtor(void) {
  assert(g_module);
  LLVMDisposeModule(g_module);
  g_module = NULL;
}

LLVMModuleRef get_module(void) {
  assert(g_module);
  return g_module;
}
