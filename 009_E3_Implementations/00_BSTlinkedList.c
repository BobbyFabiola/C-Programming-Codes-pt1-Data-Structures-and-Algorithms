/*  Author:         Fabioila C. Villanueva
    Description:    Binary Search Tree w/ Linked List Implementation
    Date:           04/01/24
*/

#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 10

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} *nodePtr;

typedef enum {FALSE, TRUE} Boolean;

//function prototypes
nodePtr initializeTree (void);
Boolean insertElem (nodePtr *T, int elem);
Boolean populateTree (nodePtr *T, int arr[]);
Boolean isMember (nodePtr T, int elem);
Boolean deleteElem (nodePtr *T, int elem);

void preOrder (nodePtr T);
void inOrder (nodePtr T);
void postOrder (nodePtr T);

int main () {
    system ("cls");
    Boolean ans = FALSE;
    int input;
    int arr[ARR_SIZE] = {31, 29, 13, 35, 40, 10, 12, 16, 21, 44};
    nodePtr mT = initializeTree();

    //! initialize
    printf("<< START >>\n\n");
    printf("00. INITIALIZE\n\tmT = %s\n", (mT == NULL)? "NULL": "Initialize Unsuccesful!");
    printf("\tStress test for isMember, intput an element to check: ");
    scanf("%d", &input);
    if (isMember (mT, input) == TRUE) {
        printf("\tFaulty isMember function.\n");
    } else {
        printf("\tYour isMember works just fine.\n");
    }

    //! populate
    printf("\n01. POPULATE TREE\n");
    if (populateTree (&mT, arr) == TRUE) {
        printf("\tPopulating Tree is Successful.\n");
    } else {
        printf("\tERROR! Unsuccessful Populating Tree.\n");
    }

    do {
        printf("\tInput Elem: ");
        scanf("%d", &input);
        if (insertElem (&mT, input) == TRUE) {
            printf("\tInsert for '%d' is successful.\n", input);
        } else {
            printf("\tElement '%d' already exists.\n", input);
        }
        printf("\n\tInsert Elem? <0-no: 1-yes>:  ");
        scanf("%d", &ans);
    } while (ans == TRUE);

    printf("\n\tPRE-ORDER: ");
    preOrder (mT);
    printf("\n\tINORDER: ");
    inOrder (mT);
    printf("\n\tPOST-ORDER: ");
    postOrder (mT);

    //! membership
    printf("\n\n02. CHECK MEMBERSHIP\n");
    do {
        printf("\tInput elem to check: ");
        scanf("%d", &input);
        if (isMember (mT, input) == TRUE) {
            printf("\t'%d' already exists in the tree.\n", input);
        } else {
            printf("\t'%d' does NOT exists in the tree.\n", input);
        }
        printf("\n\tCheck membership? <0-no: 1-yes>: ");
        scanf("%d", &ans);
    } while (ans == TRUE);

    //! delete
    printf("\n02. DELETE AN ELEMENT\n");
    do {
        printf("\tInput elem to delete: ");
        scanf("%d", &input);
        if (deleteElem (&mT, input) == TRUE) {
            printf("\tSuccessfully deleted '%d' from the tree.\n", input);
        } else {
            printf("\t'%d' does not exist in the tree.\n");
        }
        printf("\n\tDelete an element? <0-no: 1-yes>: ");
        scanf("%d", &ans);
    } while (ans == TRUE);
    printf("\n\tPRE-ORDER: ");
    preOrder (mT);
    printf("\n\tINORDER: ");
    inOrder (mT);
    printf("\n\tPOST-ORDER: ");
    postOrder (mT);

    printf("\n\n<< END >>\n");
    return 0;
}

nodePtr initializeTree (void) {
    nodePtr head = NULL;
    return head;
} 

Boolean populateTree (nodePtr *T, int arr[]) {
    Boolean retVal = FALSE;
    int x;
    for (x = 0; x < ARR_SIZE; ++x) {
        retVal = insertElem (T, arr[x]);
    }
    return retVal;
}

Boolean insertElem (nodePtr *T, int elem) {
    nodePtr *trav, temp;
    for (trav = T; *trav != NULL && (*trav)->data != elem; ) {
        trav =  (elem < (*trav)->data)? &(*trav)->left: &(*trav)->right;
    }
    if (*trav == NULL) {
        temp = (nodePtr) malloc (sizeof (struct node));
        if (temp != NULL) {
            temp->data = elem;
            temp->left = temp->right = NULL;
            *trav = temp;
        }
    }
    return (*trav == temp)? TRUE: FALSE;
}

Boolean isMember (nodePtr T, int elem) {
    int path;
    for (path = 0; T != NULL && T->data != elem; ++path) {
        T = (elem < T->data) ? T->left: T->right;
    }
    printf("\tPath of '%d' is [%d].\n", elem, (T==NULL) ? -1: path);    //-1 if reached end
    return (T == NULL) ? FALSE: TRUE;
}

Boolean deleteElem (nodePtr *T, int elem) {
    nodePtr *trav, temp;
    for (trav = T; *trav != NULL && (*trav)->data != elem; ) {
        trav = (elem < (*trav)->data) ? &(*trav)->left: &(*trav)->right;
    }
    if (*trav != NULL) {                                                                                                    //trav points to the node to be deleted
        temp = *trav;                                                                                                       //temp is the node with the element
        if (temp->left != NULL && temp->right != NULL) {                                                                    //then two children
            nodePtr *search;
            for (search = &temp->left; *search != NULL && (*search)->right != NULL; search = &(*search)->right) {}          //searching for highest predecssor
            temp->data = (*search)->data;                                                                                   //temp node will get data of highest predecessor
            temp = *search;                                                                                                 //temp will be upated to point to the node of the highest predecessor to delete
            *search = temp->left;                                                                                           //update the pointer pointer to the node to be deleted to the left child of node to delete
        } else {
            *trav = (temp->left != NULL) ? (*trav)->left: (*trav)->right;                                                   //link the only child one level up
        }
        free (temp);                                                                                                        //delete the node of the element
    }
    return (temp->data != elem) ? TRUE: FALSE;
}

void preOrder (nodePtr T) {
    if (T != NULL) {
        printf("%d ", T->data);
        preOrder (T->left);
        preOrder (T->right);
    }
}

void inOrder (nodePtr T) {
    if (T != NULL) {
        inOrder (T->left);
        printf("%d ", T->data);
        inOrder (T->right);
    }
}

void postOrder (nodePtr T) {
    if (T != NULL) {
        postOrder (T->left);
        postOrder (T->right);
        printf("%d ", T->data);
    }
}