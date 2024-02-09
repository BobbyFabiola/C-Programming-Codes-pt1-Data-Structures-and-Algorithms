//*   Author:        Fabiola C. Villanueva
//*   Description:   ArrayList Version 01 (Hard Coded)
//*   Date:          January 08, 2024

#include <stdio.h>
#include <stdlib.h>
#define SIZE 0XF                                                    //15

typedef enum {FALSE, TRUE} BOOL;

typedef struct {
   char letters[SIZE];
   int count;
} arrayList;

BOOL initialize (arrayList *L);
void display (arrayList L);
void insertRear (arrayList *L, char elem);
void insertFront (arrayList *L, char elem);
void insertSorted (arrayList *L, char elem);
int searching (arrayList L, char elem);                             //return pos else -1
void deleteRear (arrayList *L);
void deleteFront (arrayList *L);
void deleteAt (arrayList *L, int pos);

int main () {
    system ("cls");
    arrayList myL;

    printf("\n<< 0. Initialize >>\n");
    if (initialize (&myL)) {
        printf("\tArray List successfully initialized.\n");
    }

    printf("\n<< 1. Insert Rear >>\n");
    insertRear (&myL, 'D');
    insertRear (&myL, 'E');
    insertRear (&myL, 'F');
    display (myL);

    printf("\n<< 2. Insert Front >>\n");
    insertFront (&myL, 'G');
    insertFront (&myL, 'H');
    display (myL);

    printf("\n<< 3. Insert Sorted >>\n");
    insertSorted (&myL, 'A');
    insertSorted (&myL, 'B');
    insertSorted (&myL, 'C');
    display (myL);

    printf("\n<< 4. Search Elem >>\n");
    printf("\t(returns pos of elem if found; -1 if not found)\n");
    printf("\tSearch element 'A' = %d\n", searching (myL, 'A'));
    printf("\tSearch element 'Z' = %d\n", searching (myL, 'Z'));
    printf("\tSearch element 'W' = %d\n", searching (myL, 'W'));
    printf("\tSearch element 'F' = %d\n", searching (myL, 'F'));
    printf("\tSearch element 'G' = %d\n", searching (myL, 'G'));

    printf("\n<< 5. Delete Rear >>\n");
    deleteRear (&myL);
    display (myL);
    deleteRear (&myL);
    display (myL);

    printf("\n<< 6. Delete Front >>\n");
    deleteFront (&myL);
    display (myL);
    deleteFront (&myL);
    display (myL);

    printf("\n<< 7. Delete At >>\n");
    printf("\tPos = 4\n");
    deleteAt (&myL, 4);
    display (myL);
    printf("\tPos = 2\n");
    deleteAt (&myL, 2);
    display (myL);

    printf("\n");
    return 0;
}

BOOL initialize (arrayList *L) {
   L->count = 0;
   return (L->count == 0) ? TRUE: FALSE;
}

void display (arrayList L) {
    int i;
    printf("\t// Display Array List\n\t{");
    for (i = 0; i < L.count; ++i) {
        printf("%c", L.letters[i]);
        if (i < L.count-1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void insertRear (arrayList *L, char elem) {
    if (L->count < SIZE) {
        L->letters [L->count++] = elem;                             //insert at index count then increment
    }
}

void insertFront (arrayList *L, char elem) {
    int i;
    if (L->count < SIZE) {
        for (i = L->count; i > 0; --i) {                            //shifting all elements to the right
            L->letters[i] = L->letters[i-1];
        }
        L->letters[0] = elem;                                       //insert at index 0
        ++L->count;
    }
}

void insertSorted (arrayList *L, char elem) {
    int i, j;
    if (L->count < SIZE) {
        for (i = 0; i < L->count && L->letters[i] < elem; ++i) {}   //i is now index where to insert
        for (j = L->count; j > i; --j) {                            //shifting to right to make i empty cell
            L->letters[j] = L->letters[j-1];
        }
        L->letters[i] = elem;
        ++L->count;
    }
}

int searching (arrayList L, char elem) {
    int i, pos = -1;
    for (i = 0; i < L.count && pos == -1; ++i) {
        if (L.letters[i] == elem) {
            pos = i;
        }
    }
    return pos;
}

void deleteRear (arrayList *L) {
    if (L->count > 0) {                                             //if there are elements to delete
        --L->count;
    } else {
        printf("\tThere are no more elements to delete.");
    }
}

void deleteFront (arrayList *L) {
    int i;
    if (L->count > 0) {
        for (i = 0; i < L->count; ++i) {
            L->letters[i] = L->letters[i+1];
        }
        --L->count;
    } else {
        printf("\tThere are no more elements to delete.");
    }
}

void deleteAt (arrayList *L, int pos) {
    int i;
    if (pos < L->count) {
        for (i = pos; i < L->count; ++i) {
            L->letters[i] = L->letters[i+1];
        }
        --L->count;
    } else {
        printf("\tCouldn't delete. Pos is off-bounds.\n");
    }
}