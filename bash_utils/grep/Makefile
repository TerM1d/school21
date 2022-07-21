CC= gcc -std=c11 -D_GNU_SOURCE
CFLAGS= -Wall -Wextra -Werror
GREP= s21_grep.c

all: s21_grep

s21_grep:
	$(CC) $(CFLAGS) $(GREP) -o s21_grep

test:
	chmod 777 test.sh
	./test.sh

clean:
	rm -rf s21_grep
	rm -rf *.a *.out *.o *.txt

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem s21_grep.c s21_grep.h
 
lint: 
	cp ../../materials/linters/CPPLINT.cfg .
	python3 ../../materials/linters/cpplint.py --extensions=c *.c
	rm -rf *.cfg

leaks:
	CK_FORK=no leaks --atExit -- ./s21_grep

valgrind:
	CK_FORK=no valgrind --leak-check=full --tool=memcheck ./s21_grep

rebuild:
	make clean
	make all
	rm -rf  *.o *.a
