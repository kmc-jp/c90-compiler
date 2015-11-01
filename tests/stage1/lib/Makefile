# c89-compiler/tests/stage1/lib/Makefile

TOP_DIR = ../../..

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

include $(TOP_DIR)/Makefile.in

source_test: $(OBJS)

.PRECIOUS: $(OBJS)
