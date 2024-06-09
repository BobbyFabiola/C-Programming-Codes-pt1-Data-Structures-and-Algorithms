/*************************************************************************************************
 *  Author:         Fabiola Villanueva (Practice Code 002: 008_Singly Linked List Full C.R.U.D.) *
 *  Description:    Singly Linked List - Aggregate Data and Full C.R.U.D.                        *
 *  Task:           Provide the function prototypes and function defintions                      *
 *************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MENU_MAX 10

typedef char STRING[50];

//* STRUCTURE DEFINITIONS
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

//* FUNCTION PROTOTYPESs
//! start coding here (finish the parameters only)

Node_Ptr newStudent ();
void insertFront ();
void insertRear ();
void insertAt ();
void displayList ();
void displayID ();
void updateList ();
void deleteFront ();
void deleteRear ();
void deleteAt ();

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

//* FUNCTION DEFINITIONS

/**********************************************************************************************
    "newStudent" Function Specs:
    Code for user prompt to input data is provided. The function will return an entire node or
    an entire new student; the node's pointer shall be set to NULL.
 **********************************************************************************************/
Node_Ptr newStudent (Node_Ptr temp) {
	temp = (Node_Ptr) malloc (sizeof(Node_Type));

    if (temp == NULL) {
        printf("Unsuccessful memory allocation.");
    } else {
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
        
        temp->next = NULL;
	}
	return temp;
}

/**********************************************************************************************
    "insertFront" Function Specs:
    Given the list, the function will call "newStudent" function to populate a node; 
    this node shall be inserted at the front of the list.
 **********************************************************************************************/
void insertFront (Node_Ptr *list) {
	//! start coding here

    
}

/**********************************************************************************************
    "insertRear" Function Specs:
    Given the list, the function will call "newStudent" function to populate a node; 
    this node shall be inserted at the end of the list or at rear.
 **********************************************************************************************/
void insertRear (Node_Ptr *list) {
	//! start coding here


}

/**********************************************************************************************
    "insertAt" Function Specs:
    Given the list and a position, the function will call "newStudent" function to 
    populate a node; this node shall be inserted at said position into the list;
    First node == position is zero.
 **********************************************************************************************/
void insertAt (Node_Ptr *list, int pos) {
	//! start coding here


}

/**********************************************************************************************
    "displayList" Function Specs:
    Given the list, partial code is provided. Display all the elements of the list
    such that all student details shall be displayed.
 **********************************************************************************************/
void displayList (Node_Ptr list) {
    int i;
    printf("List:\n");
    if (list == NULL){
        printf("List is empty.\n");
    } else {
        for (i = 0; list != NULL; list = list->next, ++i) {
            //! start coding here


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

/**********************************************************************************************
    "updateList" Function Specs:
    Given the list and a posititon, the function will call "newStudent" function to populate a 
    node; this node shall replace a student in the list at the given position.
    Note: If a position is a number greater than the number of elements in the list, assume
    to update the last node or the node at rear of the list.
 **********************************************************************************************/
void updateList (Node_Ptr *list, int pos) {
	//! start coding here


}

/**********************************************************************************************
    "deleteFront" Function Specs:
    Given the list, the function will delete the very front element of the list.
 **********************************************************************************************/
void deleteFront (Node_Ptr *list) {
	//! start coding here


}

/**********************************************************************************************
    "deleteRear" Function Specs:
    Given the list, the function will delete the element at the very rear of the list
    or the last node of the list.
 **********************************************************************************************/
void deleteRear (Node_Ptr *list) {
	//! start coding here


}

/**********************************************************************************************
    "deleteAt" Function Specs:
    Given the list and a position, the function will delete the element at said position
    in the list.
    First node == position is zero.
 **********************************************************************************************/
void deleteAt (Node_Ptr *list, int pos) {
	//! start coding here


}