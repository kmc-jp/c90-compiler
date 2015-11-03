# c89-compiler/tests/Makefile

STAGE1_DIR = stage1
STAGE2_DIR = stage2
GTEST_DIR = gtest
VECTOR_TEST_DIR = vector_test


source_test: stage1_test stage2_test

stage1_test:
	cd $(STAGE1_DIR); make source_test

stage2_test:
	cd $(STAGE2_DIR); make source_test


unit_test: gtest vector_test

gtest:
	cd $(GTEST_DIR); make unit_test

vector_test: gtest
	cd $(VECTOR_TEST_DIR); make unit_test


CLEAN_TARGETS = stage1_clean stage2_clean gtest_clean vector_test_clean
clean: $(CLEAN_TARGETS)

stage1_clean:
	cd $(STAGE1_DIR); make clean

stage2_clean:
	cd $(STAGE2_DIR); make clean

gtest_clean:
	cd $(GTEST_DIR); make clean

vector_test_clean:
	cd $(VECTOR_TEST_DIR); make clean


DISTCLEAN_TARGETS = stage1_distclean stage2_distclean gtest_distclean vector_test_distclean
distclean: $(DISTCLEAN_TARGETS)

stage1_distclean:
	cd $(STAGE1_DIR); make distclean

stage2_distclean:
	cd $(STAGE2_DIR); make distclean

gtest_distclean:
	cd $(GTEST_DIR); make distclean

vector_test_distclean:
	cd $(VECTOR_TEST_DIR); make distclean


.PHONY: source_test stage1_test stage2_test unit_test gtest vector_test\
	clean $(CLEAN_TARGETS) distclean $(DISTCLEAN_TARGETS)
