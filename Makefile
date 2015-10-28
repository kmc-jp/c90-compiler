CC ?= gcc
CXX ?= g++
CFLAGS ?= -Wall -Wextra -O2

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
GTEST_FLAGS = -Wno-missing-field-init -lpthread -I$(TESTS_DIR)
GTEST_SRCS = $(wildcard $(GTEST_DIR)/*.cc)
GTEST_OBJS = $(GTEST_SRCS:.cc=.o)
GTEST_LIB = libgtest.so

.SUFFIXES: $(TESTSUFFIX)

RM = rm -f
AR = ar rcs

UNITTESTS = $(TESTS_DIR)/vector_int_test

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
	$(AR) $@ $(GTEST_OBJS)

$(TESTS_DIR)/vector_int_test: $(SRC_DIR)/vector.o $(SRC_DIR)/vector_int.o $(TESTS_DIR)/vector_int_test.o $(GTEST_LIB)
	$(CXX) -o $@ $(SRC_DIR)/vector.o $(SRC_DIR)/vector_int.o $(TESTS_DIR)/vector_int_test.o $(GTEST_LIB) -lpthread

$(GTEST_DIR)/%.o: $(GTEST_DIR)/%.cc
	$(CXX) -c $< $(GTEST_FLAGS) -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/vector.h
	$(CC) -c $< -o $@

$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.cpp $(SRC_DIR)/vector.h
	$(CXX) -c $< -o $@

clean:
	$(RM) $(TESTS_OBJS) $(UNITTESTS)

distclean: clean
	$(RM) $(GTEST_LIB) $(GTEST_OBJS)

.PHONY: test clean
