# c89-compiler/src/Makefile

TOP_DIR := ..

C_SRCS := $(wildcard *.c)
CXX_SRCS := $(wildcard *.cpp)
C_OBJS := $(C_SRCS:.c=.o)
CXX_OBJS := $(CXX_SRCS:.cpp=.o)
OBJS := $(C_OBJS) $(CXX_OBJS)
TARGET := kmc89

include $(TOP_DIR)/Makefile.common
include Makefile.common

build: $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@
