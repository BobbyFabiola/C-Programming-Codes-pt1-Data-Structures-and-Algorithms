/*  Author:         Fabioila C. Villanueva
    Description:    Open Hashing in ADT Set (in-class activity) 
    Date:           Feb 26, 2o24 (09:00am-06:30pm)
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//structure definition
typedef struct node {
    int data;
    struct node *link;
} *SET;
typedef SET Dictionary[MAX];
typedef enum {TRUE, FALSE} Boolean;

//function prototypes
int hashBrown (int elem);
void initDictionary (Dictionary D);
void displayDict (Dictionary D);
Boolean isMember (Dictionary D, int elem);
void insertUnique (Dictionary D, int num);
void deleteMem (Dictionary D, int num);

int main () {
    system("cls");
    printf("<< START >>\n");
    Dictionary mD;

    printf("\n1. INITIALIZE DICTIONARY\n");
    initDictionary(mD);

    displayDict(mD);

    printf("\n\n2. INSERT ELEMENTS\n");
    insertUnique (mD, 50);
    insertUnique (mD, 50);
    insertUnique (mD, 16);
    insertUnique (mD, 11);
    insertUnique (mD, 12);
    insertUnique (mD, 43);
    insertUnique (mD, 8);
    insertUnique (mD, 45);
    insertUnique (mD, 21);
    insertUnique (mD, 33);
    insertUnique (mD, 92);
    insertUnique (mD, 43);
    
    displayDict(mD);
    
    printf("\n\n2. DELETE ELEMENTS\n");
    deleteMem (mD, 92);
    deleteMem (mD, 100);
    deleteMem (mD, 50);
    deleteMem (mD, 92);
    deleteMem (mD, 33);

    displayDict(mD);

    printf("\n\n<< END >>");
    return 0;
}

//function definition
int hashBrown (int elem) {   //sum of the entire number and module MAX
    int sum = 0;
    while (elem != 0) {
        sum += (elem % 10);         //getting the ones place
        elem /= 10;                 //removing the ones place
    }
    return sum % MAX;
    // return elem % MAX;
}

void initDictionary (Dictionary D) {
    int x;
    for (x = 0; x < MAX; ++x) {
        D[x] = NULL;
    }
}

void displayDict (Dictionary D) {
    int x;
    printf("\n\tSET\tELEMENTS");
    for (x = 0; x < MAX; ++x) {
        printf("\n\t[%d] : \t", x);
        if (D[x] == NULL) {
            printf("Empty");
        } else {
            SET ptr;
            for (ptr = D[x]; ptr != NULL; ptr = ptr->link) {            //use PN so the value at head pointer does not change via using D[x] = D[x]->link
                printf("%d", ptr->data);
                if (ptr->link != NULL){
                    printf(", ");
                }
            }
        }
    }
}

Boolean isMember (Dictionary D, int elem) {
    SET temp;
    int key = hashBrown (elem);
    for (temp = D[key]; temp != NULL && temp->data != elem; temp = temp->link) {}
    return (temp != NULL)? TRUE: FALSE;
}

void insertUnique (Dictionary D, int num) {
    SET *trav, temp;
    int key = hashBrown(num);
    for (trav = &D[key]; *trav != NULL && (*trav)->data < num; trav = &(*trav)->link) {}
    if (*trav != NULL && (*trav)->data == num) {                                            //if loop terminates mid-traversal, then check if existing
        printf("\t%d is already in the set.\n", num);
    } else {                                                                                //else, elem to insert is unqiue
        temp = (SET) malloc (sizeof (struct node));
        if (temp != NULL) {
            temp->data = num;
            temp->link = *trav;
            *trav = temp;
        }
    }
}

void deleteMem (Dictionary D, int num) {
    int key = hashBrown(num);
    SET *trav, temp;
    for (trav = &D[key]; *trav != NULL && (*trav)->data != num; trav = &(*trav)->link){}
    if (*trav != NULL) {                                                                    //if elem found
        temp = *trav;
        *trav = temp->link;
        free (temp);
    } 
    else {
        printf("\t%d does not exist in the set.\n", num);
    }
}