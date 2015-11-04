# c89-compiler/tests/Makefile

STAGE1_DIR := stage1
STAGE2_DIR := stage2
GTEST_DIR := gtest
VECTOR_TEST_DIR := vector_test
SOURCE_TEST_DIRS := $(STAGE1_DIR) $(STAGE2_DIR)
UNIT_TEST_DIRS := $(GTEST_DIR) $(VECTOR_TEST_DIR)
DIRS := $(SOURCE_TEST_DIRS) $(UNIT_TEST_DIRS)

SOURCE_TEST_TARGETS := $(SOURCE_TEST_DIR:=_test)
UNIT_TEST_TARGETS := $(UNIT_TEST_DIRS:=_test)
CLEAN_TARGETS := $(DIRS:=_clean)
DISTCLEAN_TARGETS := $(DIRS:=_distclean)


source_test: $(SOURCE_TEST_TARGETS)

$(SOURCE_TEST_TARGETS):
	$(MAKE) -C $(@:_test=) source_test


unit_test: $(UNIT_TEST_TARGETS)

$(UNIT_TEST_TARGETS):
	$(MAKE) -C $(@:_test=) unit_test


clean: $(CLEAN_TARGETS)

$(CLEAN_TARGETS):
	$(MAKE) -C $(@:_clean=) clean


distclean: $(DISTCLEAN_TARGETS)

$(DISTCLEAN_TARGETS):
	$(MAKE) -C $(@:_distclean=) distclean


.PHONY: source_test unit_test clean distclean\
	$(SOURCE_TEST_TARGETS) $(UNIT_TEST_TARGETS)\
	$(CLEAN_TARGETS) $(DISTCLEAN_TARGETS)
