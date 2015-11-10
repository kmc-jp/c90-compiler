# c89-compiler/tests/gtest/Makefile

TOP_DIR := ../..
TESTS_DIR := $(TOP_DIR)/tests

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:.cc=.o)
TARGET := libgtest.a

include $(TOP_DIR)/Makefile.common
include $(TESTS_DIR)/Makefile.common

CXXFLAGS += -Wno-missing-field-initializers

unit_test: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) $@ $^

.PHONY: unit_test
