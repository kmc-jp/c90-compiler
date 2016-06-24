#ifndef KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_H
#define KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_H

typedef struct SymbolInfo* SymbolInfoRef;
typedef struct SymbolBlock* SymbolBlockRef;
typedef struct SymbolTable* SymbolTableRef;

void initialize_symbol_table(void);
void finalize_symbol_table(void);

#endif  /* KMC_C90_COMPILER_CODE_GENERATOR_SYMBOL_TABLE_H */
