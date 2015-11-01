# c89-compiler/tests/stage1/Makefile

TOP_DIR = ../..
LIB_DIR = lib

LIB_SRCS = $(wildcard $(LIB_DIR)/*.c)
LIB_OBJS = $(LIB_SRCS:.c=.o)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.out)

include $(TOP_DIR)/Makefile.in

source_test: lib_build $(OBJS)

lib_build:
	cd $(LIB_DIR); make source_test

.o.out: lib_build
	$(CC) $< $(LIB_OBJS) -o $@

clean: lib_clean

lib_clean:
	cd $(LIB_DIR); make clean

.PHONY: source_test lib_build lib_clean
