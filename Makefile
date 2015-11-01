CC ?= gcc
CXX ?= g++
CFLAGS ?= -Wall -Wextra -O2
CXXFLAGS ?= -Wall -Wextra -O2

SRC_DIR = src

TARGET = kmc89

TESTSUFFIX = .out
TESTS_DIR = tests
STAGE1_DIR = $(TESTS_DIR)/stage1
STAGE2_DIR = $(TESTS_DIR)/stage2
STAGE1_SRCS = $(wildcard $(STAGE1_DIR)/*.c)
STAGE2_SRCS = $(wildcard $(STAGE2_DIR)/*.c)
STAGE1_OBJS = $(STAGE1_SRCS:.c=$(TESTSUFFIX))
STAGE2_OBJS = $(STAGE2_SRCS:.c=$(TESTSUFFIX))
STAGE1_LIBS_DIR = $(STAGE1_DIR)/lib
STAGE1_LIBS = $(STAGE1_LIBS_DIR)/print.o
STAGE1_LIBS_CFLAGS ?= $(TESTS_CFLAGS)
TESTS_OBJS = $(STAGE1_OBJS) $(STAGE2_OBJS) $(STAGE1_LIBS)
TESTS_CFLAGS ?= -ansi -pedantic $(CFLAGS)

GTEST_DIR = $(TESTS_DIR)/gtest
GTEST_SRCS = $(wildcard $(GTEST_DIR)/*.cc)
GTEST_OBJS = $(GTEST_SRCS:.cc=.o)
GTEST_LIB = libgtest.a
GTEST_FLAGS = -Wno-missing-field-initializers
GTEST_INCLUDE = -I$(TESTS_DIR)
GTEST_LDFLAGS = -lpthread

VECTOR_HEADER = $(SRC_DIR)/vector.h
VECTOR_OBJ = $(SRC_DIR)/vector.o
TEST_VECTOR_DIR = $(TESTS_DIR)/vector_test
TEST_VECTOR_C_SRCS = $(wildcard $(TEST_VECTOR_DIR)/*.c)
TEST_VECTOR_CXX_SRCS = $(wildcard $(TEST_VECTOR_DIR)/*.cpp)
TEST_VECTOR_C_OBJS = $(TEST_VECTOR_C_SRCS:.c=.o)
TEST_VECTOR_CXX_OBJS = $(TEST_VECTOR_CXX_SRCS:.cpp=.o)
TEST_VECTOR_OBJS = $(TEST_VECTOR_C_OBJS) $(TEST_VECTOR_CXX_OBJS)

KMC89_C_SRCS = $(wildcard $(SRC_DIR)/*.c)
KMC89_CXX_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
KMC89_C_OBJS = $(KMC89_C_SRCS:.c=.o)
KMC89_CXX_OBJS = $(KMC89_CXX_SRCS:.c=.o)
KMC89_OBJS = $(KMC89_C_OBJS) $(KMC89_CXX_OBJS)

LLVM_MODULES = core analysis bitwriter
LLVM_CFLAGS = `llvm-config --cflags`
LLVM_CXXFLAGS = `llvm-config --cxxflags`
LLVM_LDFLAGS = `llvm-config --ldflags`
LLVM_LIBS = `llvm-config --libs $(LLVM_MODULES)` -lpthread -ldl -lncurses

.SUFFIXES: $(TESTSUFFIX)

RM = rm -f
AR = ar rcs

UNITTESTS = $(TARGET)
# UNITTESTS = $(TEST_VECTOR_DIR)/vector_int_test.out

all:

test: testsource_test unittests

testsource_test: tests_stage1 tests_stage2

tests_stage1: $(STAGE1_OBJS)

tests_stage2: $(STAGE2_OBJS)

$(STAGE1_DIR)/%$(TESTSUFFIX): $(STAGE1_DIR)/%.c $(STAGE1_LIBS)
	$(CC) $(TESTS_CFLAGS) $< $(STAGE1_LIBS) -o $@

$(STAGE1_LIBS_DIR)/%.o: $(STAGE1_LIBS_DIR)/%.c
	$(CC) $(STAGE1_LIBS_CFLAGS) $< -c -o $@

$(STAGE2_DIR)/%$(TESTSUFFIX): $(STAGE2_DIR)/%.c
	$(CC) $(TESTS_CFLAGS) $< -o $@


unittests: $(UNITTESTS)

$(GTEST_LIB): $(GTEST_OBJS)
	$(AR) $@ $^

$(GTEST_DIR)/%.o: $(GTEST_DIR)/%.cc
	$(CXX) $(CXXFLAGS) $(GTEST_INCLUDE) $(GTEST_FLAGS) -c $< -o $@

$(TEST_VECTOR_DIR)/vector_int_test.out: $(VECTOR_OBJ) $(TEST_VECTOR_OBJS) $(GTEST_LIB)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_LDFLAGS)

$(TEST_VECTOR_DIR)/%.o: $(TEST_VECTOR_DIR)/%.cpp $(VECTOR_HEADER)
	$(CXX) $(CXXFLAGS) $(GTEST_INCLUDE) -c $< -o $@

$(TEST_VECTOR_DIR)/%.o: $(TEST_VECTOR_DIR)/%.c $(VECTOR_HEADER)
	$(CC) $(CFLAGS) $(GTEST_INCLUDE) -c $< -o $@


$(TARGET): $(KMC89_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LLVM_LIBS) $(LLVM_LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LLVM_CFLAGS) -c $< -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(LLVM_CXXFLAGS) -c $< -o $@


clean:
	$(RM) $(TESTS_OBJS) $(UNITTESTS) $(GTEST_OBJS) $(VECTOR_OBJ) $(TEST_VECTOR_OBJS) $(KMC89_OBJS)

distclean: clean
	$(RM) $(GTEST_LIB) $(TARGET)

.PHONY: test clean
.PRECIOUS: $(STAGE1_LIBS)
