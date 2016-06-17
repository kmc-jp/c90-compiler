#ifndef KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_H
#define KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_H

#include <llvm-c/Core.h>
#include "stdstring.h"

typedef struct SymbolInfo* SymbolInfoRef;
typedef struct SymbolBlock* SymbolBlockRef;
typedef struct SymbolTable* SymbolTableRef;

void initialize_symbol_table(StringRef name);
void finalize_symbol_table(void);
void symbol_table_push(StringRef name);
void symbol_table_pop(void);
void register_symbol(StringRef name, LLVMTypeRef type, LLVMValueRef value);
void append_prefix(StringRef name);
SymbolInfoRef find_symbol(StringRef name);

#endif  /* KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_H */
