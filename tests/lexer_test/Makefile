# c90-compiler/tests/lexer_test/Makefile

TOP_DIR := ../..
SRC_DIR := $(TOP_DIR)/src
TESTS_DIR := $(TOP_DIR)/tests
GTEST_DIR := $(TESTS_DIR)/gtest

include $(TOP_DIR)/Makefile.common
include $(GTEST_DIR)/Makefile.common
include $(TESTS_DIR)/Makefile.common

LEX_SRCS := lex.yy.c utility.c parser.tab.c allocator.c memory_pool.c stdstring.c sexpr.c sexpr_pool.c use_vector.c
LEX_OBJS := $(LEX_SRCS:%.c=$(SRC_DIR)/%.o)
TARGET := lexer_test.out

AST_DIR := $(SRC_DIR)/ast
AST_SRCS := $(wildcard $(AST_DIR)/*.c)
AST_OBJS := $(AST_SRCS:.c=.o)
LEX_SRCS += $(AST_SRCS)
LEX_OBJS += $(AST_OBJS)

CLEAN_OBJS += $(LEX_OBJS)

unit_test: $(TARGET)

$(TARGET): $(OBJS) $(LEX_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TARGET): $(GTEST_TARGET)

$(OBJS): $(LEX_OBJS)

$(GTEST_TARGET):
	$(MAKE) -C $(GTEST_DIR) $(GTEST_LIB)

$(LEX_OBJS): $(SRC_DIR)/%:
	$(MAKE) -C $(SRC_DIR) $*

do_test: $(TARGET)
	./$(TARGET)

.PHONY: unit_test do_test
