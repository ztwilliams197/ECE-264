EXECUTABLE=test_count_words
SRC_C=count_words.c
TEST_C=test_count_words.c
SRC_H=count_words.h clog.h miniunit.h
CC=gcc
SUB=264submit
CFLAGS=-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV=$(CFLAGS) -fprofile-arcs -ftest-coverage
SHELL=/bin/bash
ASG_NICKNAME=HW55
FILE_SUB=count_words.c test_count_words.c expected.txt miniunit.h clog.h 
 
$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o test_count_words count_words.c test_count_words.c $(CFLAGS)

submit: 
	$(SUB) $(ASG_NICKNAME) $(FILE_SUB)

test: $(EXECUTABLE) $(TEST_EXPECTED) debug
	@# If actual output matches expected output then count it as a success
	@if diff -a -B <("./$(EXECUTABLE)")$(TEST_EXPECTED) &> /dev/null ; then \
		echo -e "\x1b[32mTest passed: output of $(EXECUTABLE) matches $(TEST_EXPECTED)\x1b[0m" ; \
	else \
		echo -e "\x1b[31mTest failed: output of $(EXECUTABLE) does NOT match $(TEST_EXPECTED)\x1b[0m" ; \
	fi

pretest: submit
	264test $(ASG_NICKNAME)

clean:
	rm -f $(EXECUTABLE)
	rm *.c.gcov
	rm *.gcda
	rm *.gcno

coverage:
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS_GCOV)
	./$(EXECUTABLE)
	gcov -f $(SRC_C)

debug: $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -g -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS) -DDEBUG

.PHONY: submit test pretest coverage
