# c89-compiler/Makefile

SRC_DIR := src
TESTS_DIR := tests
DIRS := $(SRC_DIR) $(TESTS_DIR)

TARGET := kmc89
RM := rm -f

TEST_TARGETS := unit_test source_test
CLEAN_TARGETS := $(DIRS:=_clean)
DISTCLEAN_TARGETS := $(DIRS:=_distclean)


all: $(TARGET) test

$(TARGET): build
	cp $(SRC_DIR)/$(TARGET) $(TARGET)

build:
	$(MAKE) -C $(SRC_DIR) build


test: $(TEST_TARGETS)

$(TEST_TARGETS):
	$(MAKE) -C $(TESTS_DIR) $@


clean: $(CLEAN_TARGETS)

$(CLEAN_TARGETS):
	$(MAKE) -C $(@:_clean=) clean


distclean: $(DISTCLEAN_TARGETS)
	$(RM) $(TARGET)

$(DISTCLEAN_TARGETS):
	$(MAKE) -C $(@:_distclean=) distclean


.PHONY: all build test clean distclean\
	$(TEST_TARGETS) $(CLEAN_TARGETS) $(DISTCLEAN_TARGETS)
