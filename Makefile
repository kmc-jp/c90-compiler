# c89-compiler/Makefile

SRC_DIR := src
TESTS_DIR := tests
DIRS := $(SRC_DIR) $(TESTS_DIR)

TARGET := kmc89
RM := rm -f

TEST_TARGETS := unit_test source_test
CLEAN_TARGETS := $(addprefix clean_,$(DIRS))
DISTCLEAN_TARGETS := $(addprefix distclean_,$(DIRS))


all: $(TARGET)

$(TARGET): build
	cp $(SRC_DIR)/$(TARGET) $(TARGET)

build:
	$(MAKE) -C $(SRC_DIR) build


test: $(TEST_TARGETS) do_test

$(TEST_TARGETS):
	$(MAKE) -C $(TESTS_DIR) $@

do_test:
	$(MAKE) -C $(TESTS_DIR) do_test


clean: $(CLEAN_TARGETS)

$(CLEAN_TARGETS): clean_%:
	$(MAKE) -C $* clean


distclean: $(DISTCLEAN_TARGETS)
	$(RM) $(TARGET)

$(DISTCLEAN_TARGETS): distclean_%:
	$(MAKE) -C $* distclean


.PHONY: all build test clean distclean\
	$(TEST_TARGETS) $(CLEAN_TARGETS) $(DISTCLEAN_TARGETS)
