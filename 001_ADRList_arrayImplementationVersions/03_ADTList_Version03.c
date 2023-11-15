/*  Author: Fabiola C. VIllanueva
 *  Discription: ADT List Version 3 - via hard code (fin)
 *  Date: Sep 02, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

//structure definition
typedef struct {
    int *elemPtr;
    int count;
} LIST;

//function prototypes
void initialize (LIST *L);
void insertFront (LIST *L, int new);
void insertRear (LIST *L, int new);
void insertAtPos (LIST *L, int new, int pos);
void displayList (LIST L);
void updateAtPos (LIST *L, int new, int pos);
int retreiveAtPos (LIST L, int pos);
void deleteFront (LIST *L);
void deleteRear (LIST *L);
void deleteAtPos (LIST *L, int pos);

int main() {
    system("CLS");

    LIST mainList;
    int num;

    printf("< Initialize >\n");
    initialize (&mainList);
    displayList (mainList);

    printf("< Insert Front >\n");
    insertFront (&mainList, 11);
    insertFront (&mainList, 22);
    displayList (mainList);

    printf("< Insert Rear >\n");
    insertRear (&mainList, 33);
    insertRear (&mainList, 44);
    displayList (mainList);

    printf("< Insert At Pos >\n");
    insertAtPos (&mainList, 55, 1);
    insertAtPos (&mainList, 55, 7);
    displayList (mainList);

    printf("< Retrieve at Pos >\n");
    printf("Input position: ");
    scanf("%d", &num);
    printf("Element at [%d] = %d\n\n", num, retreiveAtPos(mainList, num));

    printf("< Delete Front >\n");
    deleteFront (&mainList);
    displayList (mainList);

    printf("< Delete Rear >\n");
    deleteRear (&mainList);
    displayList (mainList);

    printf("< Delete At Pos >\n");
    printf("Input position: ");
    scanf("%d", &num);
    deleteAtPos (&mainList, num);
    displayList (mainList);

    return 0;
}

//function defintions
void initialize (LIST *L) {
    L->elemPtr = calloc (MAX, sizeof (int));        //initializing my array in heap
    if (L->elemPtr != NULL) {
        L->count = 0;                               //intializing my counter
    }
}

void insertFront (LIST *L, int new) {
    if (L->count < MAX) {
        memcpy (L->elemPtr + 1, L->elemPtr, sizeof (int) * (L->count++));
        L->elemPtr[0] = new;
    }
}

void insertRear (LIST *L, int new) {
    if (L->count < MAX) {
        L->elemPtr[L->count++] = new;
    }
}

void insertAtPos (LIST *L, int new, int pos) {
    int i;
    if (L->count < MAX) {
        for (i = 0; i < L->count && i < pos; ++i) {}
        memcpy (L->elemPtr + i + 1, L->elemPtr + i, sizeof (int) * (L->count - i));
        L->elemPtr[i] = new;
        ++(L->count);
    }
}

void displayList (LIST L) {
    int i;

    printf("Elements = {");
    for (i = 0; i < L.count; ++i) {
        printf("%d", L.elemPtr[i]);
        if (i < (L.count - 1)) {
            printf(", ");
        }
    }
    printf("}\n");
    printf("Count = %d\n\n", L.count);
}

void updateAtPos (LIST *L, int new, int pos) {
    if (pos < L->count) {
        L->elemPtr[pos] = new;
    }
}

int retreiveAtPos (LIST L, int pos) {
    return (pos < L.count) ? L.elemPtr[pos] : -1;
}

void deleteFront (LIST *L) {
    memcpy (L->elemPtr,  L->elemPtr + 1, sizeof (int) * (--(L->count)));
}

void deleteRear (LIST *L) {
    --(L->count);
}

void deleteAtPos (LIST *L, int pos) {
    if (pos < L->count) {
        memcpy (L->elemPtr + pos, L->elemPtr + pos + 1, sizeof (int) * (L->count - pos));
        --(L->count);
    }
}