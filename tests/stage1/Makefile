# c89-compiler/tests/stage1/Makefile

TOP_DIR := ../..
LIB_DIR := lib

include $(TOP_DIR)/Makefile.common

LIB_SRCS := $(wildcard $(LIB_DIR)/*.c)
LIB_OBJS := $(LIB_SRCS:.c=.o)

TARGET := $(OBJS:.o=.out)
OBJS += $(LIB_OBJS)

DO_TEST_PREFIX := do_test_
DO_TEST_TARGETS := $(addprefix $(DO_TEST_PREFIX),$(TARGET))

source_test: $(TARGET)

%.out: %.o $(LIB_OBJS)
	$(CC) $< $(LIB_OBJS) -o $@

do_test: $(DO_TEST_TARGETS)

$(DO_TEST_TARGETS): $(DO_TEST_PREFIX)%: %
	./$*

.PHONY: source_test do_test
.PRECIOUS: $(LIB_OBJS)
