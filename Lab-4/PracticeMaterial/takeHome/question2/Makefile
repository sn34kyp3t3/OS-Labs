CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEPS = misc.h processCreation.h
OBJ = question2.o misc.o processCreation.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

all: question2

question2: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o question2
