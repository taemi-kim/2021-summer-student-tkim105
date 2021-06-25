Makefile:
CC=gcc
CFLAGS=-std=c99 -pedantic -Wall Wextra

hw2: hw2.o print_functions.o maze.o
	$(CC) -o hw2 hw2.o print_functions.o maze.o

hw2.o: hw2.c maze.h print_functions.h
	$(CC) $(CFLAGS) -c hw2.c

print_functions.o: print_functions.c print_functions.h
	$(CC) $(CFLAGS) -c print_functions.c

maze.o: maze.c maze.h
	$(CC) $(CFLAGS) -c maze.c

clean:
	rm -f *.o hw2

