executableName = isPrimeCheck.out
driver = driver

# Makes
all: $(driver).o prime.o
	gcc $(driver).o prime.o -o $(executableName)

$(driver).o: $(driver).c
	gcc -c $(driver).c

prime.o: prime.c
	gcc -c prime.c

# To clean the compilation.
clean:
	rm -f *.o $(executableName)
