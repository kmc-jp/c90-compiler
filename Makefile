# c89-compiler/Makefile

SRC_DIR = src
TESTS_DIR = tests

TARGET = kmc89
RM = rm -f


all: $(TARGET) test

$(TARGET): build
	cp $(SRC_DIR)/$(TARGET) $(TARGET)

build:
	cd $(SRC_DIR); make build


test: unit_test source_test

unit_test: build
	cd $(TESTS_DIR); make unit_test

source_test:
	cd $(TESTS_DIR); make source_test


clean: src_clean tests_clean

src_clean:
	cd $(SRC_DIR); make clean

tests_clean:
	cd $(TESTS_DIR); make clean


distclean: src_distclean tests_distclean
	$(RM) $(TARGET)

src_distclean:
	cd $(SRC_DIR); make distclean

tests_distclean:
	cd $(TESTS_DIR); make distclean


.PHONY: all build test unit_test source_test\
	clean src_clean tests_clean\
	distclean src_distclean tests_distclean
