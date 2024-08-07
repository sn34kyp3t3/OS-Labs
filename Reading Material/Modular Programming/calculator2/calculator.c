#include "calculator.h"
#include <stdio.h>

void initializeCalculator(Calculator* calc, int a, int b, char op) {
    calc->operand1 = a;
    calc->operand2 = b;
    calc->operation = op;
}

void performOperation(Calculator* calc) {
    switch (calc->operation) {
        case '+':
            calc->result = calc->operand1 + calc->operand2;
            break;
        case '-':
            calc->result = calc->operand1 - calc->operand2;
            break;
        case '*':
            calc->result = calc->operand1 * calc->operand2;
            break;
        case '/':
            if (calc->operand2 != 0) {
                calc->result = calc->operand1 / calc->operand2;
            } else {
                printf("Error: Division by zero\n");
                calc->result = 0;
            }
            break;
        default:
            printf("Error: Unknown operation\n");
            calc->result = 0;
    }
}

void printResult(const Calculator* calc) {
    printf("Result: %d %c %d = %d\n", calc->operand1, calc->operation, calc->operand2, calc->result);
}
