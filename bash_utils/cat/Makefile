CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
# -lrt -lsubunit
LDFLAGS = -lcheck -lm -lpthread
#COVERFLAGS = -fprofile-arcs -ftest-coverage
#NAME = cat/s21_cat

.PHONY: all
all: s21_cat test_cat

.PHONY: s21_cat
s21_cat: s21_cat.c
	${CC} $(CFLAGS) s21_cat.c -o s21_cat

.PHONY: test_cat
test_cat:
	chmod +x test_cat
	bash test_cat

.PHONY: clean
clean:
	rm -f *.o *.a s21_cat
