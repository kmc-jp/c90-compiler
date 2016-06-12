#include "code_generator/module.h"
#include <assert.h>
#include <stddef.h>

static LLVMModuleRef g_module = NULL;
static LLVMBuilderRef g_builder = NULL;

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

void builder_ctor(void) {
  assert(!g_builder);
  g_builder = LLVMCreateBuilder();
}

void builder_dtor(void) {
  assert(g_module);
  LLVMDisposeBuilder(g_builder);
  g_builder = NULL;
}

LLVMBuilderRef get_builder(void) {
  assert(g_module);
  return g_builder;
}
