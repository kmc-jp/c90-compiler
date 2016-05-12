# c90-compiler/tests/string_test/Makefile

TOP_DIR := ../..
SRC_DIR := $(TOP_DIR)/src
TESTS_DIR := $(TOP_DIR)/tests
GTEST_DIR := $(TESTS_DIR)/gtest

include $(TOP_DIR)/Makefile.common
include $(GTEST_DIR)/Makefile.common
include $(TESTS_DIR)/Makefile.common

STRING_SRCS := utility.c stdstring.c allocator.c
STRING_OBJS := $(STRING_SRCS:%.c=$(SRC_DIR)/%.o)
TARGET = string_test.out
OBJS += $(STRING_OBJS)

unit_test: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TARGET): $(GTEST_TARGET)

$(GTEST_TARGET):
	$(MAKE) -C $(GTEST_DIR) $(GTEST_LIB)

$(STRING_OBJS): $(SRC_DIR)/%:
	$(MAKE) -C $(SRC_DIR) $*

do_test: $(TARGET)
	./$(TARGET)

.PHONY: unit_test do_test
