/*************************************************************************************************
 *  Author:         Fabiola Villanueva (Practice Code 001: 006_ADT Singly Linked List_summer)    *
 *  Description:    Singly Linked List Practice                                                  *
 *  Task:           Provide the function prototypes and function defintions                      *
 *************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#define MENU 5

typedef char STRING[50];

//* STRUCTURE DEFINITIONS
typedef struct node {
    int data;
    struct node *next;
} NodeType, *NodePtr;

//* FUNCTION PROTOTYPES
//! start coding here (prototypes only)
void insertSorted (NodePtr *list);
int searchData (NodePtr list);
void deleteAllData (NodePtr *list);
void display (NodePtr list);

int main() {
    system("CLS");

    NodePtr head = NULL;
    int i, item, choice, pos;
    STRING menu[MENU] = {  "Exit",
                            "Insert Sorted",
                            "Search Data", 
                            "Delete All",
                            "Display List" };

    do {
        printf("MENU\nKindly select a number:\n\n");
        for (i = 0; i < MENU; ++i) {
            printf("    [%d] %s\n", i, menu[i]);
        }
        printf("\nChoice: ");
        scanf("%d", &choice);

        system("CLS");

        switch (choice) {
            case 0:
                printf("\n\"EXIT\"\n\n");
                display(head);
                printf("\n\nTerminating program...");

                break;
            
            case 1:
                printf("\n\"INSERT SORTED\"\n\n");
                display(head);
                insertSorted (&head);
                printf("\n");
                display(head);

                break;
            
            case 2:
                printf("\n\"SEARCH DATA\"\n\n");
                display(head);
                pos = searchData (head);
                printf("Data is at position = [%d]\n\n", pos);
                display(head);

                break;

            case 3:
                printf("\n\"DELETE ALL\"\n\n");
                display(head);
                deleteAllData (&head);
                display(head);

                break;

            case 4:
                printf("\n\"DISPLAY LIST\"\n\n");
                display(head); 

                break;
        }
        
        printf("\n\n");
        system("PAUSE");
        system("CLS");

    } while (choice != 0);

    printf("\n");
    return 0;
}

//* FUNCTION DEFINITIONS

/**********************************************************************************************
 *  Insert Sorted Function Specifications:                                                    *
 *  Code for user prompt is provided, the integer "item" is the element to insert.            *
 *  Given the list, insert the item at its proper position in the list in ascending order.    *
 **********************************************************************************************/
void insertSorted (NodePtr *L) {
    int item;
    printf("\nEnter item (integer) to insert: ");
    scanf("%d", &item);
    printf("test");
	NodePtr *trav, temp;
	temp =(NodePtr) malloc(sizeof(struct node));
	
	if(temp != NULL){
		for(trav = L; *trav != NULL && (*trav)->data < item ; trav = &(*trav)->next){}
		temp->data = item;
		temp->next = *trav;
		*trav = temp;
	}
    //! start coding here


}

/**********************************************************************************************
 *  Search Data or Search and Element in the List Function Specifications:                    *
 *  Code for user prompt is provided, the integer "item" is the element to search.            *
 *  The function shall return the positon of the item in the list.                            *
 *  First node == position is zero; given the list, return -1 if the item to search is        *
 *  not found in the list, otherwise the position of the node.                                *
 *  Hint: Nothing changes in the list itself, take note of how the list should be passed.     *
 **********************************************************************************************/
int searchData (NodePtr L) {
    int item;
    printf("\nEnter data to search: ");
    scanf("%d", &item);
	int count = 0, pos = -1; 
	NodePtr trav;
	for(trav = L; trav != NULL && trav->data != item; trav = trav->next){
		++count;
        // printf("[%d]\n", count);
	}
    if(trav->data == item){
        pos = count;	
    }
		
    //! start coding here
	return pos;
	
}

/**********************************************************************************************
 *  Delete all Occurences Function Specifications:                                            *
 *  Code for user prompt is provided, the integer "item" is the element to delete.            *
 *  Given the list itself, delete all occurences of "item" in the list.                       *
 *  Hint: Take note of how you pass your list when manipulating addresses are involved.       *
 **********************************************************************************************/
void deleteAllData (NodePtr *L) {
    int item;
    printf("\nEnter item to delete: ");     
    scanf("%d", &item);
	NodePtr *trav, temp;
	for(trav = L; *trav != NULL && (*trav)->data != item; trav = &(*trav)->next){}
	if(*trav != NULL){
		temp = *trav;
		*trav = temp->next;
		free(temp);
	}
    //! start coding here


}

/**********************************************************************************************
 *  Display Linked List Function Specifications:                                              *
 *  Given the list, display all the element in the list of integers in ascending order.       *
 **********************************************************************************************/
void display (NodePtr L) {
    //! start coding here
	NodePtr trav;
	for(trav = L; trav != NULL; trav = trav->next){
		printf("%d ", trav->data);
	}
    
}

/**********************************************************************************************
 *  Learning outcomes:                                                                        *
 *  1. Program structure reading comprehension                                                *
 *  2. Program specifications reading comprehension                                           *
 *  3. Singly linked list basics                                                              *
 *  4. Pointer basics                                                                         *
 *                                                                                            *
 *  Bonus question: (Append in this same program as comment)                                  *
 *  Explain the difference between passing a list by copy and by reference, AND when          *
 *  should we use which on what scenario.                                                     *
 **********************************************************************************************/