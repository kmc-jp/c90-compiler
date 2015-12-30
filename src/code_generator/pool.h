#ifndef KMC_C89_COMPILER_CODE_GENERATOR_POOL_H
#define KMC_C89_COMPILER_CODE_GENERATOR_POOL_H

#include "memory_pool.h"
#include "vector.h"
#include "stdstring.h"
#include "variable_set.h"

#define codegen_palloc(type) \
  palloc(type, codegen_pool(), 1)

static const size_t CODEGEN_POOL_CHUNK_SIZE = 1024;

void codegen_pool_ctor(void);
void codegen_pool_dtor(void);
MemoryPoolRef codegen_pool(void);

#define TypeVectorFunc(func) VECTORFUNC(LLVMTypeRef, func)
DECLARE_VECTOR(LLVMTypeRef)
 
#define ValueVectorFunc(func) VECTORFUNC(LLVMValueRef, func)
DECLARE_VECTOR(LLVMValueRef)

#endif /* KMC_C89_COMPILER_CODE_GENERATOR_POOL_H */
