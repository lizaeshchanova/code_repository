CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

PATH1 = cat/
PATH2 = grep/

EXEC1 = $(PATH1)s21_cat
EXEC2 = $(PATH2)s21_grep

SRC1 = $(wildcard $(PATH1)*.c)
OBJ1 = $(patsubst %.c, %.o, $(SRC1))

SRC2 = $(wildcard $(PATH2)*.c)
OBJ2 = $(patsubst %.c, %.o, $(SRC2))

all: s21_cat s21_grep

s21_cat: $(OBJ1)
	$(CC) $(CFLAGS) $(OBJ1) -o $(EXEC1)
	rm -rf *.o $(PATH1)*.o

s21_grep: $(OBJ2)
	$(CC) $(CFLAGS) $(OBJ2) -o $(EXEC2)
	rm -rf *.o $(PATH2)*.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

format-check:
	@cp ../materials/linters/.clang-format ./
	@clang-format -n $(PATH1)*.c $(PATH1)*.h $(PATH2)*.c $(PATH2)*.h
	@rm .clang-format

format:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i $(PATH1)*.c $(PATH1)*.h $(PATH2)*.c $(PATH2)*.h
	@rm .clang-format

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem $(PATH1)*.c $(PATH1)*.h $(PATH2)*.c $(PATH2)*.h

clean:
	rm -rf *.o $(PATH1)*.o $(EXEC1) $(PATH2)*.o $(EXEC2)