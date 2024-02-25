/*  Author:         Fabioila C. Villanueva
    Description:    exploring SETS of various datatypes and sizes 
    Date: Feb 22, 2o24
*/

#include <stdio.h>
#include <stdlib.h>

//function prototypes: CRUD and UID
void displayBits (char S);
void insertFront (SET *S);
// void insertRear (SET *);
// void insertAt (SET *);
// void deleteFront (SET *);
// void deleteRear (SET *);
// void deleteAt (SET *);
// SET *myUnion (SET, SET);
// SET *myIntersection (SET, SET);
// SET *myDifference (SET, SET);

int main () {
    system("cls");
    char girl = 'F';
    char boy = 'f';

    printf("01. DISPLAY BITS OF SETS\n");
    printf("\tG = ");
    displayBits (girl);
    printf("\n\tB = ");
    displayBits (boy);

    printf("\n02. INSERT FRONT");




    printf("\n");
    return 0;
}

void displayBits (char S) {
    int ctr;
    unsigned char mask = 1 << (sizeof(char) * 8 - 1);
    for (ctr = 1; mask > 0; mask >>= 1, ++ctr) {
        printf("%d", ((S & mask) != 0)? 1: 0);
        if (ctr % 8 == 0) {
            printf(" ");
        }
    }
}

void insertFront (SET *S) {
    
}