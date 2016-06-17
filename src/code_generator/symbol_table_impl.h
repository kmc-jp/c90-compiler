#ifndef KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_IMPL_H
#define KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_IMPL_H

struct SymbolInfo {
  StringRef name;
  LLVMTypeRef type;
  LLVMValueRef value;
};

DECLARE_VECTOR(SymbolInfoRef);

struct SymbolBlock {
  StringRef name;
  VECTORREF(SymbolInfoRef) symbols;
};

#endif  /* KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_IMPL_H */
