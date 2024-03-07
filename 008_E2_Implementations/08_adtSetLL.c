/*  Author:         Fabioila C. Villanueva
    Description:    Sets in Linked Lists (unsorted & sorted)
    Date:           Mar 06, 2024
*/

#include <stdio.h>
#include <stdlib.h>

//structure definition
typedef struct node {
    int data;
    struct node *link;
} *SETLINK;

//function prototypes
SETLINK createList (int arr[]);
void displaySet (SETLINK SL);
void updateSet (SETLINK SL, int num);
SETLINK myUnion (SETLINK A, SETLINK B);
SETLINK myIntersection (SETLINK A, SETLINK B);

int main () {
    system ("cls");
    int arrA[] = {5,4,9,3,1,10,22};
    int arrB[] = {12,3,4,5,10,10,99};
    SETLINK mSET_A = NULL, mSET_B = NULL, UID = NULL;

    printf("00 Array Set to Link Set\n");
    printf("\tLL SET_A = ");
    mSET_A = createList (arrA);
    displaySet (mSET_A);
    printf("\tLL SET_B = ");
    mSET_B = createList (arrB);
    displaySet (mSET_B);

    printf("00 Update/Delete Set\n");
    updateSet (mSET_A, 10);
    printf("\tLL SET_A = ");
    displaySet (mSET_A);
    printf("\tLL SET_B = ");
    displaySet (mSET_B);

    printf("00 Union of Sets A and B\n");
    UID = myUnion (mSET_A, mSET_B);
    printf("\tLL UNION = ");
    displaySet (UID);

    printf("00 Union of Sets A and B\n");
    UID = myIntersection (mSET_A, mSET_B);
    printf("\tLL INTER = ");
    displaySet (UID);
    
    printf("\n\n");
    return 0;
}

//function defintions
SETLINK createList (int arr[]) {                    //return the address of the first node
    SETLINK newList = NULL, temp;
    int x;
    for (x = 0; x < 7; ++x) {
        temp = (SETLINK) malloc (sizeof (struct node));
        if (temp !=  NULL) {
            temp->data = arr[x];
            temp->link = newList;
            newList = temp;
        }
    }
    return newList;
}

void displaySet (SETLINK SL) {
    printf("[");
    for (; SL != NULL; SL = SL->link) {
        printf("%4d", SL->data);
    }
    printf("  ]\n");
}

void updateSet (SETLINK SL, int num) {              //update the set's node to -99 if num is found
    for (; SL != NULL && SL->data != num; SL = SL->link) {}
    if (SL != NULL) {
        SL->data = -99;
    }
}

// SETLINK myUnion (SETLINK A, SETLINK B) {
//     SETLINK newList = NULL, travA, travB, temp;
//     for (travA = A; travA != NULL; travA = travA->link) {
//         for (travB = B; travB != NULL && travB->data != travA->data; travB = travB->link) {}
//         if (travB == NULL) { //then element is unique
//             temp = malloc (sizeof (struct node));
//             if (temp != NULL) {
//                 temp->data = travA->data;
//                 temp->link = newList;
//                 newList = temp;
//             }
//         }
//     }
//     for (; B != NULL;  B = B->link) {
//         temp = malloc (sizeof (struct node));
//         if (temp != NULL) {
//             temp->data = B->data;
//             temp->link = newList;
//             newList = temp;
//         }
//     }
//     return newList;
// }

// SETLINK myIntersection (SETLINK A, SETLINK B) {
//     SETLINK newList = NULL, temp, travA, travB;
//     for (travA = A; travA != NULL; travA = travA->link) {
//         for (travB = B; travB != NULL && travB->data != travA->data; travB = travB->link) {}
//         if (travB != NULL) {
//             temp = malloc (sizeof (struct node));
//             temp->data = travA->data;
//             temp->link = newList;
//             newList = temp;
//         }
//     }
//     for (travB = A; travB != NULL; travB = travB->link) {
//         for (travA = A; travA != NULL && travA->data != travB->data; travA = travA->link) {}
//         if (travB != NULL) {
//             temp = malloc (sizeof (struct node));
//             temp->data = travB->data;
//             temp->link = newList;
//             newList = temp;
//         }
//     }
//     return newList;
// }