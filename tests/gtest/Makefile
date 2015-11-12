# c89-compiler/tests/gtest/Makefile

TOP_DIR := ../..
TESTS_DIR := $(TOP_DIR)/tests

include $(TOP_DIR)/Makefile.common
include $(TESTS_DIR)/Makefile.common

OBJS := $(CC_OBJS)
TARGET := libgtest.a

CXXFLAGS += -Wno-missing-field-initializers

unit_test: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) $@ $^

.PHONY: unit_test
