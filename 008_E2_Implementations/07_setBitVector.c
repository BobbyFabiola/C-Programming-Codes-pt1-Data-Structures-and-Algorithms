/*  Author:         Fabioila C. Villanueva
    Description:    Bit Vector / Boolean Array 
    Date:           Mar 04, 2024
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef int SET[MAX];

// function prototyes
SET *makeBitVector (int arr[]);
void displayVector (SET S);
void deletePos (SET S, int pos);
SET *myUnion (SET A, SET B);
SET *myIntersection (SET A, SET B);
SET *myDifference (SET A, SET B);

int main () {
    system("cls");
    int mArr[5] = {3, 2, 0, 8, 10};
    SET *mBV;                                       // arrB = arrC
    SET bvZ = {0,0,1,1,0,1,0,1,0};

    printf("00. Make Bit Vector (arr to bv)\n");
    printf("\tFrom integer array {3, 2, 5, 8, 10} to Bit Vector\n");
    mBV = makeBitVector (mArr);
    printf("\tSET mBV = ");
    displayVector (*mBV);

    printf("\n\n01. Delete Bits From the Bit Vector\n");
    deletePos (*mBV, 3);
    printf("\tSET mBV = ");
    displayVector (*mBV);
    deletePos (*mBV, 1);
    printf("\n\tSET mBV = ");
    displayVector (*mBV);

    printf("\n\n\t<< UID >>\n\tSET mBV = ");
    displayVector (*mBV);
    printf("\n\tSET bvZ = ");
    displayVector (bvZ);

    printf("\n\n02. Union of Two Sets\n");
    SET *F = myUnion (*mBV, bvZ);
    printf("\t  UNION = ");
    displayVector (*F);

    printf("\n\n03. Intersection of Two Sets\n");
    F = myIntersection (*mBV, bvZ);
    printf("\t  INTER = ");
    displayVector (*F);

    printf("\n\n04. Difference of Two Sets\n");
    F = myDifference ( bvZ, *mBV);
    printf("\t  DIFFERENCE = ");
    displayVector (*F);

    printf("\n\n");
    return 0;
}

// function definitions
SET *makeBitVector (int arr[]) {
    SET *temp = (SET *) calloc (MAX, (sizeof(SET) / MAX));
    if (temp != NULL)  {
        int x, idx;
        for (x = 0; x < 5; ++x) {
            idx = arr[x];
            if (idx < MAX) {
                (*temp)[idx] = 1;
            }
        }
    }
    return temp;
}

void displayVector (SET S) {
    int x;
    for (x = 0; x < MAX; ++x) {
        printf("%d", S[x]);
        if (x < MAX-1) {
            printf(" ");
        }
    }
}

void deletePos (SET S, int pos) {
    if (pos < MAX && pos >= 0) {
        S[pos-1] = 0;
    }
}

SET *myUnion (SET A, SET B) {
    SET *temp = (SET *) calloc (MAX, (sizeof(SET) / MAX));
    if (temp != NULL) {
        int x;
        for (x = 0; x < MAX; ++x) {
            if (A[x] == 1 || B[x] == 1) {
                (*temp)[x] = 1;
            }
        }
    }
    return temp;
}

SET *myIntersection (SET A, SET B) {
    SET *temp = (SET *) calloc (MAX, (sizeof(SET) / MAX));
    if (temp != NULL) {
        int x;
        for (x = 0; x < MAX; ++x) {
            if (A[x] == 1 && B[x] == 1) {
                (*temp)[x] = 1;
            }
        }
    }
    return temp;
}

SET *myDifference (SET A, SET B) {
     SET *temp = (SET *) calloc (MAX, (sizeof(SET) / MAX));
    if (temp != NULL) {
        int x;
        for (x = 0; x < MAX; ++x) {
            if (A[x] == 1 && B[x] == 0) {
                (*temp)[x] = 1;
            }
        }
    }
    return temp;
}