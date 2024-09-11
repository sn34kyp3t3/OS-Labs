#include "prime.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("error: must provide a single integer value to test\n");
    return 1;
  } else {
    int n = atoi(argv[1]);
    int prime = isPrime(n);
    printf("isPrime(%d) = %d\n", n, prime);
    return 0;
  }
}
