CC =gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep: s21_grep.o s21_grep.c
	$(CC) s21_grep.o -o s21_grep
s21_grep.o: s21_grep.c
	$(CC) $(CFLAGS) -c s21_grep.c -o s21_grep.o
clang-check:
	@cp ../../materials/linters/.clang-format ./
	@clang-format -n *.c *.h
	@rm .clang-format
clang:
	@cp ../../materials/linters/.clang-format ./
	@clang-format -i *.c *.h
	@rm .clang-format
cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h *.c *.h
clean:
	rm -rf *.o s21_grep.out

rebuild: clean all
