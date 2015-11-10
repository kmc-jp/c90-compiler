# c89-compiler/tests/stage2/Makefile

TOP_DIR := ../..

include $(TOP_DIR)/Makefile.common

OBJS := $(C_OBJS)

source_test: $(OBJS)

.o.out:
	$(CC) $< -o $@

.PHONY: source_test
