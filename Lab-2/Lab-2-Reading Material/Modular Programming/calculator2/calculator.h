#ifndef CALCULATOR_H
#define CALCULATOR_H

// Define the ADT for a calculator operation
typedef struct {
    int operand1;
    int operand2;
    int result;
    char operation; // '+', '-', '*', '/'
} Calculator;

// Function declarations
void initializeCalculator(Calculator* calc, int a, int b, char op);
void performOperation(Calculator* calc);
void printResult(const Calculator* calc);

#endif /* CALCULATOR_H */
