# c89-compiler/tests/Makefile

STAGE1_DIR := stage1
STAGE2_DIR := stage2
GTEST_DIR := gtest
VECTOR_TEST_DIR := vector_test
SOURCE_TEST_DIRS := $(STAGE1_DIR) $(STAGE2_DIR)
UNIT_TEST_DIRS := $(GTEST_DIR) $(VECTOR_TEST_DIR)
DO_TEST_DIRS := $(VECTOR_TEST_DIR)
DIRS := $(SOURCE_TEST_DIRS) $(UNIT_TEST_DIRS)

SOURCE_TEST_TARGETS := $(addprefix source_test_,$(SOURCE_TEST_DIRS))
UNIT_TEST_TARGETS := $(addprefix unit_test_,$(UNIT_TEST_DIRS))
DO_TEST_TARGETS := $(addprefix do_test_,$(DO_TEST_DIRS))
CLEAN_TARGETS := $(addprefix clean_,$(DIRS))
DISTCLEAN_TARGETS := $(addprefix distclean_,$(DIRS))


source_test: $(SOURCE_TEST_TARGETS)

$(SOURCE_TEST_TARGETS): source_test_%:
	$(MAKE) -C $* source_test


unit_test: $(UNIT_TEST_TARGETS)

$(UNIT_TEST_TARGETS): unit_test_%:
	$(MAKE) -C $* unit_test


do_test: $(DO_TEST_TARGETS)

$(DO_TEST_TARGETS): do_test_%:
	$(MAKE) -C $* do_test


clean: $(CLEAN_TARGETS)

$(CLEAN_TARGETS): clean_%:
	$(MAKE) -C $* clean


distclean: $(DISTCLEAN_TARGETS)

$(DISTCLEAN_TARGETS): distclean_%:
	$(MAKE) -C $* distclean


.PHONY: source_test unit_test clean distclean\
	$(SOURCE_TEST_TARGETS) $(UNIT_TEST_TARGETS)\
	$(CLEAN_TARGETS) $(DISTCLEAN_TARGETS)
