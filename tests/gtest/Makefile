# c89-compiler/tests/gtest/Makefile

TOP_DIR := ../..
TESTS_DIR := $(TOP_DIR)/tests

include $(TOP_DIR)/Makefile.common
include $(TESTS_DIR)/Makefile.common

TARGET := libgtest.a

unit_test: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) $@ $^

gtest-all.o: CXXFLAGS += -Wno-missing-field-initializers

.PHONY: unit_test
