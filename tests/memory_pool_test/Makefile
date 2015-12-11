# c89-compiler/tests/memory_pool_test/Makefile

TOP_DIR := ../..
SRC_DIR := $(TOP_DIR)/src
TESTS_DIR := $(TOP_DIR)/tests
GTEST_DIR := $(TESTS_DIR)/gtest

include $(TOP_DIR)/Makefile.common
include $(GTEST_DIR)/Makefile.common
include $(TESTS_DIR)/Makefile.common

UTILITY_OBJ := utility.o
UTILITY_TARGET := $(SRC_DIR)/$(UTILITY_OBJ)
MEMORY_POOL_OBJ := memory_pool.o
MEMORY_POOL_TARGET := $(SRC_DIR)/$(MEMORY_POOL_OBJ)

TARGET := memory_pool_test.out
OBJS += $(UTILITY_TARGET) $(MEMORY_POOL_TARGET)

unit_test: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TARGET): $(GTEST_TARGET)

$(GTEST_TARGET):
	$(MAKE) -C $(GTEST_DIR) $(GTEST_LIB)

$(UTILITY_TARGET):
	$(MAKE) -C $(SRC_DIR) $(UTILITY_OBJ)

$(MEMORY_POOL_TARGET):
	$(MAKE) -C $(SRC_DIR) $(MEMORY_POOL_OBJ)

do_test: $(TARGET)
	./$(TARGET)

.PHONY: unit_test do_test
