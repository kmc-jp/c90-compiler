# c89-compiler/tests/vector_test/Makefile

TOP_DIR := ../..
SRC_DIR := $(TOP_DIR)/src
TESTS_DIR := $(TOP_DIR)/tests
GTEST_DIR := $(TESTS_DIR)/gtest

include $(TOP_DIR)/Makefile.common
include $(GTEST_DIR)/Makefile.common
include $(TESTS_DIR)/Makefile.common

VECTOR_SRCS := utility.c allocator.c
VECTOR_OBJS := $(VECTOR_SRCS:%.c=$(SRC_DIR)/%.o)
TARGET := vector_test.out
OBJS += $(VECTOR_OBJS)

unit_test: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TARGET): $(GTEST_TARGET)

$(GTEST_TARGET):
	$(MAKE) -C $(GTEST_DIR) $(GTEST_LIB)

$(VECTOR_OBJS): $(SRC_DIR)/%:
	$(MAKE) -C $(SRC_DIR) $*

do_test: $(TARGET)
	./$(TARGET)

.PHONY: unit_test do_test
