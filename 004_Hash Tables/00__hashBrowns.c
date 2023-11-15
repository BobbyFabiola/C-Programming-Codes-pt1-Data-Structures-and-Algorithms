/*  Author: Fabiola Villanueva
    Description: In class notes for hash tables
    Date: Oct 05, 2023
*/

// #include <stdio.h>
// #include <stdlib.h>
// #define SIZE 5

// //typedef defintions
// typedef struct {
//     unsigned long int idNum;
//     char FN[20];
//     char LN[20];
//     int year;
//     char mi;
// } studType;

// typedef struct node {
//     studType data;
//     struct node *next;
// } nodeType, *nodePtr;

// typedef nodePtr dictionary[SIZE];           //making each index of the array a head pointer

// //function prototype
// void initialize (dictionary D[]);           //initializing every head pointer on each index to NULL
// void display (dictionary D[]);

// int main() {
//     system("CLS");
//     dictionary myD;

//     printf("0. Initialize.\n");
//     initialize (&myD);

//     printf("\n1. Display.\n");
//     display (&myD);                         //we pass the array, but should'nt myD be array name alr



//     printf("\n");
//     return 0;
// }

// //function defintions
// //0.
// void initialize (dictionary D[]) {
//     int i;
//     for (i = 0; i < SIZE; ++i) {
//         *D[i] = NULL;
//     }
// }

// //1.
// void display (dictionary D[]) {
//     int i;
//     for (i = 0; i < SIZE; ++i) {
//         if (*D[i] == NULL) {
//             printf("\t[%d] -> NULL\n", i);
//         }
//     }
// }

//Rhenz work
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef char name[20];
typedef struct {
    name names[MAX];
    int top;
}Stack;

void initialize(Stack * ptr);
void push(Stack * ptr, char elem[]);
void pop (Stack * ptr);
void displayList(Stack ptr);
name *top (Stack ptr);


int main(){
    system("cls");                              //just to clear terminal
    Stack A;
    initialize(&A);
    
    push(&A, "John");
    push(&A, "Michael");
    push(&A, "Liam");
    push(&A, "Shabimbawa");
    push(&A, "Jorge");
    printf("Top Val= %s\n", A.names[A.top]);
    // name *topVal = top(A);
    displayList(A);
    printf("\ntopVal = %s\n", top(A));
    // free(topVal);
}

void initialize(Stack * ptr){
    // ptr->top = MAX-1;
    ptr->top = MAX;                                 //initializing top off bounds from the array
}

void push(Stack * ptr, char elem[]){
    // name *Name = malloc(sizeof (name));          //no need to malloc since we aren't returning anything
    // strcpy(*Name, elem);
    if(ptr->top >= 0){
        strcpy(ptr->names[--ptr->top], elem);       //we are copying elem (our string) directly into the stack at the exact index via prefix
    }                                               //we decrement the value of top before inserting into the stack
    else{
        printf("Stack is full");
    }
}

void pop (Stack * ptr){
    if(ptr->top<MAX){
        ptr->top++;
    } else {
        printf("Stack is empty\n");
    }    
}

name *top (Stack ptr){
    name * temp = (name *)malloc(sizeof(name));     //create space in heap since u can't return arrays
    strcpy(*temp, ptr.names[ptr.top]);              //space in heap will ge the top most value
    return temp;                                    //return the address where temp is located in heap
}

void displayList(Stack ptr){                        //pass by copy, values we manipulated here wont reflect into main
    // int x = ptr.top;
    if (ptr.top == MAX) {
        printf("Stack is empty.\n");
    } else {
        printf("<<My Stack>>");
        for(; ptr.top < MAX ; ++ptr.top){           //i start where my top is and did not have to use another variable, just used top value as is
            printf("\n%s", ptr.names[ptr.top]);     //incrementing top itself since it wont reflect in main
        }   
    }
}