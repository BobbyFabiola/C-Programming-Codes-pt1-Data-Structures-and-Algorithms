/*  Author:         Fabioila C. Villanueva
    Description:    Disjoint UID 
    Date:           Feb 26, 2o24
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//structure definition
typedef struct node {
    char data;
    struct node *link;
} *SET;

//function prototypes
void populateList (SET *L, char arr[]);
void displaySet (SET L);

int main () {
    system("cls");
    char setA[MAX] = {2, 4, 6, 8, 10};
    char setB[MAX] = {1, 3, 5, 7, 9};
    SET A = NULL, B = NULL;

    printf("<< START >>\n\n");
    populateList(&A, setA);
    populateList(&A, setB);
    displaySet(B);
    displaySet(B);

    
    printf("\n\n<< END >>");
    return 0;
}

void populateList (SET *L, char arr[]) {
    SET temp;
    int x;
    for (x = 0; x < MAX; ++x) {
        temp = malloc (sizeof (struct node));
        temp->data = arr[x];
        temp->link = *L;
        *L = temp;
    }
}

void displaySet (SET L) {
    
}