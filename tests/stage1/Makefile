# c89-compiler/tests/stage1/Makefile

TOP_DIR = ../..
LIB_DIR = lib

LIB_SRCS = $(wildcard $(LIB_DIR)/*.c)
LIB_OBJS = $(LIB_SRCS:.c=.o)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.out) $(LIB_OBJS)

include $(TOP_DIR)/Makefile.in

source_test: lib_build $(OBJS)

lib_build: $(LIB_OBJS)

.o.out: lib_build
	$(CC) $< $(LIB_OBJS) -o $@

.PHONY: source_test lib_build
.PRECIOUS: $(LIB_OBJS)
