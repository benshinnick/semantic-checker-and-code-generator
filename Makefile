# CC=gcc -Wall -Wextra -std=c11
CC=gcc -std=c11

SRCS = $(filter-out src/type-constants.h, $(wildcard src/*.h))
OBJECTS = $(SRCS:src/%.h=src/%.o)

main: $(OBJECTS) src/main.c
	$(CC) -o $@ $^

test: $(OBJECTS) src/test.c
	$(CC) -o $@ $^

clean:
	$(RM) src/*.o main test
	$(RM) -r *.dSYM .vscode