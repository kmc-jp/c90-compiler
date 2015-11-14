# c89-compiler/src/Makefile

TOP_DIR = ..

C_SRCS = $(wildcard *.c)
CXX_SRCS = $(wildcard *.cpp)
C_OBJS = $(C_SRCS:.c=.o)
CXX_OBJS = $(CXX_SRCS:.cpp=.o)
OBJS = $(C_OBJS) $(CXX_OBJS)
TARGET = kmc89

LLVM_MODULES = core analysis bitwriter
LLVM_CFLAGS = `llvm-config --cflags`
LLVM_CXXFLAGS = `llvm-config --cxxflags`
LLVM_LDFLAGS = `llvm-config --ldflags`
LLVM_LIBS = `llvm-config --libs $(LLVM_MODULES)` -lpthread -ldl -lncurses

OBJS += lex.yy.o

include $(TOP_DIR)/Makefile.in

CFLAGS += $(LLVM_CFLAGS)
CXXFLAGS += $(LLVM_CXXFLAGS)
LDFLAGS += $(LLVM_LDFLAGS)
LIBS += $(LLVM_LIBS)

build: $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LIBS) -o $@

lex.yy.c lex.yy.h: lexer.l
	$(LEX) --header-file=lex.yy.h -o lex.yy.c lexer.l

lexer_adapter.o: lex.yy.h lex.yy.o
