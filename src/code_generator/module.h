#ifndef KMC_C90_COMPILER_CODE_GENERATOR_MODULE_H
#define KMC_C90_COMPILER_CODE_GENERATOR_MODULE_H

void module_ctor(const char* module_name);
void module_dtor(void);
LLVMModuleRef get_module(void);

void builder_ctor(void);
void builder_dtor(void);
LLVMBuilderRef get_builder(void);

#endif  /* KMC_C90_COMPILER_CODE_GENERATOR_MODULE_H */
