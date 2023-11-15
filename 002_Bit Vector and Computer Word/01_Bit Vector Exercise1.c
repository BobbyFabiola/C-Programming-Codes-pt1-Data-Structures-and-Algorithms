/*  Author: Fabiola Villanueva
    Description: Bit Vector Exercise 
                (bits represented as an array)
    Date: Oct 07, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef unsigned int SET;

void displayBitVector (SET Z[]);
SET *unionOfBits (SET X[], SET Y[]);
SET *intersectionOfBits (SET X[], SET Y[]);
SET *diferencesOfBits (SET X[], SET Y[]);

int main() {
    system("CLS");
    SET A[SIZE] = {1, 0, 0, 1, 1, 1, 0, 1, 0, 1};
    SET B[SIZE] = {1, 1, 0, 0, 0, 1, 1, 1, 1, 1};

    printf("0. Display.\n");
    printf("\tSET A = ");
    displayBitVector (A);
    printf("\tSET B = ");
    displayBitVector (B);

    printf("\n1. Union of Bits.\n");
    printf("\tA | B = ");
    displayBitVector (unionOfBits (A, B));

    printf("\n2. Intersection of Bits.\n");
    printf("\tA & B = ");
    displayBitVector (intersectionOfBits (A, B));

    printf("\n2. Difference of Bits.\n");
    printf("\tA ^ B = ");
    displayBitVector (diferencesOfBits (A, B));

    printf("\n");
    return 0;
}

void displayBitVector (SET Z[]) {
    int i;
    for (i = 0; i < SIZE; ++i) {
        printf("%d", Z[i]);
    }
    printf("\n");
}

SET *unionOfBits (SET X[], SET Y[]) {
    SET *Z = calloc(SIZE, sizeof(SET));
    int i; 
    for (i = 0; i < SIZE; ++i) {
        Z[i] = (X[i] | Y[i]) ? 1: 0;
    }
    return Z;
}

SET *intersectionOfBits (SET X[], SET Y[]) {
    SET *Z = calloc(SIZE, sizeof(SET));
    int i;
    for (i = 0; i < SIZE; ++i) {
        Z[i] = (X[i] & Y[i]) ? 1: 0;
    }
    return Z;
}

SET *diferencesOfBits (SET X[], SET Y[]) {
    SET *Z = calloc(SIZE, sizeof(SET));
    int i;
    for (i = 0; i < SIZE; ++i) {
        Z[i] = (X[i] ^ Y[i]) ? 1: 0;
    }
    return Z;
}