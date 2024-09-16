CC =gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11

all: s21_cat

s21_cat: s21_cat.o s21_cat.c
	$(CC) s21_cat.o -o s21_cat
s21_cat.o: s21_cat.c
	$(CC) $(CFLAGS) -c s21_cat.c -o s21_cat.o
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
	rm -rf *.o s21_cat.out

rebuild: clean all
