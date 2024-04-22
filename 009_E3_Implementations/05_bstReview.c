#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct node {
	int data;
	int LC;
	int RC;
	int link;
}NodeType;

typedef struct {
	NodeType arr[MAX];
	int avail;
}VirtualHeap;

typedef int BST;

//Memory operations
void initVH(VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int node);

//BST operations
void initBST(BST *A);
void insert(BST *A, VirtualHeap *VH, int newDat);
void deleteNode(BST *A, VirtualHeap *VH, int target);
void member(BST *A, VirtualHeap *VH);
void preorder(BST A, VirtualHeap VH);
void postorder(BST A, VirtualHeap VH);
void inorder(BST A, VirtualHeap VH);
int main() 
{
	VirtualHeap myVH;
	BST myBST;
	initVH(&myVH);
	initBST(&myBST);
	insert(&myBST, &myVH, 5);
	insert(&myBST, &myVH, 2);
	insert(&myBST, &myVH, 7);
	deleteNode(&myBST, &myVH, 2);
	deleteNode(&myBST, &myVH, 5);
	deleteNode(&myBST, &myVH, 7);
	preorder(myBST, myVH);
	//postorder(myBST, myVH);
	//inorder(myBST, myVH);
	
	return 0;
}

void initVH(VirtualHeap *VH) 
{
	int x;
	for(x = 0; x < MAX; x++) {
		VH->arr[x].link = x+1;
	}
		VH->arr[MAX-1].link = -1;
		VH->avail = 0;
}

int allocSpace(VirtualHeap *VH)
{
	int retVal = VH->avail;
	if(VH->avail != -1) {
		retVal = VH->avail++;
	}
	return retVal;
}

void deallocSpace(VirtualHeap *VH, int node) 
{
	VH->arr[node].link = VH->avail;
	VH->avail = node;
}

void initBST(BST *A)
{
	(*A) = -1;
}

void insert(BST *A, VirtualHeap *VH, int newDat)
{
	BST *trav = A;
	while((*trav) != -1 && VH->arr[(*trav)].data != newDat) {
		if(VH->arr[(*trav)].data > newDat) {
			trav = &VH->arr[(*trav)].LC;
		} else {
			trav = &VH->arr[(*trav)].RC;
		}
	}
	
	if((*trav) == -1) {	
		int newNode = allocSpace(VH);
		VH->arr[newNode].data = newDat;
		VH->arr[newNode].LC	= VH->arr[newNode].RC = (*trav);
		(*trav) = newNode;
	}
}

void deleteNode(BST *A, VirtualHeap *VH, int target) 
{
	BST *trav = A;
	while((*trav) != -1 && VH->arr[(*trav)].data != target) {
		if(VH->arr[(*trav)].data < target) {
			trav = &VH->arr[(*trav)].RC;
		} else {
			trav = &VH->arr[(*trav)].LC; 
		}
	}
	
	if((*trav) != -1) {
		if(VH->arr[(*trav)].LC != -1) {
			deallocSpace(VH, (*trav));
			(*trav) = VH->arr[(*trav)].RC;
		} else if (VH->arr[(*trav)].RC != -1) {
			deallocSpace(VH, (*trav));
			(*trav) = VH->arr[(*trav)].LC;
		} else {
			
		}
		deallocSpace(VH, (*trav));
		(*trav) = -1;
	}
}

void preorder(BST A, VirtualHeap VH) 
{	
	if(A != -1) {
		printf("%d", VH.arr[A].data);
		preorder(VH.arr[A].LC, VH);
		preorder(VH.arr[A].RC, VH);
	} 
}

void postorder(BST A, VirtualHeap VH) 
{	
	if(A != -1) {
		postorder(VH.arr[A].LC, VH);
		postorder(VH.arr[A].RC, VH);
		printf("%d", VH.arr[A].data);
	} 
}

void inorder(BST A, VirtualHeap VH) 
{	
	if(A != -1) {
		inorder(VH.arr[A].LC, VH);
		printf("%d", VH.arr[A].data);
		inorder(VH.arr[A].RC, VH);
	} 
}

void member(BST *A, VirtualHeap *VH);







