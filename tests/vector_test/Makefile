# c89-compiler/tests/vector_test/Makefile

TOP_DIR := ../..
SRC_DIR := $(TOP_DIR)/src
TESTS_DIR := $(TOP_DIR)/tests
GTEST_DIR := $(TESTS_DIR)/gtest

UTILITY_OBJ := utility.o
UTILITY_TARGET := $(SRC_DIR)/$(UTILITY_OBJ)

C_SRCS := $(wildcard *.c)
CXX_SRCS := $(wildcard *.cpp)
C_OBJS := $(C_SRCS:.c=.o)
CXX_OBJS := $(CXX_SRCS:.cpp=.o)
OBJS := $(C_OBJS) $(CXX_OBJS)
TARGET := vector_test.out

include $(TOP_DIR)/Makefile.common
include $(GTEST_DIR)/Makefile.common
include $(TESTS_DIR)/Makefile.common

unit_test: $(TARGET)

$(TARGET): $(OBJS) $(UTILITY_TARGET)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TARGET): $(GTEST_TARGET)

$(GTEST_TARGET):
	$(MAKE) -C $(GTEST_DIR) $(GTEST_LIB)

$(UTILITY_TARGET):
	$(MAKE) -C $(SRC_DIR) $(UTILITY_OBJ)

do_test: $(TARGET)
	./$(TARGET)

.PHONY: unit_test do_test
