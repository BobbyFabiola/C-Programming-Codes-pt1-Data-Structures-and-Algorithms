// transfer data from s1 to s2 
// then s2 to q

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 5

typedef struct{
    int elem[MAX];
    int currentSize;
}Stack;

typedef struct node{
    int elem;
    struct node *link;
}*Queue;

void initStack(Stack *S){
    S->currentSize = 0;
}

void initQueue(Queue *Q){
    *Q = NULL;
}

bool isEmptyS(Stack S){
    return (S.currentSize == 0) ? true : false;
}

bool isFullS(Stack S){
    return (S.currentSize == MAX) ? true : false;
}

bool isEmptyQ(Queue Q){
    return (Q == NULL) ? true : false;
}

void push(Stack *S, int data){
    if(!isFullS(*S)){
        S->elem[S->currentSize] = data;
        S->currentSize++;
    }
}

void pop(Stack *S){
    if(!isEmptyS(*S)){
        S->currentSize--;
    }
}

int top(Stack S){
    return S.elem[S.currentSize - 1];
}

void printStack(Stack S){
    if(isEmptyS(S)){
        printf("Stack is EMPTY.\n");
    }else{
        for(; !isEmptyS(S) ; pop(&S)){
            printf("[%d]", top(S));
        }
    }
}

void enqueue(Queue *Q, int data){
    Queue *temp, newNode = (Queue)malloc(sizeof(struct node));
    for(temp = Q ; *temp != NULL ; temp = &(*temp)->link){}
    newNode->elem = data;
    newNode->link = NULL;
    *temp = newNode;
}

void dequeue(Queue *Q){
    Queue toDel = *Q;
    *Q = (*Q)->link;
    free(toDel);
}

int front(Queue Q){
    return Q->elem;
}

void printQueue(Queue Q){
    if(isEmptyQ(Q)){
        printf("Queue is EMPTY.\n");
    }else{
        for(; !isEmptyQ(Q) ; dequeue(&Q)){
            printf("[%d]", front(Q));
        }
    }
    printf("\n");
}

void populateS2(Stack *S1, Stack *S2){
    int ndx;
    for(; !isEmptyS(*S1) ; pop(S1)){
        push(S2, top(*S1));
    }
}

void populateQueue(Stack S, Queue *Q){
    for(; !isEmptyS(S) ; pop(&S)){
        enqueue(Q, top(S));
    }
}

int main(){
    Stack S1, S2;
    Queue Q;

    //initializing
    initQueue(&Q);
    initStack(&S1);
    initStack(&S2);

    //populate S1
    int ndx, s1populate[] = {0,1,2,3,4};
    for(ndx = 0 ; ndx < MAX ; ndx++){
        push(&S1, s1populate[ndx]);
    }
    printf("1.) Populating S1\n");
    printf("S1: ");
    printStack(S1);
    printf("\n\n");

    //transfer data from s1 to s2
    printf("2.) Populating S2 with S1\n");
    populateS2(&S1, &S2);
    printf("S1: ");
    printStack(S1);
    printf("S2: ");
    printStack(S2);
    printf("\n\n");

    //populate Q with S2
    printf("3.) Populating Q with S2\n");
    printf("S1: ");
    printStack(S1);
    printf("S2: ");
    printStack(S2);
    printf("\nQ:  ");
    populateQueue(S2, &Q);
    printQueue(Q);
}