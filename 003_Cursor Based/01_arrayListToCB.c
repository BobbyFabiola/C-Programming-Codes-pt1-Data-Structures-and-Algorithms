/*   Author:   Fabiola Villanueva
 *   Description:   Create an Unsorted Array List of Student Data, Then Inserted 
 *                  Sorted Unique Students Into a Cursor Based List in Ascending Order
 *   Date:          Nov 21, 2023 (Day of DSA PreFinals)
 */

#include <stdio.h>
#include <string.h>
#define VH_MAX 0XFF
#define MAX 0xA

//typedef defintions
typedef enum {FALSE, TRUE} BOOL;

typedef struct {
     char FN[24], LN[16], MI;
} nameType;

typedef struct {
     char ID[10];
     nameType name;
     char course[8];
     int yrLevel;
} studRec;

typedef struct node {         //definition of array list
     studRec data[MAX];
     int studCtr;             //actual elem count
} *ArrayList;

// typedef struct {              //definition of virtual heap 
//      studRec stud;
//      int link;                //-1 if not pointing to any CBnode
// } CBnode;

// typedef struct {
//      CBnode heap[VH_MAX];
//      int avail;
// } *VHeap;

//function prototypes

int main () {
     ArrayList list;



     return 0;
}

//function definitions