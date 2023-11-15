/*  Author: Fabiola C. Villanueva
 *  Description: ADT List Version 1 - via hard code (fin)
 *  Date: Sep 02, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

//structure definition
typedef struct {
    int elem[MAX];
    int count;
} LIST;

//function prototypes
void initialize (LIST *L);
void displayList (LIST L);
void insertFront (LIST *L, int new);
void insertRear (LIST  *L, int new);
void insertAtPos (LIST *L, int new, int pos);
void updateAtPos (LIST *L, int new, int pos);
int retreiveAtPos (LIST L, int pos);
void deleteFront (LIST *L);
void deleteRear (LIST *L);
void deleteAtPos (LIST *L, int pos);

int main() {
    system("CLS");

    LIST myList;
    int num;

    printf("< Initialize >\n");
    initialize (&myList);
    displayList (myList);

    printf("< Insert Front >\n");
    insertFront (&myList, 100);
    insertFront (&myList, 101);
    displayList (myList);

    printf("< Insert Rear >\n");
    insertRear (&myList, 200);
    insertRear (&myList, 202);
    displayList (myList);

    printf("< Insert At Pos >\n");
    insertAtPos (&myList, 111, 2);
    insertAtPos (&myList, 222, 0);
    displayList (myList);

    printf("< Update At Pos >\n");
    updateAtPos (&myList, 505, 5);
    updateAtPos (&myList, 501, 1);
    updateAtPos (&myList, 506, 6);  //does not update, pos is greater than count
    displayList (myList);

    printf("< Retreive At Pos >\n");
    printf("Input position: ");
    scanf("%d", &num);
    printf("Element at [%d] = %d\n\n", num, retreiveAtPos (myList, num));
    
    printf("< Delete Front >\n");
    deleteFront (&myList);
    displayList (myList);

    printf("< Delete Rear >\n");
    deleteRear (&myList);
    displayList (myList);

    printf("< Delete At Pos >\n");
    printf("Input position: ");
    scanf("%d", &num);
    deleteAtPos (&myList, num);
    displayList (myList);

    return 0;
}

//function definitions
void initialize (LIST *L) {
    L->count = 0;
}

void displayList (LIST L) {
    int i;
    printf("Elements = {");
    for (i = 0; i < L.count; ++i) {
        printf("%d", L.elem[i]);
        if (i < (L.count-1)) {
            printf(", ");
        }
    }
    printf("}\n");
    printf("Count = %d\n\n", L.count);
}

void insertFront (LIST *L, int new) {
    if (L->count < MAX) {
        memcpy (L->elem + 1, L->elem, sizeof (int) * L->count);
        L->elem[0] = new;
        ++(L->count);
    }
}

void insertRear (LIST  *L, int new) {
    if (L->count < MAX) {
        L->elem[L->count++] = new;
    }
}

void insertAtPos (LIST *L, int new, int pos) {
    int i;
    if (L->count < MAX) {
        for (i = 0; i < L->count && i < pos; ++i) {}
        memcpy (L->elem + i + 1, L->elem + i, sizeof (int) * (L->count - i));
        L->elem[i] = new;
        ++(L->count);
    }
}

void updateAtPos (LIST *L, int new, int pos) {
    if (pos < L->count) {
        L->elem[pos] = new;
    }
}

int retreiveAtPos (LIST L, int pos) {
    return (pos < L.count) ? L.elem[pos] : -1;
}

void deleteFront (LIST *L) {
    memcpy (L->elem, L->elem + 1, sizeof (int) * (--L->count));
}

void deleteRear (LIST *L) {
    --(L->count);
}

void deleteAtPos (LIST *L, int pos) {
    if (pos < L->count) {
        memcpy (L->elem + pos, L->elem + pos + 1, sizeof (int) * (L->count - pos));
        --(L->count);
    }
}