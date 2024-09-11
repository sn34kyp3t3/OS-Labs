#include <stdio.h>
#include "calculator.h"

int main() {
    Calculator calc;

    // Example usage
    initializeCalculator(&calc, 10, 5, '+');
    performOperation(&calc);
    printResult(&calc);

    initializeCalculator(&calc, 10, 5, '/');
    performOperation(&calc);
    printResult(&calc);

    return 0;
}
