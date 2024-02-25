#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 0XA // 10


typedef struct {
    char FN[24];
    char LN[16];
    char MI;
}nametype;

typedef struct {
    char ID[10];
    nametype name;
    char course[8]; //BSCS, BSIS, BSIT
    int yrLevel;
}studRec;

/* Definition of List in Linked list and Array implementation */
typedef struct node {
    studRec stud;
    struct node *link;
}*StudLink;         //linked list data type defenition

typedef struct arr {
    studRec stud[MAX];
    int count;      //Number of element in the list
}StudArray;         //Array list data type defenition

typedef struct List {
    StudLink IT;    //BSIT list
    StudArray CS;   //BSCS list
}*ComboList;

/*
    Given a list sorted according to ID and implemented using linked list, write the code of the function createComboList(). The function will remove all BSCS and BSIT student records and put them in their respective list in the newly created ComboList and still retaining the sorted order of elements. The newly created ComboList will be returned to the calling function. [Hint: Copying the sorted list implemented using linked list to another sorted linked list does not need traversal every time an element is inserted].

    Note: Use the list datatypes whenever necessary, not their equivalents. The only functions that can be called/invoked are the functions in the C header files.
*/
StudLink populate();
void insertFirst(StudLink *S, studRec stud);
void displayLink(StudLink S);
void displayArr(StudArray S);
ComboList createComboList(StudLink *S);

int main() {
    system("cls");
    StudLink S = populate();
    printf("%35s\n", "[Current S Linked List]");
    displayLink(S);
    
    ComboList C = createComboList(&S);
    printf("After createComboList\n");

    // Uncomment after completing the function
    printf("%35s\n", "[Current S Linked List]");
    displayLink(S);
    printf("%34s\n", "[Current IT Linked List]");
    displayLink(C->IT);
    printf("%34s\n", "[Current CS Array List]");
    displayArr(C->CS);
}


StudLink populate(){
    int count = 10;
    studRec students[] = {
        {"010", {"Sophia", "Rodriguez", 'J'}, "BSIS", 1},
        {"009", {"James", "Garcia", 'I'}, "BSIT", 4},
        {"008", {"Olivia", "Martinez", 'H'}, "BSCS", 3},
        {"007", {"William", "Davis", 'G'}, "BSIS", 4},
        {"006", {"Emily", "Jones", 'F'}, "BSCS", 2},
        {"005", {"Michael", "Williams", 'E'}, "BSIT", 1},
        {"004", {"Bob", "Brown", 'D'}, "BSIS", 2},
        {"003", {"Alice", "Johnson", 'C'}, "BSCS", 3},
        {"002", {"Jane", "Smith", 'B'}, "BSIT", 2},
        {"001", {"John", "Doe", 'A'}, "BSCS", 1}
    };

    StudLink S = NULL;
    for(int i = 0; i < count; i++) {
        insertFirst(&S, students[i]);
    }

    return S;
}
void insertFirst(StudLink *S, studRec stud) {
    StudLink temp = malloc(sizeof(struct node));
    temp->stud = stud;
    temp->link = *S;
    *S = temp;
}
void displayLink(StudLink S) {
    printf("--------------------------------------------------------\n");
    printf("%-10s| %-20s| %-3s| %-8s| %-4s\n", "ID", "Name", "MI", "Course", "Year");
    for (;S != NULL; S = S->link) {
        printf("%-10s| %-20s| %-3c| %-8s| %-4d\n", S->stud.ID, strcat(strcat(S->stud.name.FN, " "), S->stud.name.LN), S->stud.name.MI, S->stud.course, S->stud.yrLevel);
    }
    printf("--------------------------------------------------------\n");
}
void displayArr(StudArray S) {
    printf("--------------------------------------------------------\n");
    printf("%-10s| %-20s| %-3s| %-8s| %-4s\n", "ID", "Name", "MI", "Course", "Year");
    for (int i = 0; i < S.count; i++) {
        printf("%-10s| %-20s| %-3c| %-8s| %-4d\n", S.stud[i].ID, strcat(strcat(S.stud[i].name.FN, " "), S.stud[i].name.LN), S.stud[i].name.MI, S.stud[i].course, S.stud[i].yrLevel);
    }
    printf("--------------------------------------------------------\n");
}

ComboList createComboList(StudLink *S) {
    //Complete the code
    StudLink *trav, *tail, temp;
    ComboList newCL = malloc (sizeof (struct List));

    if (newCL != NULL) {
        newCL->IT = NULL;
        tail = NULL;
        newCL->CS.count = 0;

        for (trav = S; *trav != NULL;) {
            if (strcmp ((*trav)->stud.course, "BSIT") == 0) {
                temp = *trav;
                *trav = temp->link;
                temp->link = NULL;
                (newCL->IT != NULL) ? ((*tail)->link = temp): (newCL->IT = temp);
                // if (newCL->IT != NULL) {
                //     (*tail)->link = temp;
                // } else {
                //     newCL->IT = temp;
                // }
                *tail = temp;
            } else if (strcmp ((*trav)->stud.course, "BSCS") == 0) {
                if (newCL->CS.count < MAX) {
                    temp = *trav;
                    newCL->CS.stud[newCL->CS.count++] = temp->stud;
                    *trav = temp->link;
                    free (temp);
                }
            } else {
                    trav = &(*trav)->link;
            }
        }
    }
    return newCL;
}