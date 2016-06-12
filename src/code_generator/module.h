#ifndef KMC_C90_COMPILER_CODE_GENERATOR_MODULE_H
#define KMC_C90_COMPILER_CODE_GENERATOR_MODULE_H

void module_ctor(const char* module_name);
void module_dtor(void);
LLVMModuleRef get_module(void);

#endif  /* KMC_C90_COMPILER_CODE_GENERATOR_MODULE_H */
