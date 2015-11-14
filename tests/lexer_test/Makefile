# c89-compiler/tests/lexer_test/Makefile

TOP_DIR = ../..
SRC_DIR = $(TOP_DIR)/src
TESTS_DIR = $(TOP_DIR)/tests
GTEST_DIR = $(TESTS_DIR)/gtest

GTEST_LIB = $(GTEST_DIR)/libgtest.a

LEX_SOURCES = lex.yy.c yacc_mock.c
UTILITY_SOURCES = use_vector.c utility.c
LEX_OBJS = $(LEX_SOURCES:%.c=$(SRC_DIR)/%.o)
UTILITY_OBJS = $(UTILITY_SOURCES:%.c=$(SRC_DIR)/%.o)
C_SRCS = $(wildcard *.c)
CXX_SRCS = $(wildcard *.cpp)
C_OBJS = $(C_SRCS:.c=.o)
CXX_OBJS = $(CXX_SRCS:.cpp=.o)
OBJS = $(C_OBJS) $(CXX_OBJS) $(LEX_OBJS) $(UTILITY_OBJS)
TARGET = lexer_test.out
INCLUDE = -I$(TESTS_DIR) -I$(SRC_DIR)

include $(TOP_DIR)/Makefile.in

CFLAGS += $(INCLUDE)
CXXFLAGS += $(INCLUDE)
LDFLAGS += -L$(GTEST_DIR)
LIBS += -lgtest -lpthread

unit_test: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o $@

$(TARGET): $(GTEST_LIB)

lexer_test.cpp : $(SRC_DIR)/token.h

.PHONY: unit_test
