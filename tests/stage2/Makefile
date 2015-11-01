# c89-compiler/tests/stage1/Makefile

TOP_DIR = ../..

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.out)

include $(TOP_DIR)/Makefile.in

source_test: $(OBJS)

.o.out:
	$(CC) $< -o $@

.PHONY: source_test
