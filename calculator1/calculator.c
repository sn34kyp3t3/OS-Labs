#include "calculator.h" // including header files in the implementation files.

// Function definitions
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

double divide(int a, int b) {
    if (b != 0) {
        return (double) a / b;
    } else {
        return 0; // Handle division by zero appropriately
    }
}
