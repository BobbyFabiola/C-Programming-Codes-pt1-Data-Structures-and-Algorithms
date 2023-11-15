/*  Author: Fabiola Villanueva
 *  Description: Bobby's First Cursor Based Practice
 *  Date: Sep 20, 2023
 */

#include <stdio.h>
#include <stdlib.h>         //just for system("CLS")
#define MAX 10

//typedef declarations      //respect the datatype typedef for LIST
typedef int LIST;           //designated to "point" to the address(index) of the first elem

//structure defintions
typedef struct {
    char data;
    int next;
} nodeType;

typedef struct {
    nodeType NODES[MAX];
    int avail;
} virtualHeap;              //my list

//function prototypes
void initialize (LIST *L, virtualHeap *VH);
void display (LIST L, virtualHeap VH);
void insertFront (LIST *L, virtualHeap *VH, char elem);
void insertRear (LIST *L, virtualHeap *VH, char elem);
void insertAt (LIST *L, virtualHeap *VH, int pos, char elem);
void insertSorted (LIST *L, virtualHeap *VH, char elem);
void deleteFront (LIST *L, virtualHeap *VH);
void deleteRear (LIST *L, virtualHeap *VH);
void deleteAt (LIST *L, virtualHeap *VH, int pos);

int main() {
    system("CLS");
    LIST myL;               //will hold index of first elem OR points to first elem of list
    virtualHeap myVH;

    printf("__________________________________________________________\n");
    printf("\n0. Initialize Virtual Heap.\n");
    initialize (&myL, &myVH);

    printf("\n1. Display Current Values of Virtual Heap (data and next).\n");
    display (myL, myVH);

    printf("\n2. Insert Front.\n");
    printf("   (Inserting Elements: A, H)\n\n");
    insertFront (&myL, &myVH, 'A');
    insertFront (&myL, &myVH, 'H');
    display (myL, myVH);

    printf("\n3. Insert Rear.\n");
    printf("   (Inserting Elements: C, I)\n\n");
    insertRear (&myL, &myVH, 'C');
    insertRear (&myL, &myVH, 'I');
    display (myL, myVH);   

    printf("\n4. Insert At.\n");
    printf("   (Inserting Elements: [0]E, [5]F, [3]G)\n\n");
    insertAt (&myL, &myVH, 0, 'E');
    insertAt (&myL, &myVH, 5, 'F');
    insertAt (&myL, &myVH, 3, 'G');
    display (myL, myVH); 

    printf("\n5. Insert Sorted.\n");
    printf("   (Inserting Elements: B, D)\n\n");
    insertSorted (&myL, &myVH, 'B');
    insertSorted (&myL, &myVH, 'D');
    display (myL, myVH);

    printf("\n6. Delete Front.\n");
    deleteFront (&myL, &myVH);
    display (myL, myVH);

    printf("\n7. Delete Rear.\n");
    deleteRear (&myL, &myVH);
    deleteRear (&myL, &myVH);
    display (myL, myVH);

    printf("\n8. Delete At.\n");
    printf("   (Deleting Positions: [2], [6])\n\n");
    deleteAt (&myL, &myVH, 2);
    deleteAt (&myL, &myVH, 6);
    display (myL, myVH);

    printf("\n");
    return 0;
}

//function definitions
//0. pre-define node next pointers to point to the next node
void initialize (LIST *L, virtualHeap *VH) {
    int i;
    for (i = 0; i < (MAX-1); ++i) {
        VH->NODES[i].next = i+1;
        VH->NODES[i].data = 0;
    }
    VH->NODES[i].data = 0;
    VH->NODES[i].next = -1;         //last node points to -1/NULL in LL
    VH->avail = 0;                  //initializes first avail elem is index 0
    *L = -1;                        //indicates the list to be empty
}

// 1. display data and what addresses the nodes are pointing to next
void display (LIST L, virtualHeap VH) {
    int i;
    if (L == -1) {
        printf("\tList is empty.\n");
        printf("\t*L = %d\n\tAvail = %d\n", L, VH.avail);
        printf("\n\tIDX = DATA: NEXT\n");
        for (i = VH.avail; i != -1; i = VH.NODES[i].next) {                         //for loop just for displayning list with garbage values
            printf("\t[%d] = %5c: %5d\n", i, VH.NODES[i].data, VH.NODES[i].next);
        }
    } else {
        printf("\t*L = %d\n\tAvail = %d\n", L, VH.avail);
        printf("\n\tIDX = DATA: NEXT\n");
        for (i = L; i != -1; i = VH.NODES[i].next) {
            printf("\t[%d] = %4c: %4d\n", i, VH.NODES[i].data, VH.NODES[i].next);
        }
    }
}

//2. insert at the very first of the list by changing the head pointer (fin)
void insertFront (LIST *L, virtualHeap *VH, char elem) {
    LIST temp;
    if (VH->avail != -1) {
        temp = VH->avail;                           //getting the allocated space
        VH->avail = VH->NODES[temp].next;           //vh->avail is now getting the temp nodes next pointer
        VH->NODES[temp].data = elem;                //inserting the new elem into available node
        VH->NODES[temp].next = *L;                  //temp->next is now pointing to whatever head was pointing
        *L = temp;                                  //head points to temp node
    } else {
        printf("\nList is Full.\n");
    }
}

//3. insert at the very end of the list via traversal (fin)
void insertRear (LIST *L, virtualHeap *VH, char elem) {
    LIST temp, *trav;
    if (VH->avail != -1) {
        for (trav = L; *trav != -1; trav = &(VH->NODES[*trav].next)) {}         //traverse to get ahold of the last node's index
        temp = VH->avail;                                                       //allocate space for temp node to be inserted
        VH->avail = VH->NODES[temp].next;                                       //update the avail to the next node via temp->next
        VH->NODES[temp].data = elem;                                            //insert the new elem into temp node
        VH->NODES[temp].next = -1;                                              //since temp node is last node, hard assign its next to -1(NULL)
        *trav = temp;                                                           //directly changing the previous last node's next to point to temp node
    } else {
        printf("\nList is Full.\n");
    }
}

//4. insert elem at given position into list
void insertAt (LIST *L, virtualHeap *VH, int pos, char elem) {
    LIST temp, *trav;
    int i;                                                                                          //counter for position
    if (VH->avail != -1) {
        for (i = 0, trav = L; *trav != -1 && i < pos; trav = &(VH->NODES[*trav].next), ++i) {}      //value of counter i is now position to insert, trav is node to point to temp
        temp = VH->avail;                                                                           //allocate space for temp node
        VH->avail = VH->NODES[temp].next;                                                           //udpdate the avail to the next available node currently pointed by temp->next
        VH->NODES[temp].data = elem;                                                                //assign element into temp node
        VH->NODES[temp].next = *trav;                                                               //temp->next will get whate trav was pointing to
        *trav = temp;                                                                               //directly assigning trav to point to temp
    }
}
//5. insert an element in its sorted position assuming the list is sorted
void insertSorted (LIST *L, virtualHeap *VH, char elem) {
    LIST temp, *trav;
    if (VH->avail != -1) {
        for (trav = L; *trav != -1 && elem > VH->NODES[*trav].data; trav = &(VH->NODES[*trav].next)) {}     //loops until elem is less than the next node
        temp = VH->avail;                                                                                   //allocate space for node to insert
        VH->avail = VH->NODES[temp].next;                                                                   //update value of avail
        VH->NODES[temp].data = elem;                                                                        //assign elem into node
        VH->NODES[temp].next = *trav;                                                                       //temp->next will get the next node that is of greater value than elem
        *trav = temp;                                                                                       //link temp node into list
    }
}

//6. delete the first node of the list by declaring it available
void deleteFront (LIST *L, virtualHeap *VH) {
    LIST temp;                                      //holds what prev next pointer of node to delete
    if (*L != -1) {                                 //if list is not empty == if there is something to delete
        temp = *L;                                  //temp will get the node to be deleted, in this case the first node
        *L = VH->NODES[temp].next;                  //head will get the node that temp is pointing to 
        VH->NODES[temp].next = VH->avail;           //temp node will point to the next available node
        VH->avail = temp;                           //the available node is now the node that was "deleted"
    }
}

//7. delete the last element of the list by trabversing to the second to the last element
void deleteRear (LIST *L, virtualHeap *VH) {
    LIST temp, *trav;
    if (*L != -1) {
        for (trav = L; VH->NODES[*trav].next != -1; trav = &(VH->NODES[*trav].next)) {}         //loops to travers to the second to the last element
        temp = *trav;                                                                           //temp will get the "address" of the very last element
        *trav = -1;                                                                             //assign the second to the last element to point to -1(NULL)
        VH->NODES[temp].next = VH->avail;                                                       //temp->next will point to previous avail
        VH->avail = temp;                                                                       //declare the last node as available
    }
}

//8. traverse the list until reached the given position
void deleteAt (LIST *L, virtualHeap *VH, int pos) {
    LIST temp, *trav;                                               //temp holds the address of index to delete, *trav holds address of cell pointing to temp
    int i;
    if (*L != -1) {
        for (trav = L, i = 0; VH->NODES[*trav].next != -1 && i < pos; trav = &(VH->NODES[*trav].next), ++i) {}
        temp = *trav;                                               //temp gets the node to delete
        *trav = VH->NODES[*trav].next;                              //"pointing over", node pointing to node to delete now re-points over to point to next
        VH->NODES[temp].next = VH->avail;                           //temp->next now points to the current avail
        VH->avail = temp;                                           //assigning the current temp to be the new avail
    }
}