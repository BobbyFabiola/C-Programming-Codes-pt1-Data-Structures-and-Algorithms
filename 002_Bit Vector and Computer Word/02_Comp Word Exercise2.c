/*  Author: Fabiola Villanueva
    Description: Computer Word Exercise from PPT (First Hands-On)
    Date: Oct 08, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned char SET;
typedef enum {FALSE, TRUE} Bool;

//function prototypes
void displayElems (SET X);
void displayBits (SET X);
void initSet (SET *X);
void insertAt (SET *X, int pos);
Bool isMember (SET X, int pos);
void deleteAt (SET *X, int pos);
void unionSets (SET X, SET Y, SET *Z);
void intersectionSets (SET X, SET Y, SET *Z);
void differenceSets (SET X, SET Y, SET *Z);

int main() {
    system("CLS");
    SET mA, mB, mC;
    int pos;
    
    printf("0. Initialize Set\n");
    initSet (&mA);
    displayBits (mA);
    displayElems (mA);

    printf("\n0.1 Set Value\n");
    printf("\tValue: ");
    scanf("%hhu", &mA);             //conversion type for usigned char
    displayBits (mA);
    displayElems (mA);

    printf("\n1. Insert At");
    do {
        printf("\n\tPos: ");
        scanf("%d", &pos);
        if (pos >= (sizeof(SET) * 8)) {
            printf("\tInvalid position. Only input range from 0 to %d.\n", sizeof(SET) * 8);
        }
    } while (pos >= sizeof(SET) * 8);
    insertAt (&mA, pos);
    printf("\tBit inserted at [%d].\n", pos);
    displayBits (mA);
    displayElems (mA);

    printf("\n2. Is Member");
    do {
        printf("\n\tPos: ");
        scanf("%d", &pos);
        if (pos >= (sizeof(SET) * 8)) {
            printf("\tInvalid position. Only input range from 0 to %d.\n", sizeof(SET) * 8);
        }
    } while (pos >= sizeof(SET) * 8);
    if (isMember (mA, pos)) {
        printf("\tBit at pos [%d] is a member.\n", pos);
    } else {
        printf("\tBit at pos [%d] is NOT a member.\n", pos);
    }

    printf("\n3. Delete At");
    do {
        printf("\n\tPos: ");
        scanf("%d", &pos);
        if (pos >= (sizeof(SET) * 8)) {
            printf("\tInvalid position. Only input range from 0 to %d.\n", sizeof(SET) * 8);
        }
    } while (pos >= sizeof(SET) * 8);
    printf("\n\t(Before)\n");
    displayBits (mA);
    deleteAt (&mA, pos);
    printf("\n\t(After)\n");
    displayBits (mA);
    displayElems (mA);

    printf("\n<< UID Operations >>\n");
    printf("\tInput values for sets:\n");
    printf("\tSET X = ");
    scanf("%hhu", &mA);
    printf("\tSET Y = ");
    scanf("%hhu", &mB);

    printf("\n");
    displayBits (mA);
    displayElems (mA);
    printf("\n");
    displayBits (mB);
    displayElems (mB);
    
    printf("\n4. Union of Sets\n\t(A | B)\n");
    unionSets (mA, mB, &mC);
    displayBits (mA);
    displayBits (mB);
    displayBits (mC);

    printf("\n5. Instersection of Sets\n\t(A & B)\n");
    intersectionSets (mA, mB, &mC);
    displayBits (mA);
    displayBits (mB);
    displayBits (mC);

    printf("\n6. Difference of Sets\n\t(A ^ B)\n");
    differenceSets (mA, mB, &mC);
    displayBits (mA);
    displayBits (mB);
    displayBits (mC);
    

    printf("\n");
    return 0;
}

//function definitions arranged from ppt list
//0. initialize set to zero
void initSet (SET *X) {
    *X = 0;     //initializes passed variable to zero   
}

//0.1
void displayElems (SET X) {
    SET mask = sizeof(SET) * 8;                             //mask "traverses" each bit in out set  
    int i = (sizeof(SET) * 8) - 1;                                              //elem counter
    printf("\n\tIndex for %hhu = ", X);
    for (mask = 1 << i; mask > 0; mask >>= 1, --i) {        //for loop traverses and displays indices
        if (X & mask) {
            printf("[%3d] ", i);
        } else {
            printf("[   ] ");
        }
    }
    printf("\n\tElems for %hhu = ", X);
    for (i = (sizeof(SET) * 8) - 1, mask = 1 << i; mask > 0; mask >>= 1, --i) { //for loop traverses and displays elements
        if (X & mask) {
            printf("[%3d] ", (int) pow (2, i));
        } else {
            printf("[   ] ");
        }
    }
    printf("\n");
}

//1. displaying one set
void displayBits (SET X) {
    SET mask = sizeof (SET) * 8;                            //mask "traverses" each bit of the set
    printf("\t%3hhu = ", X);                                //value of set
    for (mask = 1 << mask - 1; mask > 0; mask >>= 1) {      //bit representation of set for loop condition
        printf("%2d", (X & mask)? 1: 0);                    //bit-by-bit printing of set's binary value
    }
    printf("\n");
}

//2. insert bit at position
void insertAt (SET *X, int pos) {
    (*X) |= 1 << pos;                                       //add 1 by shifting "mask" pos number of times via bitwise OR
}

//3. is position a member?
Bool isMember (SET X, int pos) {
    return (X & (1 << pos))? TRUE: FALSE;                   //checks if bit at position is 1 or 0
}

void deleteAt (SET *X, int pos) {
    (*X) &= ~(1 << pos);                                    //shift the mask at pos, invert the mask value and evaluate bitwise &
}

void unionSets (SET X, SET Y, SET *Z) {
    *Z = X | Y;                                             //*Z will get all elements of X and Y
}

void intersectionSets (SET X, SET Y, SET *Z) {
    *Z = X & Y;                                             //*Z will get all common elements of X and Y
}

void differenceSets (SET X, SET Y, SET *Z) {
    *Z = X ^ Y;                                             //*Z will get unique elements from both X and Y
}