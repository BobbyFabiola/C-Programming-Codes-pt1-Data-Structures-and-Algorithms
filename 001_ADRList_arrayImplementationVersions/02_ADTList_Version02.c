/*  Author: Fabiola C. VIllanueva
 *  Discription: ADT List Version 2 - via hard code (fin)
 *  Date: Aug 31, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

//structure definition
typedef struct list {
    int elem[MAX];
    int count;
} *listPtr;

//function prototypes
void initialize (listPtr *L);
void displayList (listPtr L);
void insertFront (listPtr L, int new);
void insertRear (listPtr L, int new);
void insertAtPos (listPtr L, int new, int pos);
void updateAtPos (listPtr L, int new, int pos);
int retrieveAtPos (listPtr L, int pos);
void deleteFront (listPtr L);
void deleteRear (listPtr L);
void deleteAtPos (listPtr L, int pos);

int main() {
    system("CLS");

    listPtr List;
    int num;

    printf("< Initialize >\n");
    initialize (&List);
    displayList (List);

    printf("< Insert Front >\n");
    insertFront (List, 10);
    insertFront (List, 11);
    insertFront (List, 12);
    displayList (List);

    printf("< Insert Rear >\n");
    insertRear (List, 20);
    insertRear (List, 21);
    insertRear (List, 22);
    displayList (List);
    
    printf("< Insert At Pos >\n");
    insertAtPos (List, 30, 1);
    insertAtPos (List, 31, 11);
    insertAtPos (List, 32, 6);
    displayList (List);

    printf("< Update At Pos >\n");
    updateAtPos (List, 40, 1);
    updateAtPos (List, 41, 5);
    updateAtPos (List, 42, 10);     //does not displayList bc pos is greater than count
    displayList (List);
    
    printf("< Retrieve at Pos >\n");
    printf("Input position: ");
    scanf("%d", &num);
    printf("Element at [%d] = %d\n\n", num, retrieveAtPos(List, num));

    printf("< Delete Front >\n");
    deleteFront (List);
    displayList (List);

    printf("< Delete Rear >\n");
    deleteRear (List);
    displayList (List);

    printf("< Delete At Pos >\n");
    printf("Input position: ");
    scanf("%d", &num);
    deleteAtPos (List, num);
    displayList (List);

    return 0;
}

//function definitions
void initialize (listPtr *L) {
    (*L) = calloc (1, sizeof (struct list));
    if ((*L) != NULL) {
        (*L)->count = 0;
    }
}

void displayList (listPtr L) {
    int i;

    printf("Elements = {");
    for (i = 0; i < L->count; ++i) {
        printf("%d", L->elem[i]);
        if (i < (L->count - 1)) {
            printf(", ");
        }
    }
    printf("}\n");
    printf("Count = %d\n\n", L->count);
}

void insertFront (listPtr L, int new) {
    if (L->count < MAX) {
        memcpy (L->elem + 1, L->elem, sizeof (int) * (L->count));

        L->elem[0] = new;
        ++(L->count);
    }
}

void insertRear (listPtr L, int new) {
    if (L->count < MAX) {
        L->elem[L->count++] = new;
    }
}

void insertAtPos (listPtr L, int new, int pos) {
    int i;
    if (L->count < MAX) {
        for (i = 0; i < L->count && i < pos; ++i) {}                            //considers case where pos is greater than count,then insert rear
        memcpy (L->elem + i + 1, L->elem + i, sizeof (int) * (L->count - i));

        L->elem[i] = new;
        ++(L->count);
    }
}

void updateAtPos (listPtr L, int new, int pos) {
    if (pos < L->count) {
        L->elem[pos] = new;
    }
}

int retrieveAtPos (listPtr L, int pos) {
    return (pos < L->count) ? L->elem[pos] : -1;
}

void deleteFront (listPtr L) {
    memcpy (L->elem, L->elem + 1, sizeof (int) * (L->count -1));
    --(L->count);
}

void deleteRear (listPtr L) {
    --(L->count);
}

void deleteAtPos (listPtr L, int pos) {
    if (pos < L->count) {
        memcpy (L->elem + pos, L->elem + pos + 1, sizeof (int) * (L->count - pos));
        --(L->count);
    }
}