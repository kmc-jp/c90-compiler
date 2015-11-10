# c89-compiler/src/Makefile

TOP_DIR := ..

include $(TOP_DIR)/Makefile.common
include Makefile.common

OBJS := $(C_OBJS) $(CXX_OBJS)
TARGET := kmc89

build: $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@
