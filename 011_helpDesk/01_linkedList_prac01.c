/*************************************************************************************************
 *  Author:         Fabiola Villanueva (Practice Code 001: 006_ADT Singly Linked List_summer)    *
 *  Description:    Singly Linked List Practice                                                  *
 *  Task:           Provide the function prototypes and function defintions                      *
 *************************************************************************************************/

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

int main() {
    system("CLS");

    NodePtr head = NULL;
    int i, item, choice, pos;
    STRING menu[MENU] = {   "Exit",
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
                insertSorted ();
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

            default:
                printf("\n\"INVALID INPUT\"\n\n");
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
void insertSorted () {
    int item;
    printf("\nEnter item (integer) to insert: ");
    scanf("%d", &item);

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
void searchData () {
    int item;
    printf("\nEnter data to search: ");
    scanf("%d", &item);

    //! start coding here


}

/**********************************************************************************************
 *  Delete all Occurences Function Specifications:                                            *
 *  Code for user prompt is provided, the integer "item" is the element to delete.            *
 *  Given the list itself, delete all occurences of "item" in the list.                       *
 *  Hint: Take note of how you pass your list when manipulating addresses are involved.       *
 **********************************************************************************************/
void deleteAllData () {
    int item;
    printf("\nEnter item to delete: ");     
    scanf("%d", &item);

    //! start coding here


}

/**********************************************************************************************
 *  Display Linked List Function Specifications:                                              *
 *  Given the list, display all the element in the list of integers in ascending order.       *
 **********************************************************************************************/
void display () {
    //! start coding here

    
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