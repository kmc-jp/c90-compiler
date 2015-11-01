# c89-compiler/tests/gtest/Makefile

TOP_DIR = ../..
TEST_DIR = $(TOP_DIR)/tests

SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)
TARGET = libgtest.a
INCLUDE = -I$(TEST_DIR)

include $(TOP_DIR)/Makefile.in

CXXFLAGS += -Wno-missing-field-initializers $(INCLUDE)

unit_test: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) $@ $^

.PHONY: unit_test
