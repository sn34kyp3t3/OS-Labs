//Driver File
#include <stdio.h>
#include "calculator.h"

int main() {
    int a = 10, b = 5;

    printf("Addition: %d + %d = %d\n", a, b, add(a, b));
    printf("Subtraction: %d - %d = %d\n", a, b, subtract(a, b));
    printf("Multiplication: %d * %d = %d\n", a, b, multiply(a, b));
    printf("Division: %d / %d = %.2f\n", a, b, divide(a, b));

    return 0;
}

// after compiling both main.c and calculator.c; main.o and calculator.o are linkable modules. Compiled object file ( -o files ) can be linked together to form a program.

// to make a single executable. the files can be linked together like this:
    // > gcc -o calculator calculator.o main.o