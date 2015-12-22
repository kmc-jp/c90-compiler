# c89-compiler/src/Makefile

TOP_DIR := ..
SRC_DIR := .

include $(TOP_DIR)/Makefile.common
include $(SRC_DIR)/Makefile.common

AST_DIR := ast
AST_SRCS := $(wildcard $(AST_DIR)/*.c)
AST_OBJS := $(AST_SRCS:.c=.o)

LEX_SRC := lexer.l

LEX := flex
LEX_OPTION := --header-file=lex.yy.h -o lex.yy.c
YACC := bison
TARGET := kmc89
OBJS += $(AST_OBJS)
OBJS += lex.yy.o parser.tab.o
CLEAN_OBJS += lex.yy.c lex.yy.h

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d $<

lex.yy.c lex.yy.h: $(LEX_SRC)
	$(LEX) $(LEX_OPTION) $<

lex.yy.o: CFLAGS += -Wno-unused-function

main.o: CFLAGS += -Wno-long-long

.PHONY: build
