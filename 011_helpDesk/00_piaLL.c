#include <stdio.h>
#include <stdlib.h>
#define SIZE 0XF

typedef struct {
    char FName[24];
    char MI;
    char LName[16];
} nameType;

typedef struct {
    nameType name;
    char gender;
} personType;

//Defintion of the array implementation of list
typedef struct {
    personType people[SIZE];
    int count;
} ArrayList;

//Definition of Linked List
typedef struct node {
    personType person;
    struct node *next;
} *LinkList;

void insertFirst(LinkList *L, personType P);
void displayLinkedList(LinkList L);

int main(){
    system ("cls");

    // LinkList given;                                         //! declaration  of head pointer
    LinkList given = NULL;                                  //! declaration AND initialization of head pointer 
    personType person1 = {{"Pia", 'D', "Tantay"}, 'F'};
    insertFirst(&given, person1);

    personType person2 = {{"Simon", 'U', "Tabaloc"}, 'M'};
    insertFirst(&given, person2);

    personType person3 = {{"Chan", 'C', "Rosell"}, 'M'};
    insertFirst(&given, person3);

    displayLinkedList(given);
    

    printf("\n\n");
    return 0;
}
void insertFirst(LinkList *L, personType P){
    LinkList temp = malloc(sizeof(struct node));
    if(temp != NULL) {
        temp->person = P;
        temp->next = *L;
        *L = temp;
    }
}
void displayLinkedList(LinkList L){
    while(L != NULL){
        printf("%s %c %s \t |", L->person.name.FName, L->person.name.MI, L->person.name.LName);
        printf("\t %c\n", L->person.gender);
        L = L->next;
    }
}