#clang-format --style=file s21_string.c test.c s21_string.h -i
#valgrind --leak-check=full --leak-resolution=high ./3v1.out
#CK_FORK=no leaks --atExit -- ./test.out
python3 ../materials/linters/cpplint.py *.h s21_string.c test.c
cppcheck --enable=all --suppress=missingIncludeSystem --check-config s21_string.c test.c s21_string.h
