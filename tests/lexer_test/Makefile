# c89-compiler/tests/lexer_test/Makefile

TOP_DIR := ../..
SRC_DIR := $(TOP_DIR)/src
TESTS_DIR := $(TOP_DIR)/tests
GTEST_DIR := $(TESTS_DIR)/gtest

include $(TOP_DIR)/Makefile.common
include $(GTEST_DIR)/Makefile.common
include $(TESTS_DIR)/Makefile.common

LEX_SRCS := lex.yy.c yacc_mock.c use_vector.c utility.c
LEX_OBJS := $(LEX_SRCS:%.c=$(SRC_DIR)/%.o)
TARGET := lexer_test.out
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
