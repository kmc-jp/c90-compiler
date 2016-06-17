#include "code_generator/symbol_table.h"
#include "code_generator/symbol_table_impl.h"
#include "utility.h"

DEFINE_VECTOR(SymbolInfoRef)
DEFINE_VECTOR(SymbolBlockRef)

static SymbolTableRef g_symbol_table;
static const char g_separator = '$';

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

SymbolBlockRef symbol_block_ctor(StringRef name) {
  const SymbolBlockRef block = safe_malloc(struct SymbolBlock);
  const StringRef block_name = string_ctor(string_data(name), NULL);
  block->name = block_name;
  block->symbols = VECTORFUNC(SymbolInfoRef, ctor)(NULL);
  return block;
}

void symbol_block_dtor(SymbolBlockRef* pself) {
  assert(pself);
  string_dtor(&(*pself)->name);
  {
    const VECTORREF(SymbolInfoRef) vector = (*pself)->symbols;
    SymbolInfoRef* iter = VECTORFUNC(SymbolInfoRef, begin)(vector);
    const SymbolInfoRef* const end = VECTORFUNC(SymbolInfoRef, end)(vector);
    for (; iter != end; ++iter) {
      SymbolInfoRef* const tmp = iter;
      symbol_info_dtor(tmp);
    }
    VECTORFUNC(SymbolInfoRef, dtor)(&(*pself)->symbols);
  }
  safe_free(*pself);
}

SymbolTableRef symbol_table_ctor(StringRef name) {
  const SymbolTableRef table = safe_malloc(struct SymbolTable);
  table->module = LLVMModuleCreateWithName(string_data(name));
  table->builder = LLVMCreateBuilder();
  table->prefix = string_ctor("", NULL);
  table->stack = VECTORFUNC(SymbolBlockRef, ctor)(NULL);
  return table;
}

void symbol_table_dtor(SymbolTableRef* pself) {
  assert(pself);
  LLVMDisposeModule((*pself)->module);
  LLVMDisposeBuilder((*pself)->builder);
  string_dtor(&(*pself)->prefix);
  {
    const VECTORREF(SymbolBlockRef) vector = (*pself)->stack;
    SymbolBlockRef* iter = VECTORFUNC(SymbolBlockRef, begin)(vector);
    const SymbolBlockRef* const end = VECTORFUNC(SymbolBlockRef, end)(vector);
    for (; iter != end; ++iter) {
      SymbolBlockRef* const tmp = iter;
      symbol_block_dtor(tmp);
    }
    VECTORFUNC(SymbolBlockRef, dtor)(&(*pself)->stack);
  }
  safe_free(*pself);
}

void initialize_symbol_table(StringRef name) {
  assert(!g_symbol_table);
  g_symbol_table = symbol_table_ctor(name);
}

void finalize_symbol_table(void) {
  assert(g_symbol_table);
  symbol_table_dtor(&g_symbol_table);
}

void symbol_table_push(StringRef name) {
  const SymbolBlockRef block = symbol_block_ctor(name);
  VECTORFUNC(SymbolBlockRef, push_back)(g_symbol_table->stack, block);
  string_push_back(g_symbol_table->prefix, g_separator);
  string_append(g_symbol_table->prefix, name);
}

void symbol_table_pop(void) {
  assert(!string_empty(g_symbol_table->prefix));
  assert(!VECTORFUNC(SymbolBlockRef, empty)(g_symbol_table->stack));
  {
    SymbolBlockRef block =
        VECTORFUNC(SymbolBlockRef, back)(g_symbol_table->stack);
    symbol_block_dtor(&block);
    VECTORFUNC(SymbolBlockRef, pop_back)(g_symbol_table->stack);
  }
  {
    const size_t length = string_length(g_symbol_table->prefix);
    size_t i = length - 1;
    for (; 0 < i; --i) {
      if (string_at(g_symbol_table->prefix, i) == g_separator) {
        break;
      }
    }
    string_erase(g_symbol_table->prefix, i, length - i);
  }
}

void register_symbol(StringRef name, LLVMTypeRef type, LLVMValueRef value) {
  const SymbolInfoRef symbol = symbol_info_ctor(name, type, value);
  const SymbolBlockRef block =
      VECTORFUNC(SymbolBlockRef, back)(g_symbol_table->stack);
  VECTORFUNC(SymbolInfoRef, push_back)(block->symbols, symbol);
}
