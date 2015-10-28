CC ?= gcc
CXX ?= g++
CFLAGS ?= -Wall -Wextra -O2
CXXFLAGS ?= -Wall -Wextra -O2

SRC_DIR = src

TESTSUFFIX = .out
TESTS_DIR = tests
STAGE1_DIR = $(TESTS_DIR)/stage1
STAGE2_DIR = $(TESTS_DIR)/stage2
TESTS_STAGE1 = $(wildcard $(STAGE1_DIR)/*.c)
TESTS_STAGE2 = $(wildcard $(STAGE2_DIR)/*.c)
TESTS = $(TESTS_STAGE1) $(TESTS_STAGE2)
STAGE1_OBJS = $(TESTS_STAGE1:.c=$(TESTSUFFIX))
STAGE2_OBJS = $(TESTS_STAGE2:.c=$(TESTSUFFIX))
TESTS_OBJS = $(STAGE1_OBJS) $(STAGE2_OBJS) $(TESTS_LIBS_STAGE1)
TESTS_CFLAGS ?= -ansi -pedantic $(CFLAGS)
TESTS_LIBS_STAGE1_DIR = $(STAGE1_DIR)/lib
TESTS_LIBS_STAGE1 = $(TESTS_LIBS_STAGE1_DIR)/print.o
TESTS_LIBS_STAGE1_CFLAGS ?= $(TESTS_CFLAGS)

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
TEST_VECTOR_OBJS = $(TEST_VECTOR_C_SRCS:.c=.o) $(TEST_VECTOR_CXX_SRCS:.cpp=.o)

.SUFFIXES: $(TESTSUFFIX)

RM = rm -f
AR = ar rcs

UNITTESTS = $(TEST_VECTOR_DIR)/vector_int_test.out

all:

test: testsource_test unittests

testsource_test: tests_stage1 tests_stage2

tests_stage1: $(STAGE1_OBJS)

tests_stage2: $(STAGE2_OBJS)

$(STAGE1_DIR)/%$(TESTSUFFIX): $(STAGE1_DIR)/%.c $(TESTS_LIBS_STAGE1)
	$(CC) $(TESTS_CFLAGS) $< $(TESTS_LIBS_STAGE1) -o $@

$(TESTS_LIBS_STAGE1_DIR)/%.o: $(TESTS_LIBS_STAGE1_DIR)/%.c
	$(CC) $(TESTS_LIBS_STAGE1_CFLAGS) $< -c -o $@

$(STAGE2_DIR)/%$(TESTSUFFIX): $(STAGE2_DIR)/%.c
	$(CC) $(TESTS_CFLAGS) $< -o $@


unittests: $(UNITTESTS)

$(GTEST_LIB): $(GTEST_OBJS)
	$(AR) $@ $^

$(GTEST_DIR)/%.o: $(GTEST_DIR)/%.cc
	$(CXX) $(CXXFLAGS) $(GTEST_INCLUDE) $(GTEST_FLAGS) -c $< -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(VECTOR_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_VECTOR_DIR)/vector_int_test.out: $(VECTOR_OBJ) $(TEST_VECTOR_OBJS) $(GTEST_LIB)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_LDFLAGS)

$(TEST_VECTOR_DIR)/%.o: $(TEST_VECTOR_DIR)/%.cpp $(VECTOR_HEADER)
	$(CXX) $(CXXFLAGS) $(GTEST_INCLUDE) -c $< -o $@

$(TEST_VECTOR_DIR)/%.o: $(TEST_VECTOR_DIR)/%.c $(VECTOR_HEADER)
	$(CC) $(CFLAGS) $(GTEST_INCLUDE) -c $< -o $@

clean:
	$(RM) $(TESTS_OBJS) $(UNITTESTS)

distclean: clean
	$(RM) $(GTEST_LIB) $(GTEST_OBJS)

.PHONY: test clean
