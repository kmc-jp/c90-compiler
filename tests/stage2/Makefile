# c89-compiler/tests/stage2/Makefile

TOP_DIR := ../..

include $(TOP_DIR)/Makefile.common

OBJS := $(C_OBJS)
TARGET := $(C_OBJS:.o=.out)

source_test: $(TARGET)

%.out: %.o
	$(CC) $< -o $@

.PHONY: source_test
