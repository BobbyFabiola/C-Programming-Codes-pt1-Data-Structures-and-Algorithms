/*  Author:     Fabiola Villaneuva
    Project:    Singly Linked List CRUD via PPN or Double Pointers - Class Record
    Date:       July 13, 2023 (9:13pm)
    End: 		July 14, 2023 (10:38am)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MENU_MAX 10

typedef char STRING[50];

//structure definitions
typedef struct {
    STRING studName;
    STRING course;
    int year;
    int ID;
} Student_Type;

typedef struct node {
    Student_Type data;
    struct node *next;
} Node_Type, *Node_Ptr;

//function protoypes
Node_Ptr newStudent(Node_Ptr temp);
void insertFront (Node_Ptr *list);
void insertRear (Node_Ptr *list);
void insertAt (Node_Ptr *list, int pos);
void displayList (Node_Ptr list);
void displayID (Node_Ptr list);
void updateList (Node_Ptr *list, int pos);
void deleteFront (Node_Ptr *list);
void deleteRear (Node_Ptr *list);
void deleteAt (Node_Ptr *list, int pos);

int main() {
    Node_Ptr head = NULL;

    int i, pos, choice;
    STRING menu[MENU_MAX] = {   "Exit",
                                "Insert Front", "Insert Rear", "Insert At",
                                "Display List", "Display ID List", 
                                "Update At",
                                "Delete Front", "Delete Rear", "Delete At" };

    do { 
        system("CLS");  
        printf("SINGLY LINKED LIST CRUD IMPLEMENTATION:\n");
        printf("STUDENT RECORDS\n");
        for (i = 0; i < MENU_MAX; ++i) {
            printf("\t[%d]  %s\n", i, menu[i]);
        }
        printf("Input choice: ");
        scanf("%d", &choice);
        system("CLS");

        switch (choice) {
            case 0:
                printf("\"EXIT\"\n\n");
                printf("Terminating program...Thank you!\n");

                break;
            
            case 1:
                printf("\"INSERT FRONT\"\n\n");
                insertFront (&head);

                printf("\n");
                system("PAUSE");
                break;
            
            case 2:
                printf("\"INSERT REAR\"\n\n");
                insertRear (&head);

                printf("\n");
                system("PAUSE");
                break;
                
            case 3:
            	printf("\"INSERT AT\"\n\n");
            	displayID (head);
            	printf("\nEnter position to insert: ");
            	scanf("%d", &pos);
                insertAt (&head, pos);

                printf("\n");
                system("PAUSE");
                break;

            case 4:
                printf("\"DISPLAY LIST\"\n\n");
                displayList (head);

                printf("\n");
                system("PAUSE");
                break;
                
            case 5:
            	printf("\"DISPLAY ID List\"\n\n");
                displayID (head);

                printf("\n");
                system("PAUSE");
                break;
                
            case 6:
            	printf("\"UPDATE AT\"\n\n");
            	displayID (head);
            	printf("\nEnter position to update: ");
            	scanf("%d", &pos);
                updateList (&head, pos);
                displayID (head);

                printf("\n");
                system("PAUSE");
                break;
                
            case 7:
            	printf("\"DELETE FRONT\"\n\n");
            	displayID (head);
            	deleteFront (&head);
            	printf("\n");
            	displayID (head);
            	
            	printf("\n");
                system("PAUSE");
                break;
                
            case 8:
            	printf("\"DELETE REAR\"\n\n");
            	displayID (head);
            	deleteRear (&head);
            	printf("\n");
            	displayID (head);
            	
            	printf("\n");
                system("PAUSE");
                break;
                
            case 9:
            	printf("\"DELETE AT\"\n\n");
            	displayID (head);
            	printf("\nEnter position to delete: ");
            	scanf("%d", &pos);
            	deleteAt (&head, pos);
            	displayID (head);
            	
            	printf("\n");
              	system("PAUSE");
                break;
            	
            default:
            	printf("Invalid menu item. Try again.\n");
            	
            	printf("\n");
                system("PAUSE");
            	break;
        }

    } while (choice != 0);

    printf("\n");
    free (head);
    return 0;
}

//function definitions
Node_Ptr newStudent (Node_Ptr temp) {					//populates temp->data
	temp = (Node_Ptr) malloc (sizeof(Node_Type));

    if (temp == NULL) {
        printf("Unsuccessful memory allocation.");
    } else {                                          	//input student info
        printf("Register student below.\n");
        
        printf("\tID: ");
        scanf("%d", &temp->data.ID);
        printf("\tName: ");
        fflush(stdin);
        gets(temp->data.studName);
        printf("\tCourse: ");
        fflush(stdin);
        gets(temp->data.course);
        printf("\tYear level: ");
        scanf("%d", &temp->data.year);
        
        temp->next = NULL;								//pre-sets temp->next
	}
	return temp;
}

void insertFront (Node_Ptr *list) {
	Node_Ptr temp;
	temp = newStudent (temp);

    temp->next = (*list);
    (*list) = temp;
}

void insertRear (Node_Ptr *list) {
	Node_Ptr *trav, temp;
	temp = newStudent (temp);
	
	for (trav = list; (*trav) != NULL; trav = &(*trav)->next) {}
	
	temp->next = (*trav);
	(*trav) = temp;
}

void insertAt (Node_Ptr *list, int pos) {
	int i;
	
	Node_Ptr *trav, temp;
	temp = newStudent (temp);
	
	for (i = 0, trav = list; ((*trav) != NULL) && i < pos; trav = &(*trav)->next, ++i) {}
	
	temp->next = (*trav);
	(*trav) = temp;
}

void displayList (Node_Ptr list) {
    int i;
    printf("List:\n");
    if (list == NULL){
        printf("List is empty.\n");
    } else {
        for (i = 0; list != NULL; list = list->next, ++i) {
            printf("[%d]    %8d  | %30s  | %4s | year %d \n", i, list->data.ID, list->data.studName, strupr(list->data.course), list->data.year);
        }
    }
}

void displayID (Node_Ptr list) {
	printf("(Student ID List) = ");
	for (; list != NULL; list = list->next) {
		printf("[%d]", list->data.ID);
		if (list->next != NULL) {
			printf(" -> ");
		}
	}
}

void updateList (Node_Ptr *list, int pos) {      //overwrite a certain node at pos by user
	int i;
	Node_Ptr temp, newNode, *trav;
	newNode = newStudent (newNode);
	
	for (i = 0, trav = list; (*trav) != NULL && i < pos; trav = &(*trav)->next, ++i) {}
	
	temp = (*trav);
	newNode->next = temp->next;
	(*trav) = newNode;
	free(temp);
}

void deleteFront (Node_Ptr *list) {
	Node_Ptr temp;
	
	temp = (*list);
	(*list) = temp->next;
	free(temp);
}

void deleteRear (Node_Ptr *list) {
	Node_Ptr *trav, temp;
	
	for (trav = list; (*trav)->next != NULL; trav = &(*trav)->next) {}
	
	temp = (*trav);
	(*trav) = (*trav)->next;
	free(temp);
}

void deleteAt (Node_Ptr *list, int pos) {
	int i;
	Node_Ptr *trav, temp;
	
	for (i = 0, trav = list; (*trav) != NULL &&  i < pos; trav = &(*trav)->next, ++i) {}
	
	temp = (*trav);
	(*trav) = temp->next;
	free(temp);
}