# c89-compiler/src/Makefile

TOP_DIR := ..
SRC_DIR := .

include $(TOP_DIR)/Makefile.common
include $(SRC_DIR)/Makefile.common

LEX := flex
TARGET := kmc89
OBJS += lex.yy.o
CLEAN_OBJS += lex.yy.c lex.yy.h

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

lex.yy.c lex.yy.h: lexer.l
	$(LEX) --header-file=lex.yy.h -o lex.yy.c lexer.l

lex.yy.o: CFLAGS += -Wno-unused-function

main.o: CFLAGS += -Wno-long-long

.PHONY: build
