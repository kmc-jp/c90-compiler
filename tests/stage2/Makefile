# c89-compiler/tests/stage2/Makefile

TOP_DIR := ../..

include $(TOP_DIR)/Makefile.common

TARGET := $(OBJS:.o=.out)

DO_TEST_PREFIX := do_test_
DO_TEST_TARGETS := $(addprefix $(DO_TEST_PREFIX),$(TARGET))

source_test: $(TARGET)

%.out: %.o
	$(CC) $< -o $@

do_test: $(DO_TEST_TARGETS)

$(DO_TEST_TARGETS): $(DO_TEST_PREFIX)%: %
	./$*

.PHONY: source_test do_test
