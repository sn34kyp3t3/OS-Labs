CC = gcc
CFLAGS = -Wall

all: matrix_multiplication

matrix_multiplication: main.o misc.o
	$(CC) $(CFLAGS) -o matrix_multiplication main.o misc.o

main.o: main.c misc.h
	$(CC) $(CFLAGS) -c main.c

misc.o: misc.c misc.h
	$(CC) $(CFLAGS) -c misc.c

clean:
	rm -f matrix_multiplication *.o
