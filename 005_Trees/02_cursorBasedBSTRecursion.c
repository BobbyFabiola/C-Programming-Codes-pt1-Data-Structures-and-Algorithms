/*   Author:             Fabiola Villanueva
 *   Description:        Cursor Based Implementation of Binary Search Trees (Iterative)
 *                       Personal Project
 *   Date:               Nov 20, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 20

//typedef definitions
typedef struct {
     int data;
     int RC;
     int LC;
} nodeType;

typedef struct {
     nodeType NODES[MAX];
     int avail;
} VH;

typedef enum {FALSE, TRUE} BOOL;

//function prototypes
void initialize (int *nodePtr, VH *bst);                    //initialize tree to empty, root pointer is -1
void insertElem (int *nodePtr, VH *bst, int elem) ;         //recursion attempt
int allocSpace (VH *list);                                  //return the index of the 
BOOL isMember (int *head, VH bst, int elem);                //return true if elem to check is a member 
void deleteElem (int *nodePtr, VH *bst, int elem);

int main () {
     system ("cls");
     int root;                //passing the virual heap comes with passing the root pointer
     VH myBst;

     BOOL ans = TRUE;
     int val;

     printf("\n<< 0. Initialize Cursor Based Binary Search Tree >>\n");
     initialize (&root, &myBst);
     if (root == -1) {
          printf("\tTree is empty.");
     }

     printf("\n<< 1. Inserting Elements Into Tree >>\n");
     do {
          printf("\n\tInsert an element? <1-yes/0-no>\n\tAnswer: ");
          scanf("%d",  &ans);
          if (ans == TRUE) {
               printf("\tInput elem to insert into CB BST: ");
               scanf("%d", &val);
               insertElem (&root, &myBst, val);                             //passing copy of idx root, referencing tree, copy of val to insert
          }
     } while (ans == TRUE);

     printf("\n\n");
     return 0;
}

//function defintions
void initialize (int *nodePtr, VH *bst) {
     int i;
     *nodePtr = -1;                                                        //sets pointer to bst to null == empty tree
     bst->avail = 0;
     for (i = 0; i < MAX; ++i) {
          bst->NODES[i].LC = -1;
          bst->NODES[i].RC = (i != MAX-1) ? i+1: -1;
     }
}

void insertElem (int *nodePtr, VH *bst, int elem) {
     if (isMember (nodePtr, *bst, elem) == FALSE) {
          if (*nodePtr == -1) {      //if the tree is not empty and the elem is unique
               printf("\tElement is unique. Inserting into tree...\n");
               int idxAvail = allocSpace (bst);
               bst->NODES[idxAvail].data = elem;
               *nodePtr = idxAvail;
          } else {
               (elem < bst->NODES[*nodePtr].data) ? insertElem (&bst->NODES[*nodePtr].LC, bst, elem): insertElem (&bst->NODES[*nodePtr].RC, bst, elem);
          }
     } else {
          printf("\tElement is not unique.\n");
     }
}

int allocSpace (VH *list) {
     if (list->avail != -1) {
          int temp;
          temp = list->avail;
          list->avail = list->NODES[temp].RC;
          return temp;
     }
}

BOOL isMember (int *head, VH bst, int elem) {
     if (*head == -1) {                                     //tree is empty, thus there are no existing node in the first place            
          return FALSE;
     } else if (bst.NODES[*head].data == elem) {            //if tree is populated then evaluate if current data at index is equal to member 
          return TRUE;
     } else {                                               //otherwise, continue traversing the tree/list, but this time pass the current index/node
          return (elem < bst.NODES[*head].data) ? isMember (&(bst.NODES[*head].LC), bst, elem): isMember (&(bst.NODES[*head].RC), bst, elem);
     }
}

void deleteElem (int *nodePtr, VH *bst, int elem) {
}