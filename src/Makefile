# c89-compiler/src/Makefile

TOP_DIR := ..
SRC_DIR := .

include $(TOP_DIR)/Makefile.common
include $(SRC_DIR)/Makefile.common

LEX_SRC := lexer.l
LEX_INTERMEDIATE := lex.yy.c lex.yy.h
LEX_TARGET := lex.yy.o
YACC_SRC := parser.y
YACC_INTERMEDIATE := parser.tab.c parser.tab.h
YACC_TARGET := parser.tab.o

LEX := flex
LEX_OPTION := --header-file=$(filter %.h,$(LEX_INTERMEDIATE))
YACC := bison
YACC_OPTION := -d
TARGET := kmc89
OBJS += $(LEX_TARGET) $(YACC_TARGET)
CLEAN_OBJS += $(LEX_INTERMEDIATE) $(YACC_INTERMEDIATE)

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(LEX_INTERMEDIATE): $(LEX_SRC) $(YACC_INTERMEDIATE)
	$(LEX) $(LEX_OPTION) $<

$(LEX_TARGET): CFLAGS += -Wno-unused-function

$(YACC_INTERMEDIATE): $(YACC_SRC)
	$(YACC) $(YACC_OPTION) $<

# for now
$(YACC_INTERMEDIATE): YACC_OPTION += -Wno-other

main.o: CFLAGS += -Wno-long-long

.PHONY: build
