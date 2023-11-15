/*  Author: Fabiola C. VIllanueva
 *  Discription: ADT List Version 4 - via hard code (fin)
 *  Date: Sep 03, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

//structure defintion
typedef struct list {
    int *elemPtr;
    int count;
} *LISTPTR;

//function prototypes
void initialize (LISTPTR *L);
void displayList (LISTPTR L);
void insertFront (LISTPTR * L, int new);
void insertRear (LISTPTR *L, int new);
void insertAtPos (LISTPTR *L, int new, int pos);
void updateAtPos (LISTPTR *L, int new, int pos);
int retreiveAtPos (LISTPTR L, int pos);
void deleteFront (LISTPTR *L);
void deleteRear (LISTPTR *L);
void deleteAtPos (LISTPTR *L, int pos);

int main() {
    system("CLS");

    LISTPTR arrList;
    int num;

    printf("< Initialize >\n");
    initialize (&arrList);
    displayList (arrList);

    printf("< Insert Front >\n");
    insertFront (&arrList, 100);
    insertFront (&arrList, 101);
    displayList (arrList);

    printf("< Insert Rear >\n");
    insertRear (&arrList, 200);
    insertRear (&arrList, 201);
    displayList (arrList);

    printf("< Insert At Pos >\n");
    insertAtPos (&arrList, 300, 1);
    insertAtPos (&arrList, 301, 8);
    displayList (arrList);

    printf("< Retrieve at Pos >\n");
    printf("Input position: ");
    scanf("%d", &num);
    printf("Element at [%d] = %d\n\n", num, retreiveAtPos(arrList, num));

    printf("< Delete Front >\n");
    deleteFront (&arrList);
    displayList (arrList);

    printf("< Delete Rear >\n");
    deleteRear (&arrList);
    displayList (arrList);

    printf("< Delete At Pos >\n");
    printf("Input position: ");
    scanf("%d", &num);
    deleteAtPos (&arrList, num);
    displayList (arrList);

    return 0;
}

//function definitions
void initialize (LISTPTR *L) {
    (*L) = calloc (1, sizeof (struct list));
    if ((*L) != NULL) {
        (*L)->elemPtr = calloc (MAX, sizeof (int));
        (*L)->count = 0;
    }
}

void displayList (LISTPTR L) {
    int i;

    printf("Elements = {");
    for (i = 0; i < L->count; ++i) {
        printf("%d", L->elemPtr[i]);
        if (i < (L->count - 1)) {
            printf(", ");
        }
    }
    printf("}\n");
    printf("Count = %d\n\n", L->count);
}

void insertFront (LISTPTR * L, int new) {
    if ((*L)->count < MAX) {
        memcpy ((*L)->elemPtr + 1, (*L)->elemPtr, sizeof (int) * ((*L)->count++));
        (*L)->elemPtr[0] = new;
    }
}

void insertRear (LISTPTR *L, int new) {
    if ((*L)->count < MAX) {
        (*L)->elemPtr[(*L)->count++] = new;
    }
}

void insertAtPos (LISTPTR *L, int new, int pos) {
    int i;

    for (i = 0; i < (*L)->count && i < pos; ++i) {}
    memcpy ((*L)->elemPtr + i + 1, (*L)->elemPtr + i, sizeof (int) * ((*L)->count - i));
    (*L)->elemPtr[i] = new;
    ++((*L)->count);
}

void updateAtPos (LISTPTR *L, int new, int pos) {
    if (pos < ((*L)->count)) {
        (*L)->elemPtr[pos] = new;
    }
}

int retreiveAtPos (LISTPTR L, int pos) {
    return (pos < L->count) ? L->elemPtr[pos] : -1;
}

void deleteFront (LISTPTR *L) {
    memcpy ((*L)->elemPtr, (*L)->elemPtr + 1, sizeof (int) * (--(*L)->count));
}

void deleteRear (LISTPTR *L) {
    --((*L)->count);
}

void deleteAtPos (LISTPTR *L, int pos) {
    if (pos < (*L)->count) {
        memcpy ((*L)->elemPtr + pos, (*L)->elemPtr + pos + 1, sizeof (int) * ((*L)->count - pos));
        --((*L)->count);
    }
}