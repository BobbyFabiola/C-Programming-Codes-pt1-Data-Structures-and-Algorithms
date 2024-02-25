/*  Author: Fabiola Villanueva
    Description:   
        Remove the BSICT from the given linked list and move it into the    
        array in ascending order via last name; 
        populate linked list, move into array
    Date: Feb 24, 2024
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

//structure definition
typedef struct {
    char LN[16], FN[16], MI;
} nameType;

typedef struct {
    nameType name;
    char ID[10];
    int yrLevel;
    char course[8];
} studRec;

typedef struct node {                                                               //linked list definition
    studRec stud;
    struct node *sLink;
} *studLink;

typedef struct {                                                                    //array in heap (pointer to a structure)
    nameType names[MAX];
    int lastNdx;
} *studArr;

//function prototypes
void populateLL (studLink *L, studRec arr[]);
void displayLL (studLink L);
studArr removeBSICT (studLink *L);                                                 //return a pointer of the arrayList
void displayArray (studArr Arr);

int main () {
    system("cls");
    printf("<< START >>\n");
    studLink myList = NULL;
    studArr myArr;
    studRec arr[MAX] = {                                                            //array data to linked list
        {{"Rodriguez",  "Sophia",  'C'}, "22103326", 2, "BSICT"},
        {{"Garcia",     "James",   'A'}, "33193326", 4, "BSCS"},
        {{"Martinez",   "Olivia",  'D'}, "27183329", 2, "BS ADV"},
        {{"Davis",      "William", 'B'}, "22184457", 2, "BSICT"},
        {{"Jones",      "Emily",   'O'}, "77281932", 2, "BSCS"},
        {{"Williams",   "Michael", 'K'}, "33183326", 4, "BSCS"},
        {{"Brown",      "Bob",     'L'}, "77103382", 3, "BSICT"},
        {{"Johnson",    "Alice",   'M'}, "19173284", 3, "BSICT"},
        {{"Smith",      "Jane",    'Y'}, "62193274", 2, "BSCS"},
        {{"Doe",        "John",    'S'}, "81922103", 1, "BSICT"},
    };

    populateLL (&myList, arr);
    displayLL (myList);
    myArr = removeBSICT (&myList);                                                  //calling function gets the address to the arraylist
    displayArray (myArr);
    displayLL (myList);

    printf("\n\n<< END >>");
    return 0;
}

void populateLL (studLink *L, studRec arr[]) {
    studLink temp;
    int x;
    for (x = 0; x < MAX; ++x) {                                                     //traversing the array
        temp = malloc (sizeof (struct node));
        if (temp != NULL) {
            temp->stud = arr[x];
            temp->sLink = *L;
            *L = temp; 
        }
    }
}

void displayLL (studLink L) {
    printf("\n\tLINKED LIST OF STUDENTS\n");
    int x;
    for (x = 1; L != NULL; ++x, L = L->sLink) {
        printf("\t[%2d] %16s %16s %c. | %10s | %8s | %2d\n", 
                x, L->stud.name.LN, L->stud.name.FN, L->stud.name.MI, L->stud.ID, L->stud.course, L->stud.yrLevel);
    }
}

studArr removeBSICT (studLink *L) {
    studArr ICT = malloc ((sizeof (nameType) * MAX) + (sizeof (int)));
    if (ICT != NULL) {
        ICT->lastNdx = -1;
        studLink *trav, temp;
        for (trav = L; *trav != NULL;) {
            if (strcmp ((*trav)->stud.course, "BSICT") == 0) {      //ICT->lastNdx != MAX-1
                if (ICT->lastNdx != MAX-1) {                        //if not full
                    int x, n;                                       //insertSorted
                    for (x = 0; x <= ICT->lastNdx && strcmp (ICT->names[x].LN, (*trav)->stud.name.LN) < 0; ++x) {}
                    for (n = ICT->lastNdx; n >= x; --n) {
                        ICT->names[n+1] = ICT->names[n];
                    }
                    ICT->names[x] = (*trav)->stud.name;             //x is exact index to insert
                    ICT->lastNdx++;
                }
                temp = *trav;
                *trav = temp->sLink;
                free(temp);
            } else {
                trav = &(*trav)->sLink;
            }
        }
    }
    return ICT;
}

void displayArray (studArr Arr) {
    printf("\n\tARRAY LIST OF BSICT STUDENTS\n");
    int x;
    if (Arr->lastNdx != -1) {
        for (x = 0; x <= Arr->lastNdx; ++x) {
            printf("\t[%2d] %16s %16s %c.\n", x, Arr->names[x].LN, Arr->names[x].FN, Arr->names[x].MI);
        }
    } else {
        printf("\tNo BSICT Students!\n");
    }
}