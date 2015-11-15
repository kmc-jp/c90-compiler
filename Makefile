# c89-compiler/Makefile

SRC_DIR := src
TESTS_DIR := tests
DIRS := $(SRC_DIR) $(TESTS_DIR)

TARGET := kmc89
RM := rm -f

CLEAN_PREFIX := clean_
DISTCLEAN_PREFIX := distclean_

TEST_TARGETS := unit_test source_test do_test
CLEAN_TARGETS := $(addprefix $(CLEAN_PREFIX),$(DIRS))
DISTCLEAN_TARGETS := $(addprefix $(DISTCLEAN_PREFIX),$(DIRS))


all: $(TARGET)

$(TARGET): build
	cp $(SRC_DIR)/$(TARGET) $(TARGET)

build:
	$(MAKE) -C $(SRC_DIR) build


test: $(TEST_TARGETS)

$(TEST_TARGETS):
	$(MAKE) -C $(TESTS_DIR) $@


clean: $(CLEAN_TARGETS)

$(CLEAN_TARGETS): $(CLEAN_PREFIX)%:
	$(MAKE) -C $* clean


distclean: $(DISTCLEAN_TARGETS)
	$(RM) $(TARGET)

$(DISTCLEAN_TARGETS): $(DISTCLEAN_PREFIX)%:
	$(MAKE) -C $* distclean


.PHONY: all build test clean distclean\
	$(TEST_TARGETS) $(CLEAN_TARGETS) $(DISTCLEAN_TARGETS)
