/*   Author:             Fabiola Villanueva
 *   Description:        Linked List Implementation of Binary Search Trees (Iterative)
 *   Specifications:     Recursive (~isMember, ~insertion, ~tree traversal)
 *   Date:               Nov 19, 2023
 */

#include <stdio.h>
#include <stdlib.h>

//typedef definitions
typedef enum {FALSE, TRUE} Boolean;

typedef struct node {
     int data;
     struct node *left;
     struct node *right;
} *BST;

//function prototypes
void initialize (BST *root);
Boolean isMember (BST root, int elem);
void insertMember (BST *nodePtr, int elem);
void preorderDisplay (BST root);
void inorderDisplay (BST root);
void postorderDisplay (BST root);

int main() {
     system ("cls");
     BST headRoot = NULL;

     printf("<< BEGIN >>\n");
     printf("\n<< 0. Initialized Root Node >>\n");
     if (headRoot == NULL) {
          printf("\tLeft and right branches of root node are now initialized to null.\n");
     }

     printf("\n<< 1. Inserting Elements >>\n");
     printf("\tInserting 8, 10, 13, 5, 4, 8, 10, 6, 3...");
     insertMember (&headRoot, 8);
     insertMember (&headRoot, 10);
     insertMember (&headRoot, 13);
     insertMember (&headRoot, 5);
     insertMember (&headRoot, 4);
     insertMember (&headRoot, 8);
     insertMember (&headRoot, 10);
     insertMember (&headRoot, 6);
     insertMember (&headRoot, 3);

     printf("\n\n<< 2. Pre-order Display >>\n\t");
     preorderDisplay (headRoot);

     printf("\n\n<< 3. In-order Display >>\n\t");
     inorderDisplay (headRoot);

     printf("\n\n<< 4. Post-order Display >>\n\t");
     postorderDisplay (headRoot);

     printf("\n\n<< END  >>");
     return 0;
}

//function defintions
void initialize (BST *root) {
     *root = NULL;
}

Boolean isMember (BST root, int elem) {                     //returns another function call while terminating the previous call as it traverses the tree
     if (root == NULL) {
          return FALSE;
     } else if (root->data == elem) {
          return TRUE;
     } else {                       
          return (elem < root->data) ? isMember (root->left, elem): isMember (root->right, elem);
     }
}

BST insertNode(BST root, int elem) {                                  //i dont understand recursion wtf
    if (root == NULL) {                                               //allocate new node temp to insert
        BST temp = malloc(sizeof(struct node));
        temp->data = elem;
        temp->left = temp->right = NULL;

        if (temp == NULL) {                                           //malloc failure management
            return NULL;
        }

        return temp;
    } else {
        if (elem < root->data) {                                      //recursively insert the element based on BST property
            root->left = insertNode(root->left, elem);
        } else if (elem > root->data) {
            root->right = insertNode(root->right, elem);
        }                                                             //if elem is equal to root->data, it's a duplicate; handle as needed
    }
    return root;
}

void insertMember(BST* root, int elem) {
    if (!isMember(*root, elem)) {                                     //check if elem does not exist in the tree
        *root = insertNode(*root, elem);
    }
}

void inorderDisplay (BST headPtr) {                                   //recursive
     if (headPtr != NULL) {                                           //visits every left child, prints the data ascending once it reaches the bottom
          inorderDisplay (headPtr->left);                             //after printing each left child, then to parent, then to right child
          printf("[%d]", headPtr->data);                              //function is removed from execution stack once condition meets NULL
          inorderDisplay (headPtr->right);
     }
}

void preorderDisplay (BST headPtr) {
     if (headPtr != NULL) {
          printf("[%d]", headPtr->data);
          preorderDisplay (headPtr->left);
          preorderDisplay (headPtr->right);
     }
}

void postorderDisplay (BST headPtr) {
     if (headPtr != NULL) {
          preorderDisplay (headPtr->left);
          preorderDisplay (headPtr->right);
          printf("[%d]", headPtr->data);
     }
}