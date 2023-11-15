/*  Author: Fabiola Villanueva
    Description: First Hands-on Computer Word
    Date: Oct 07, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

//typedefs
typedef unsigned char SET;

void initializeSet (SET *X);
void displaySet (SET X);
void displaySetArr (SET Y[]);

int main() {
    system("CLS");
    SET A[] = "Fabiola";                       //print these values in binary representation
    SET B = 'A';
    SET C[SIZE] = {11, 22, 33, 44, 55};
    SET D = 'F';
    SET E;

    printf("0. Initialize.\n");
    initializeSet (&E);
    printf("\tE = ");
    displaySet (E);

    printf("\n1. Displaying Single Variables.\n");
    printf("\tB = ");
    displaySet (B);

    printf("\n2. Displaying Array.\n");
    displaySetArr (C);

    printf("\n");
    return 0;
}

//function defintions
void initializeSet (SET *X) {
    *X = 0;
}

void displaySet (SET X) {
    if (X == 0) {
        printf("Set is of zero (0) value.\n");
    } else {
        SET mask = sizeof (SET) * 8;
        for (mask = 1 << (mask-1); mask > 0; mask >>= 1) {
            printf("%d", (X & mask)? 1: 0);
        }
        printf("\n");
    }
}

void displaySetArr (SET Y[]) {
    int i;
    SET mask;
    for (i = 0; i < SIZE; ++i) {        //traversing the array
        printf("\t[%d] = ", Y[i]);
        mask = sizeof (SET) * 8;
        for (mask = 1 << (mask-1); mask > 0; mask >>= 1) {
            printf("%d", (Y[i] & mask)? 1: 0);
        }
        printf("\n");
    }
}

