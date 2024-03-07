/*  Author:         Fabioila C. Villanueva
    Description:    exploring SETS of various datatypes and sizes 
    Date: Feb 22, 2o24
*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char SET;                  //logical

//function prototypes: CRUD and UID
void displayBits (SET S);
void insertFront (SET *S);
void insertRear (SET *S);
void insertAt (SET *S, int pos);
void deleteFront (SET *S);
void deleteRear (SET *S);
void deleteAt (SET *S, int pos);
SET myUnion (SET a, SET b);
SET myIntersection (SET a, SET b);
SET myDifference (SET a, SET b);

int main () {
    system("cls");
    SET x = 100;
    SET y = 50;
    SET w, v;

    printf("<< START >>\n\n");
    printf("01. DISPLAY BITS OF SETS\n");
    printf("\t[%3d] = ", x);
    displayBits (x);
    printf("\n\t[%3d] = ", y);
    displayBits (y);

    printf("\n02. INSERT FRONT\n");
    insertFront (&x);
    printf("\t[%3d] = ", x);
    displayBits (x);
    insertFront (&y);
    printf("\n\t[%3d] = ", y);
    displayBits (y);

    printf("\n03. INSERT REAR\n");
    insertRear (&x);
    printf("\t[%3d] = ", x);
    displayBits (x);
    insertRear (&y);
    printf("\n\t[%3d] = ", y);
    displayBits (y);

    printf("\n04. INSERT AT\n");
    insertAt (&x, 4);
    printf("\t[%3d] = ", x);
    displayBits (x);
    insertAt (&y, 6);
    printf("\n\t[%3d] = ", y);
    displayBits (y);

    printf("\n05. DELETE FRONT\n");
    deleteFront (&x);
    printf("\t[%3d] = ", x);
    displayBits (x);
    deleteFront (&y);
    printf("\n\t[%3d] = ", y);
    displayBits (y);

    printf("\n06. DELETE REAR\n");
    deleteRear (&x);
    printf("\t[%3d] = ", x);
    displayBits (x);
    deleteRear (&y);
    printf("\n\t[%3d] = ", y);
    displayBits (y);

    printf("\n07. DELETE AT\n");
    deleteAt (&x, 3);
    printf("\t[%3d] = ", x);
    displayBits (x);
    deleteAt (&y, 5);
    printf("\n\t[%3d] = ", y);
    displayBits (y);

    printf("\n08. UNION OF SETS\n");
    w = myUnion (x, y);
    printf("\t[%3d] = ", w);
    displayBits (w);

    printf("\n09. INTERSECTION OF SETS\n");
    w = myIntersection (x, y);
    printf("\t[%3d] = ", w);
    displayBits (w);

    printf("\n10. DIFFERENCE OF SETS\n");
    w = myDifference (x, y);
    printf("\t[%3d] = ", w);
    displayBits (w);
    v = myDifference (y, x);
    printf("\n\t[%3d] = ", v);
    displayBits (v);


    printf("\n\n<< END >>\n");
    return 0;
}

void displayBits (SET S) {
    int ctr;
    SET mask = 1 << (sizeof(SET) * 8 - 1);
    for (ctr = 1; mask > 0; mask >>= 1, ++ctr) {
        printf("%u", ((S & mask) != 0)? 1: 0);
        if (ctr % 8 == 0) {
            printf(" ");
        }
    }
}

void insertFront (SET *S) {
    SET mask = 1 << (sizeof (SET) * 8 - 1);
    *S = (*S) | mask;
}

void insertRear (SET *S) {
    SET mask = 1;
    *S = (*S) | mask;
}

void insertAt (SET *S, int pos) {
    SET mask = 1 << (pos-1);
    *S = (*S) | mask;
}

void deleteFront (SET *S) {
    SET mask = 1 << (sizeof (SET) * 8 - 1);
    *S = (*S) & (~mask);
}

void deleteRear (SET *S) {
    SET mask = 1;
    *S = (*S) &  (~mask);
}

void deleteAt (SET *S, int pos) {
    SET mask = 1 << (pos-1);
    *S = (*S) & (~mask);
}

SET myUnion (SET a, SET b) {
    SET c = a | b;
    return c;
}

SET myIntersection (SET a, SET b) {     //common between the sets
    SET c = a & b;
    return c;
}

SET myDifference (SET a, SET b) {       //a-b == unique elements in a that are not in b == NAND
    SET c = a & (~b);
    return c;
}