/*  Author:         Fabiola Vilanueva
    Description:    Linked list of students to priority queue
    Date:           04/15/23
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 25

//structure definition
typedef char STRING[20];
typedef struct {
    STRING fName, lName;
    char IDnum[10];
    float grade;
} studType;
typedef struct node {
    studType data;
    struct node *link;
} *nodePtr;                 //linked list structure
typedef struct heap {
    studType *heapRec;
    int lastIdx;
} *HEAP;                    //priotrity queue structure

//function definitions
void initializeLL (nodePtr *L);
void initializeHeap (HEAP *H);

int main () {
    system ("cls");
    printf("\n<< START >>\n\n");

    nodePtr mL;
    HEAP mH;

    printf("< INITIALIZE >\n");
    initializeLL (&mL);
    initializeHeap (&mH);
    if (mL == NULL && mH != NULL) {
        printf("\tLinked list and Heap initialized successfully.\n");
    }



    printf("\n<< END >>\n");
    return 0;
}

void initializeLL (nodePtr *L) {
    *L = NULL;
}

void initializeHeap (HEAP *H) {
    *H = malloc (sizeof (struct heap));
    if (*H != NULL) {
        (*H)->heapRec = malloc (sizeof (studType) * MAX);
        (*H)->lastIdx = -1;
    }
}