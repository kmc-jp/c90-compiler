CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2

TESTSUFFIX = .out
TESTSDIR = tests
TESTS = $(wildcard $(TESTSDIR)/*.c)
TESTS_OBJ = $(TESTS:.c=$(TESTSUFFIX))
.SUFFIXES: $(TESTSUFFIX)

RM = rm -f

all:

test: testsource_test

testsource_test: $(TESTS_OBJ)

$(TESTSDIR)/%$(TESTSUFFIX): tests/%.c
	$(CC) $< -o $@

clean:
	$(RM) $(TESTS_OBJ)

.PHONY: test clean
