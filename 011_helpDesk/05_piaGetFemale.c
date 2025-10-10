#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 0XF

typedef struct {
    char FName[24], MI, LName[16];
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

void insertFirst(LinkList *L);
void displayLinkedList(LinkList L);
ArrayList getFemale(LinkList *L);
void displayArrayList(ArrayList A);

int main(){
    LinkList given = NULL;
    int option;

    do {
        displayLinkedList(given);
        printf("\n\n[1] Add student\n");
        printf("[2] Exit\n");
        printf("Option: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                system("CLS");
                printf("ADD A STUDENT\n\n");
                insertFirst(&given);
        }
    } while (option != 2);

    return 0;
}
void insertFirst(LinkList *L){
    int num, x, c;

    LinkList temp = malloc(sizeof(struct node));
    if(temp != NULL) {
        fflush(stdin);
        printf("First Name: ");
        fgets(temp->person.name.FName, 24, stdin);fflush(stdin);
        temp->person.name.FName[(strcspn(temp->person.name.FName, "\n"))] = '\0';
        
        printf("Middle Initial: ");
        scanf(" %c", &temp->person.name.MI);
        
        fflush(stdin);
        printf("Last Name: ");
        fgets(temp->person.name.LName, 16, stdin); fflush(stdin);
        temp->person.name.LName[(strcspn(temp->person.name.LName, "\n"))] = '\0';

        printf("Gender: ");
        scanf(" %c", &temp->person.gender);
        temp->next = *L;
        *L = temp;
    }
}
void displayLinkedList(LinkList L){
    if(L == NULL){
        printf("-- List is Empty --");
    } else {
        while(L != NULL){
            printf("%-8s %-8c %s \t |", L->person.name.FName, L->person.name.MI, L->person.name.LName);
            printf("\t %c\n", L->person.gender);
            L = L->next;
        }
    }
}
ArrayList getFemale(LinkList *L){
    ArrayList arr;
    LinkList *trav, temp;
    arr.count = 0;

    for(trav = L; *trav != NULL;){
        if((*trav)->person.gender == 'F'){
            temp = *trav; //nagsegmentation fault to ato last night nga "*trav = temp->next"
            strcpy(arr.people[arr.count].name.FName, temp->person.name.FName);
            arr.people[arr.count].name.MI = temp->person.name.MI;
            strcpy(arr.people[arr.count].name.LName, temp->person.name.LName);
            arr.people[arr.count].gender = temp->person.gender;
            arr.count++;
            *trav = temp->next;
            free(temp);
        } else {
            trav = &(*trav)->next;
        }
    }

    return arr;
}
void displayArrayList(ArrayList A){
    int x;
    
    printf("\nFemale Students: %d\n", A.count);
    for(x = 0; x < A.count; x++){
        printf("%-8s %-8c %s \t |", A.people[x].name.FName, A.people[x].name.MI, A.people[x].name.LName);
        printf("\t %c\n", A.people[x].gender);
    }
}