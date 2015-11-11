# c89-compiler/tests/stage1/Makefile

TOP_DIR := ../..
LIB_DIR := lib

include $(TOP_DIR)/Makefile.common

LIB_SRCS := $(wildcard $(LIB_DIR)/*.c)
LIB_OBJS := $(LIB_SRCS:.c=.o)
OBJS := $(C_OBJS) $(LIB_OBJS)
TARGET := $(C_OBJS:.o=.out)

source_test: $(TARGET)

%.out: %.o $(LIB_OBJS)
	$(CC) $< $(LIB_OBJS) -o $@

.PHONY: source_test
.PRECIOUS: $(LIB_OBJS)
