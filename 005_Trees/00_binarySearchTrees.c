/*   Author:        Fabiola Villanueva
 *   Description:   Linked List Implementation of Trees (unique elements)
 *   Date:          Nov 15, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 15

//typedef struct definitions
typedef enum BOOL {FALSE, TRUE} Boolean;

typedef struct treeNode {
     int data;
     struct treeNode *left;
     struct treeNode *right;
} treeType, *treePtr;

//function prototypes
Boolean initialize (treePtr *treeHead);
void insertSet (treePtr *treeHead, int arr[]);
Boolean isMember (treePtr treeHead, int elem);
void insertMember (treePtr *treeHead, int elem);
// void postorderDisplay ();
// void preorderDisplay ();
// void inorderDisplay ();
// void delete ();

int main() {
     system ("cls");
     treePtr head;
     int set[MAX] = {21, 33, 43, 11, 11, 67, 32, 75, 91, 15, 3, 21, 43, 67, 66};
     int i, elem;
     Boolean ans = TRUE;

     printf("<< 0. Initialize >>\n");
     if (initialize (&head)) {
          printf("\thead = NULL\n");
          printf("\tHead of tree is now intialized to NULL.\n");
     }

     printf("\n<< 1. Insert Set Into Tree >>\n");
     
     printf("\tSet = {");
     for (i = 0; i < MAX; ++i) {
          printf("%d", set[i]);
          if (i < MAX-1) {
               printf(", ");
          }
     }
     printf("}");

     printf("\n\tInserting all elements in the set into the tree...\n\n");
     insertSet (&head, set);
     
     printf("\n\t> User input of elements into the tree:\n");
     do {
          printf("\n\tAdd an element into the tree? < 1-yes / 0-no >\n");
          printf("\tAns: ");
          scanf("%d", &ans);

          if (ans == TRUE) {
               printf("\tInput member to insert: ");
               scanf("%d", &elem);
               insertMember (&head, elem);
          }
     } while (ans == TRUE);



     printf("\n\n<< END >>\n\n");
     return 0;
}

//function definition
Boolean initialize (treePtr *treeHead) {
     *treeHead = NULL;
     return (*treeHead == NULL) ? TRUE: FALSE;
}

void insertSet (treePtr *treeHead, int arr[]) {
     treePtr temp;
     int i;

     for (i = 0; i < MAX; ++i) {                  //per iteration of the array is an element to insert into the tree
          insertMember (treeHead, arr[i]);        //if unique element then insert into tree
     }
}

Boolean isMember (treePtr treeHead, int elem) {
     while (treeHead != NULL && treeHead->data != elem) {
          treeHead = (elem < treeHead->data) ? treeHead->left: treeHead->right;
     }
     return (treeHead != NULL) ? TRUE: FALSE;     //is a member if trav is pointing to an existing node
}

void insertMember (treePtr *treeHead, int elem) {
     treePtr *trav = treeHead, temp;

     if (isMember(*trav, elem) == FALSE) {
          printf("\t[%d] is a unique element. Inserting into tree...\n", elem);
          
          temp = malloc(sizeof(treeType));
          temp->left = NULL; 
          temp->right = NULL;
          temp->data = elem;

          while (*trav != NULL && (*trav)->data != elem) {
               trav = (elem < (*trav)->data) ? &(*trav)->left: &(*trav)->right;
          }
          *trav = temp;
     } else {
          printf("\t[%d] is NOT a unique element.\n", elem);
     }
}

//how to visit each node with tree traversals in code?
//isnt that recursion? how recursion? and what is iterative? what is recursion vs iterative?