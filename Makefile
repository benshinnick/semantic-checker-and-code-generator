# CC=gcc -Wall -Wextra -std=c11
CC=gcc -std=c11

SRCS = $(filter-out type-constants.h, $(wildcard *.h))
OBJECTS = $(SRCS:%.h=%.o)

main: $(OBJECTS) main.c
	$(CC) -o $@ $^

clean:
	$(RM) *.o main test
	$(RM) -r *.dSYM .vscode