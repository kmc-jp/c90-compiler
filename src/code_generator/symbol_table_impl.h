#ifndef KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_IMPL_H
#define KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_IMPL_H

#include <llvm-c/Core.h>
#include "stdstring.h"
#include "vector.h"

struct SymbolInfo {
  StringRef name;
  LLVMTypeRef type;
  LLVMValueRef value;
};

DECLARE_VECTOR(SymbolInfoRef)

struct SymbolBlock {
  StringRef name;
  VECTORREF(SymbolInfoRef) symbols;
};

DECLARE_VECTOR(SymbolBlockRef)

struct SymbolTable {
  VECTORREF(SymbolBlockRef) stack;
};

#endif  /* KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_IMPL_H */
