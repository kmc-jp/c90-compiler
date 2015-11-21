#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include <llvm-c/Core.h>
#include "parser.tab.h"
#include "utility.h"

LLVMTypeRef function_type(const struct AstFunctionDefinition* definition) {
  const LLVMTypeRef return_type = definition->type.llvm;
  const ASTVEC param_list = definition->parameter_list;
  const unsigned param_count = (unsigned)ASTFUNC(size)(param_list);
  if (param_count == 0 ||
      (param_count == 1 &&
       ASTFUNC(data)(param_list)->ast.declaration.specifier.tag ==
       AST_TYPE_VOID)) {
    return LLVMFunctionType(return_type, NULL, 0, false);
  } else {
    LLVMTypeRef* const param_type_list =
        safe_array_malloc(LLVMTypeRef, param_count);
    const AST* iter = ASTFUNC(begin)(param_list);
    unsigned i = 0;
    for (i = 0; i < param_count; ++i, ++iter) {
      assert(iter->tag == AST_DECLARATION);
      param_type_list[i] = iter->ast.declaration.specifier.llvm;
    }
    return LLVMFunctionType(return_type, param_type_list, param_count, false);
  }
}

LLVMValueRef build_expression(LLVMModuleRef module, LLVMBuilderRef builder,
                              const AST* expression) {
  switch (expression->tag) {
    case AST_NULL_EXPRESSION:
      return NULL;
    case AST_FUNCTION_CALL:
      {
        char* identifier = expression->ast.function_call.identifier.symbol;
        LLVMValueRef function = LLVMGetNamedFunction(module, identifier);
        ASTVEC argument_list = expression->ast.function_call.argument_list;
        const AST* const begin = ASTFUNC(begin)(argument_list);
        const unsigned argument_count = ASTFUNC(size)(argument_list);
        LLVMValueRef* arguments = NULL;
        unsigned param_count = 0;
        LLVMTypeRef function_type = NULL;
        unsigned i = 0;
        if (function == NULL) {
          fprintf(stderr, "unknown function name\n");
        }
        if (argument_count == 0) {
          return LLVMBuildCall(builder, function, NULL, 0, identifier);
        }
        function_type = LLVMGetElementType(LLVMTypeOf(function));
        param_count = LLVMCountParamTypes(function_type);
        if (argument_count != param_count) {
          fprintf(stderr, "count of parameter differ: %d != %d\n",
                  argument_count, param_count);
        }
        arguments = safe_array_malloc(LLVMValueRef, argument_count);
        for (i = 0; i < argument_count; ++i) {
          arguments[i] = build_expression(module, builder, begin + i);
        }
        if (LLVMGetTypeKind(LLVMGetReturnType(function_type)) ==
            LLVMVoidTypeKind) {
          identifier = "";
        }
        return LLVMBuildCall(builder, function, arguments,
                             argument_count, identifier);
      }
      break;
    case AST_IDENTIFIER:
      fprintf(stderr, "%d: Not supported\n", expression->tag);
      return NULL;
      break;
    case AST_STRING_LITERAL:
      {
        char* string = expression->ast.string_literal.string;
        return LLVMConstString(string, strlen(string), false);
      }
    case AST_INTEGER_CONSTANT:
      {
        char* integer = expression->ast.integer_constant;
        return LLVMConstIntOfStringAndSize(LLVMInt32Type(),
                                           integer, strlen(integer), 10);
      }
    default:
      fprintf(stderr, "%d: Not supported\n", expression->tag);
      return NULL;
      break;
  }
}

void build_return(LLVMModuleRef module, LLVMBuilderRef builder,
                  const AST* expression) {
  LLVMValueRef value = build_expression(module, builder, expression);
  if (value) {
    LLVMBuildRet(builder, value);
  } else {
    LLVMBuildRetVoid(builder);
  }
}

void build_block(LLVMModuleRef module, LLVMBuilderRef builder,
                 ASTVEC compound_statement) {
  size_t i = 0;
  const AST* const begin = ASTFUNC(begin)(compound_statement);
  const size_t count = ASTFUNC(size)(compound_statement);
  for (i = 0; i < count; ++i) {
    switch (begin[i].tag) {
      case AST_COMPOUND_STATEMENT:
        build_block(module, builder, begin[i].ast.vec);
        break;
      case AST_EXPRESSION_STATEMENT: {
        AST* statement = ASTFUNC(data)(begin[i].ast.vec);
        build_expression(module, builder, statement);
      }
        break;
      case AST_RETURN_STATEMENT: {
        AST* statement = ASTFUNC(data)(begin[i].ast.vec);
        build_return(module, builder, statement);
      }
        break;
      default:
        fprintf(stderr, "%d: Not supported\n", begin[i].tag);
        break;
    }
  }
}

void build_function_definition(LLVMModuleRef module, LLVMBuilderRef builder,
                               const struct AstFunctionDefinition* definition) {
  LLVMTypeRef type = function_type(definition);
  const char* const name = definition->identifier.symbol;
  LLVMValueRef func = LLVMAddFunction(module, name, type);
  LLVMBasicBlockRef entry = LLVMAppendBasicBlock(func, "entry");
  LLVMPositionBuilderAtEnd(builder, entry);
  build_block(module, builder, definition->compound_statement);
}

void add_print_declaration(LLVMModuleRef module) {
  LLVMTypeRef void_type = LLVMVoidType();
  LLVMTypeRef char_type = LLVMInt8Type();
  LLVMTypeRef int_type = LLVMInt32Type();
  LLVMTypeRef char_ptr_type = LLVMPointerType(char_type, 0);
  LLVMTypeRef print_type =
      LLVMFunctionType(void_type, &char_ptr_type, 1, false);
  LLVMTypeRef print_num_type =
      LLVMFunctionType(void_type, &int_type, 1, false);
  LLVMAddFunction(module, "print", print_type);
  LLVMAddFunction(module, "print_num", print_num_type);
}

int main(int argc, char *argv[]) {
  LLVMModuleRef module = LLVMModuleCreateWithName("kmc89_module");
  LLVMBuilderRef builder = LLVMCreateBuilder();
  const size_t name_len = strlen(argv[1]);
  char* bc_name = NULL;
  const size_t bc_len = name_len + 2;
  AST ast = parse(argv[1]);
  AST* iter = NULL;
  int i = 0;
  assert(ast.tag == AST_TRANSLATION_UNIT);
  add_print_declaration(module);
  for (iter = ASTFUNC(begin)(ast.ast.vec);
       iter != ASTFUNC(end)(ast.ast.vec); ++iter) {
    ++i;
    switch (iter->tag) {
      case AST_FUNCTION_DEFINITION:
        build_function_definition(module, builder,
                                  &iter->ast.function_definition);
        break;
      default:
        assert(false);
        break;
    }
  }
  {
    char *error = NULL;
    LLVMVerifyModule(module, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage(error);
  }
  bc_name = safe_array_malloc(char, bc_len);
  strncpy(bc_name, argv[1], bc_len);
  bc_name[bc_len - 3] = 'b';
  bc_name[bc_len - 2] = 'c';
  if (LLVMWriteBitcodeToFile(module, bc_name) != 0) {
    fputs("failed to write bitcode to file", stderr);
  }
  LLVMDisposeBuilder(builder);
  LLVMDisposeModule(module);
  return 0;
  UNUSED(argc);
}
