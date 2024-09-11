executableName = lab2

all: $(executableName)

$(executableName): main.o DEPARTMENT.o misc.o
	gcc -o $(executableName) main.o DEPARTMENT.o misc.o
main.o: main.c DEPARTMENT.h misc.h
	gcc -c main.c
DEPARTMENT.o: DEPARTMENT.c DEPARTMENT.h
	gcc -c DEPARTMENT.c
misc.o: misc.c misc.h
	gcc -c misc.c
clean:
	rm -f *.o $(executableName)
