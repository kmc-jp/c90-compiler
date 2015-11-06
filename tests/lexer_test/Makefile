# c89-compiler/tests/lexer_test/Makefile

TOP_DIR = ../..
SRC_DIR = $(TOP_DIR)/src
TESTS_DIR = $(TOP_DIR)/tests
GTEST_DIR = $(TESTS_DIR)/gtest

GTEST_LIB = $(GTEST_DIR)/libgtest.a
SRC_OBJS = $(SRC_DIR)/lex.yy.o $(SRC_DIR)/yacc_mock.o $(SRC_DIR)/lexer_adapter.o $(SRC_DIR)/use_vector.o $(SRC_DIR)/utility.o

C_SRCS = $(wildcard *.c)
CXX_SRCS = $(wildcard *.cpp)
C_OBJS = $(C_SRCS:.c=.o)
CXX_OBJS = $(CXX_SRCS:.cpp=.o)
OBJS = $(C_OBJS) $(CXX_OBJS)
TARGET = lexer_test.out
INCLUDE = -I$(TESTS_DIR) -I$(SRC_DIR)

include $(TOP_DIR)/Makefile.in

CFLAGS += $(INCLUDE)
CXXFLAGS += $(INCLUDE)
LDFLAGS += -L$(GTEST_DIR)
LIBS += -lgtest -lpthread
OBJS += $(SRC_DIR)/lex.yy.o

unit_test: $(TARGET)

$(TARGET): $(OBJS) $(SRC_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o $@

$(TARGET): $(GTEST_LIB)

.PHONY: unit_test
