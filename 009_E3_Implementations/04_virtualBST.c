/*	Author: Fabiola Villanueva
 	Date: 04 / 11 / 24
	Description: Binary Search Trees in Cursor Based
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 15

//structure definition
typedef char STRING[15];

typedef struct {
	char ID[5];			//order of the nodes will be by ID
	STRING nickName;
} elemType;

typedef struct {
	elemType data;
	int leftChild;
	int rightChild;
} nodeType;

typedef struct {
	nodeType NODES[MAX];
	int avail;
} VH;

typedef int SET;		//index of first node 

typedef enum {TRUE, FALSE} Boolean;

//function prototypes
void initialize (VH *TREE, SET *S);
void displayPreOrder (VH TREE, SET S);
void insertElem (VH *TREE, SET *S, elemType elem);
void deleteElem (VH *TREE, int *S, elemType elem);
Boolean isMember (VH TREE, int S, elemType elem);

int allocSpace (VH *TREE);
void deallocSpace (VH *TREE, int x);

int main () {
	system("cls");
	VH mCBT;
	SET mSet;
	
	printf("<< START >>\n");
	printf("\n< INITIALIZE >\n");
	initialize (&mCBT, &mSet);
	if (mSet == -1) {
		printf("Succesfully Initialized Tree.\n");
	}
	
	elemType tempArr[MAX] = {   
        {"888", "Reyna"},
        {"223", "Sova"},
        {"967", "Astra"},
        {"124", "Brimstone"},
        {"122", "Deadlock"},
        {"101", "Skye"},
        {"660", "Fade"},
        {"120", "Omen"},
        {"656", "Clove"},
        {"111", "Sage"},
        {"132", "Harbor"},
        {"451", "Jett"},
        {"893", "Iso"},
        {"157", "Kay-O"},
        {"312", "Killjoy"}
    };
    
    printf("\n< POPULATE TREE & PRE-ORDER DISPLAY >\n");
    int x;
    for (x = 0; x < MAX; ++x) {
    	insertElem (&mCBT,&mSet, tempArr[x]);
	}
	printf("\tLC____________DATA____________RC\n");
	displayPreOrder (mCBT, mSet);
	
	printf("\n< DELETE ELEMENTS >\n");
	deleteElem (&mCBT, &mSet, tempArr[0]);
	deleteElem (&mCBT, &mSet, tempArr[5]);
	deleteElem (&mCBT, &mSet, tempArr[10]);

	printf("\tLC____________DATA____________RC\n");
	displayPreOrder (mCBT, mSet);

	printf("\n< CHECK MEMBERSHIP >\n");
	if (isMember (mCBT, mSet, tempArr[5]) == TRUE) {
		printf("Agent '%s - %s' IS a member.\n", tempArr[5].ID, tempArr[5].nickName);
	} else {
		printf("Agent '%s - %s' is NOT a member.\n", tempArr[5].ID, tempArr[5].nickName);
	}

	if (isMember (mCBT, mSet, tempArr[13]) == TRUE) {
		printf("Agent '%s - %s' IS a member.\n", tempArr[13].ID, tempArr[13].nickName);
	} else {
		printf("Agent '%s - %s' is NOT a member.\n", tempArr[13].ID, tempArr[13].nickName);
	}

	if (isMember (mCBT, mSet, tempArr[0]) == TRUE) {
		printf("Agent '%s - %s' IS a member.\n", tempArr[0].ID, tempArr[0].nickName);
	} else {
		printf("Agent '%s - %s' is NOT a member.\n", tempArr[0].ID, tempArr[0].nickName);
	}
	
	if (isMember (mCBT, mSet, tempArr[8]) == TRUE) {
		printf("Agent '%s - %s' IS a member.\n", tempArr[8].ID, tempArr[8].nickName);
	} else {
		printf("Agent '%s - %s' is NOT a member.\n", tempArr[8].ID, tempArr[8].nickName);
	}
	
	printf("\n<< END >>\n");
	return 0;
}

//function definitions

void initialize (VH *TREE, SET *S) {
	*S = -1;
	TREE->avail = 0;
	int x;
	for (x = 0; x < MAX; ++x) {
		TREE->NODES[x].leftChild = -1;
		TREE->NODES[x].rightChild = (x < MAX-1) ? x + 1: -1;
	}
}

void displayPreOrder (VH TREE, SET S) {
	if (S != -1) {
		printf("\t%2d [ %2d %-10s\t%s ] %2d\n", TREE.NODES[S].leftChild, S, TREE.NODES[S].data.nickName, TREE.NODES[S].data.ID, TREE.NODES[S].rightChild);
		displayPreOrder (TREE, TREE.NODES[S].leftChild);
		displayPreOrder (TREE, TREE.NODES[S].rightChild);
	}
}

void insertElem (VH *TREE, SET *S, elemType elem) {
	int *trav;
	if (TREE->avail != -1) {								//if there is still an available node
		for (trav = S; *trav != -1 && strcmp (TREE->NODES[*trav].data.ID, elem.ID) != 0; ) {
			trav = (strcmp(elem.ID, TREE->NODES[*trav].data.ID) < 0) ? &(TREE->NODES[*trav].leftChild): &(TREE->NODES[*trav].rightChild);
		}
		if (*trav == -1) {
			int temp = allocSpace (TREE);
			if (temp != -1) {
				TREE->NODES[temp].data = elem;
				TREE->NODES[temp].rightChild = -1;
				TREE->NODES[temp].leftChild = -1;
				*trav = temp;
			}	
		}
	}
}

int allocSpace (VH *TREE) {
	int temp = -1;
	if (TREE->avail != -1) {
		temp = TREE->avail;
		TREE->avail = TREE->NODES[temp].rightChild;
	}
	return temp;
}

void deleteElem (VH *TREE, int *S, elemType elem) {
	int *search;
	for (search = S; *search != -1 && strcmp (TREE->NODES[*search].data.ID, elem.ID) != 0; )  {
		search = (strcmp (elem.ID, TREE->NODES[*search].data.ID) < 0)? &(TREE->NODES[*search].leftChild): &(TREE->NODES[*search].rightChild);
	}
	if (*search != -1) {
		int temp = *search;
		if (TREE->NODES[temp].leftChild != -1 && TREE->NODES[temp].rightChild != -1) {
			int *trav;
			for (trav = &(TREE->NODES[temp].rightChild); *trav != -1 && TREE->NODES[*trav].leftChild != -1; trav = &(TREE->NODES[*trav].leftChild)) {}
			TREE->NODES[temp].data = TREE->NODES[*trav].data;
			temp = *trav;
			*trav = TREE->NODES[*trav].rightChild;
		} else {
			*search = (TREE->NODES[temp].leftChild != -1) ? TREE->NODES[temp].leftChild: TREE->NODES[temp].rightChild;
		}
		deallocSpace (TREE, temp);
		printf("Agent '%s - %s' has been deleted.\n", TREE->NODES[temp].data.ID, TREE->NODES[temp].data.nickName);
	}
}

void deallocSpace (VH *TREE, int x) {
	TREE->NODES[x].leftChild = -1;
	TREE->NODES[x].rightChild = TREE->avail;
	TREE->avail = x;
}

Boolean isMember (VH TREE, int S, elemType elem) {
	while(S != -1 && strcmp (elem.ID, TREE.NODES[S].data.ID) != 0) {
		S = (strcmp (elem.ID, TREE.NODES[S].data.ID) < 0) ? TREE.NODES[S].leftChild: TREE.NODES[S].rightChild;
	}
	return (S != -1) ? TRUE: FALSE;
}