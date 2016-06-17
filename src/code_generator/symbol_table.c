#include "code_generator/symbol_table.h"
#include "code_generator/symbol_table_impl.h"
#include "stdstring.h"
#include "utility.h"

DEFINE_VECTOR(SymbolInfoRef)
DEFINE_VECTOR(SymbolBlockRef)

SymbolInfoRef symbol_info_ctor(StringRef name, LLVMTypeRef type,
                               LLVMValueRef value) {
  const SymbolInfoRef symbol = safe_malloc(struct SymbolInfo);
  const StringRef symbol_name = string_ctor(string_data(name), NULL);
  symbol->name = symbol_name;
  symbol->type = type;
  symbol->value = value;
  return symbol;
}

void symbol_info_dtor(SymbolInfoRef* pself) {
  assert(pself);
  string_dtor(&(*pself)->name);
  safe_free(*pself);
}
