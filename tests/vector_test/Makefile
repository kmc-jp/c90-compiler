# c89-compiler/tests/vector_test/Makefile

TOP_DIR := ../..
SRC_DIR := $(TOP_DIR)/src
TESTS_DIR := $(TOP_DIR)/tests
GTEST_DIR := $(TESTS_DIR)/gtest

GTEST_LIB := libgtest.a
UTILITY_OBJ := utility.o
GTEST_TARGET := $(GTEST_DIR)/$(GTEST_LIB)
UTILITY_TARGET := $(SRC_DIR)/$(UTILITY_OBJ)

C_SRCS := $(wildcard *.c)
CXX_SRCS := $(wildcard *.cpp)
C_OBJS := $(C_SRCS:.c=.o)
CXX_OBJS := $(CXX_SRCS:.cpp=.o)
OBJS := $(C_OBJS) $(CXX_OBJS)
TARGET := vector_test.out
INCLUDE := -I$(TESTS_DIR) -I$(SRC_DIR)

include $(TOP_DIR)/Makefile.in

CFLAGS += $(INCLUDE)
CXXFLAGS += $(INCLUDE)
LDFLAGS += -L$(GTEST_DIR)
LIBS += -lgtest -lpthread

unit_test: $(TARGET)

$(TARGET): $(OBJS) $(UTILITY_TARGET)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o $@

$(TARGET): $(GTEST_TARGET)

$(GTEST_TARGET):
	$(MAKE) -C $(GTEST_DIR) $(GTEST_LIB)

$(UTILITY_TARGET):
	$(MAKE) -C $(SRC_DIR) $(UTILITY_OBJ)

.PHONY: unit_test
