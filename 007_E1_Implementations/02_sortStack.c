//Author:       Fabiola Villanueva
//Description:  Sort A Stack Implemented in Array
//Date:         Feb 19, 2024

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//structure definition
typedef struct {
    char arr[MAX];
    int top;
} STACK;

//function prototypes
void initStack (STACK *S);
void pop (STACK *S);
void push (STACK *S, char elem);
char top (STACK S);
void display (STACK S);
void sortStack (STACK *S);

int main() {
    system("cls");
    STACK myS;
    initStack (&myS);
    if (myS.top == MAX) {
        printf("0. Stack Initialized from MAX-1 to 0 (top == MAX)\n");
    }
    push(&myS, 'f');
    push(&myS, 'a');
    push(&myS, 'b');
    push(&myS, 'i');
    push(&myS, 'o');
    push(&myS, 'l');
    push(&myS, 'a');

    printf("1. Displaying Stack\n");
    display(myS);

    printf("2. Sort the Stack in Ascending Order\n");
    sortStack (&myS);
    display(myS);

    printf("\n");
    return 0;
}

//function definiton
void initStack (STACK *S) {
    S->top = MAX;
}

void pop (STACK *S) {
    if (S->top != MAX) {
        S->top++;
    }
}

void push (STACK *S, char elem) {
    if (S->top != 0) {              //is full if top is 0
        S->arr[--S->top] = elem;
    }
}

char top (STACK S) {
    return (S.top != MAX)? S.arr[S.top]: '\0';
}

void display (STACK S) {
    int x;
    if (S.top != MAX) {
        for (x = S.top; x < MAX; ++x) {
            printf("\t[%c]\n", S.arr[x]);
        }
    } else {
        printf("\tStack is EMPTY!\n");
    }
}

void sortStack (STACK *S) {
    STACK temp;
    initStack(&temp);
    
    push(&temp, top(*S));
    while (S->top != MAX) {
        if (top(*S) < top(temp)) {
            push(&temp, top(*S));
            pop(S);
        } else {
            char val = top(*S);
            pop(S);
            push(S, top(temp));
            pop(&temp);
            push(&temp, val);
        }
    }
    while (temp.top != MAX) {
        push(S, top(temp));
        pop(&temp);
    }
}