/*  Author:         Fabioila C. Villanueva
    Description:    Priority Queue (MAXHEAP) - a Partially Order Tree and Heap Implementation
    Date:           04/03/24
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 15

//structure definition
typedef char STRING[15];

typedef struct {
    STRING nickName;
    int priorityNum;
} elemType;

typedef struct {            //my priority queue of names
    elemType list[MAX];
    int lastIdx;
} heapPQ;

typedef enum {FALSE, TRUE} Boolean;

//function prototypes
heapPQ initializeHeap (void);
void displayMaxHeap (heapPQ heap);
int parentIdx (int childIdx);
int leftChildIdx (int parentIdx);
int rightChildIdx (int parentIdx);
void insertIntoHeap (heapPQ *heap, elemType elem);
void heapSort (heapPQ *heap);
elemType deleteMax (heapPQ *heap);
void heapify (heapPQ *heap, int subRoot);

int main () {
    system("cls");
    printf("\n<< START >>\n\n");

    heapPQ maxHeap = initializeHeap ();
    Boolean ans = FALSE;
    elemType mTemp;

    //! initialize
    printf("00. INITIALIZE THE POT\n");
    if (maxHeap.lastIdx == -1) {
        printf("\tInitialized successfully.\n");
    } else {
        printf("\tError during initialization.\n");
    }

    //! populate empty tree
    printf("\n01. POPULATE THE EMPTY POT\n");
    // do {
    //     printf("\tEnter name: ");
    //     fflush (stdin);
    //     fgets(mTemp.nickName, sizeof (STRING), stdin);
    //     mTemp.nickName[strcspn (mTemp.nickName, "\n")] = '\0';
    //     printf("\tHello %s, kindly enter a number: ", mTemp.nickName);
    //     scanf("%d", &mTemp.priorityNum);
        
    //     printf("\t...adding you in queue.\n\n");
    //     insertIntoHeap (&maxHeap, mTemp);

    //     printf("\tRegister a new customer? <1-yes: 0-no>: ");
    //     scanf("%d", &ans);
    // } while (ans != FALSE);
    printf("\tPopulating and making max heap via insertAll given an array.\n");
    elemType tempArr[MAX] = {   
        {"Reyna",       6},
        {"Sova",        2},
        {"Astra",       9},
        {"Brimstone",   4},
        {"Deadlock",    2},
        {"Skye",        0},
        {"Fade",        6},
        {"Omen",        10},
        {"Clove",       8},
        {"Sage",        1},
        {"Harbor",      12},
        {"Jett",        4},
        {"Iso",         3},
        {"Kay-O",       1},
        {"Killjoy",     9}
    };
    int x;
    for (x = 0; x < MAX; ++x) {
        insertIntoHeap (&maxHeap, tempArr[x]);
    }

    // printf("\n");
    // system("pause");

    printf("\n02. POST-POPULATE: Max Heap\n");
    displayMaxHeap (maxHeap);

    //! in-place sorting
    printf("\n03. HEAP SORT\n");
    printf("\tPerforming heap sort.\n");
    heapSort (&maxHeap);

    displayMaxHeap (maxHeap);

    printf("\n\n<< END >>\n");
    return 0;
}

/*************************************************************************************
 *  Heapsort is populated via insertAll then in place sorting via calling deleteMin  *
 *************************************************************************************/

heapPQ initializeHeap (void) {
    heapPQ temp = {.lastIdx = -1};
    return temp;
}

void displayMaxHeap (heapPQ heap) {
    if (heap.lastIdx != -1) {
        printf("\t<< DISPLAYING PRIORITY QUEUE >>\n");
        printf("\t%-3s\t", "IDX");
        printf("%-10s", "PRIONUM");
        printf("%-10s", "NICKNAME");
        int x;
        for (x = 0; x <= heap.lastIdx; ++x) {
            printf("\n\t%2d\t", x);
            printf("%-10d", heap.list[x].priorityNum);
            printf("%-10s", heap.list[x].nickName);
        }
    } else {
        printf("\tThe Priority Queue is empty.\n");
    }
}

int parentIdx (int childIdx) {
    return (childIdx - 1) / 2;
}

int leftChildIdx (int parentIdx) {
    return (2 * parentIdx) + 1;
}

int rightChildIdx (int parentIdx) {
    return (2 * parentIdx) + 2;
    // return (leftChildIdx (parentIdx)) + 1;
}

void insertIntoHeap (heapPQ *PQ, elemType elem) {                                                   //making tree a POT per insertion
    //swapping method
    if (PQ->lastIdx < MAX-1) {                                                                      //if there is still space to insert
        PQ->list[++(PQ->lastIdx)] = elem;                                                           //insert the element at end

        int idx;                                                                                    //insertAll process
        for (idx = PQ->lastIdx; parentIdx(idx) >= 0 && PQ->list[parentIdx (idx)].priorityNum < PQ->list[idx].priorityNum; idx = parentIdx (idx)) {
            elemType temp = PQ->list[idx];
            PQ->list[idx] = PQ->list[parentIdx(idx)];
            PQ->list[parentIdx(idx)] = temp;
        }
    }

    //shifting method
    // if (PQ->lastIdx < MAX-1) {
    //     int trav;
    //     for (trav = ++(PQ->lastIdx); parentIdx (trav) >= 0 && elem.priorityNum > PQ->list[parentIdx (trav)].priorityNum; trav = parentIdx (trav)) {
    //         PQ->list[trav] = PQ->list[parentIdx (trav)];
    //     }
    //     PQ->list[trav] = elem;
    // }
}

void heapSort (heapPQ *heap) {
    int origLastIdx = heap->lastIdx;                          //store the original lastIndex of the heap
    while (heap->lastIdx > 0) {                               //while there is still an element to swap the root with
        heap->list[heap->lastIdx] = deleteMax (heap);         //assign what delete max returns to the index after the unsorted part of the array
    }
    heap->lastIdx = origLastIdx;
}

elemType deleteMax (heapPQ *heap) {
    elemType temp = heap->list[0];                              //temp gets root priority
    heap->list[0] = heap->list[(heap->lastIdx)--];              //updating the last index of the unsorted portion of the array and having new root

    if (heap->lastIdx > 0) {                                    //seems quite redundant to check
        heapify (heap, 0);                                      //heapifying with new root (pushdown into proper position)
    }
    return temp;
}

void heapify (heapPQ *heap, int subRoot) {
    int trav, idx;
    for (trav = subRoot; leftChildIdx (trav) <= heap->lastIdx; trav = idx) {                                                        //if there is atleast a child to compare
        idx = (heap->list[leftChildIdx (trav)].priorityNum > heap->list[trav].priorityNum) ? leftChildIdx (trav): trav;             //if leftchild's priority is higher than its parent, assign  to idx
        if (rightChildIdx (trav) <= heap->lastIdx && heap->list[rightChildIdx (trav)].priorityNum > heap->list[idx].priorityNum) {  //if there exists a rightchild, then there is also a left child; thus compare
            idx = rightChildIdx (trav);                                                                                             //comparison between right child and whatever idx was
        }

        if (idx != trav) {                          //if idx is not trav or the parent itself but rather an index of a child, then swap
            elemType temp = heap->list[idx];
            heap->list[idx] = heap->list[trav];
            heap->list[trav] = temp;
        } else {                                    //if idx remains parent (if theere was never a child with higher priority), then do not swap swap and terminate creatively
            idx = heap->lastIdx;
        }
    }
}