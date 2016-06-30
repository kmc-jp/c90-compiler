# c90-compiler/src/Makefile

TOP_DIR := ..
SRC_DIR := .

include $(TOP_DIR)/Makefile.common
include $(SRC_DIR)/Makefile.common

AST_DIR := ast
AST_SRCS := $(wildcard $(AST_DIR)/*.c)
AST_OBJS := $(AST_SRCS:.c=.o)

CODEGEN_DIR := code_generator
CODEGEN_SRCS := $(wildcard $(CODEGEN_DIR)/*c)
CODEGEN_OBJS := $(CODEGEN_SRCS:.c=.o)

LEX_SRC := lexer.l
LEX_INTERMEDIATE := lex.yy.c
LEX_TARGET := lex.yy.o
YACC_SRC := parser.y
YACC_INTERMEDIATE := parser.tab.c parser.tab.h
YACC_TARGET := parser.tab.o

LEX := flex
LEX_OPTION :=
YACC := bison
YACC_OPTION := --debug -d
TARGET := kmc90
OBJS += $(AST_OBJS)
OBJS += $(CODEGEN_OBJS)
OBJS += $(LEX_TARGET) $(YACC_TARGET)
CLEAN_OBJS += $(LEX_INTERMEDIATE) $(YACC_INTERMEDIATE)

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(YACC_INTERMEDIATE): $(YACC_SRC)
	$(YACC) $(YACC_OPTION) $<

$(LEX_INTERMEDIATE): $(LEX_SRC) $(YACC_INTERMEDIATE)
	$(LEX) $(LEX_OPTION) $<

$(LEX_TARGET): CFLAGS += -Wno-unused-function

.PHONY: build

main.c: $(YACC_INTERMEDIATE)
