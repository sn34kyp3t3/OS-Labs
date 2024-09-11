# Variable declaration
executableName = calculator

# Targets and recipes
all: $(executableName)

$(executableName): main.o calculator.o
	gcc -o $(executableName) main.o calculator.o

main.o: main.c calculator.h
	gcc -c main.c

calculator.o: calculator.c calculator.h
	gcc -c calculator.c

clean:
	rm -f *.o $(executableName)
