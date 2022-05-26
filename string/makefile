CC = gcc
CFLAGS = -Wall -Wextra -Werror
# -lrt -lsubunit
LDFLAGS = -lcheck -lm -lpthread
COVERFLAGS = -fprofile-arcs -ftest-coverage
NAME = s21_string

.PHONY: all
all: s21_string.a test gcov_report

.PHONY: s21_string.a
s21_string.a: $(NAME).c $(NAME).h
	${CC} $(CFLAGS) -c $(NAME).c
	ar rc $(NAME).a $(NAME).o

.PHONY: test
test: $(NAME).h test.c
	${CC} $(CFLAGS) -c $(NAME).c $(COVERFLAGS) $(LDFLAGS)
	ar rc $(NAME).a $(NAME).o
	${CC} ${CFLAGS} test.c -L. $(NAME).a $(COVERFLAGS) ${LDFLAGS} -o test.out
	./test.out

.PHONY: gcov_report
gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

.PHONY: clean
clean: 
	rm -f *.o *.a *.gcno *.gcda *.info *.out
	rm -rf ./report
