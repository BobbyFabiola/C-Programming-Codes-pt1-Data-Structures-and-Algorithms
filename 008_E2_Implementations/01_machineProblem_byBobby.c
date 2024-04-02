/******************************************************************
 * Project Name:  	List, Set and Dictionary                      *
 * Programmer  :  	Fabiola C. Villanueva                         *
 * Date Completed: 	03/07/24 1200pm - 03/09/24 0330am             *
 ******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VH_SIZE     0XC    //size of Virtual Heap
#define OPEN_DSIZE  0XA    //size of Open Hash Table
#define CLOSE_DSIZE 0XC    //size of Close Hash Table
#define LIST_SIZE   0XF    //size of the array implementation of List

/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct {  			// FOR ELEMTYPE
	char name[24];          // Chocolate name  
 	int  weight;            // Chocolate weight in grams  
}chocoDesc;
 
typedef struct {
   	char prodID[8];         //  product ID uniquely identifies the products; EMPTY or DELETED   
  	chocoDesc prodDesc;     //  product description 
 	float prodPrice;        //  product price 
  	int prodQty;            //  product count or quantity   
}product;                   //  product record  

typedef struct {
	product elem;            
	int next;                
}prodNode;                 // Product node, used in cursor-based implementation of Set  

/************************
 * Virtual Heap         *
 ************************/
typedef struct {
   prodNode VH_node[VH_SIZE];
   int avail;
}VHeap;

/******************************************
 * Cursor-Based Implementation of SET     *
 ******************************************/
typedef struct {
   int elemIndex;        // index of the 1st element in the set  
   int count;            // holds the actual number of elements in the set  
   VHeap *VHptr;         // holds the pointer to the virtual heap  
}cursorSet;            

/********************************************
 * Open Hashing Implementation of Dictionary*
 ********************************************/
typedef struct {
	int header[OPEN_DSIZE];  // array of sets   
	int count;               // total number of elements in the dictionary  
	VHeap *dicVHptr;         // holds the pointer to the virtual heap  
}openDic;


/**********************************************
 * Closed Hashing with 2 pass loading          *
 **********************************************/
#define EMPTY   "empty"     // stored in product ID field  
#define DELETED  "del"      // stored in product ID field
 
typedef product closeDic[CLOSE_DSIZE];   //Definition of the closed hash dictionary
  
typedef struct {
	product prod[LIST_SIZE];
	int last;   //index of the last element; -1 if list is empty	
}List;



/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
//?---Problem #1 ---
void initVHeap(VHeap *VH);
cursorSet initCursorSet(VHeap *VH);
void displayVHeap(VHeap V);
void displaySet(cursorSet A);

//?---Problem #2 ---
int mallocInVHeap(VHeap *VH);
void insertSorted(cursorSet *A, product P);
void populateSet(cursorSet *A);

//?---Problem #3 ---
int openHash(char prodID[]);                
openDic initOpenDict(VHeap *VH);
openDic convertToOpenDict(cursorSet *A);
void displayOpenDict(openDic D);

//?---Problem #4 ---
void freeInVHeap(VHeap *VH, int ndx);
void deleteDict(openDic *D, char IDen[]);

//?---Problem #5 ---
int closeHash(char ID[]);
void initCloseDict(closeDic CD);
closeDic * convertToCloseDict(openDic *D);	
void displayCloseDict(closeDic CD);


 
/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *                                                                                  *
 ***********************************************************************************/
 int main( ) {	
	system("cls");
 /*---------------------------------------------------------------------------------
 * 	Problem #1 ::  1) Initializes the virtual heap and the cursor Set             *
 *                 2) Displays the contents  virtual heap and cursor Set          *
 *--------------------------------------------------------------------------------*/
 	printf("Problem #1:: "); 
 	printf("\n------------");
 	//Declare variables needed for Problem #1
	VHeap mVH;
	cursorSet mCurSet;
 	 
 	//Function Calls for Problem #1
	initVHeap (&mVH);
	mCurSet = initCursorSet (&mVH);
	displayVHeap (mVH);
	displaySet (mCurSet);

/*---------------------------------------------------------------------------------
 * 	Problem #2 ::  1) Populates the Cursor set which is sorted in ascending order *
 *                    according to ID                                             *
 *                 2) Displays the Cursor set                                     * 
 *--------------------------------------------------------------------------------*/	 
 	printf("\n\n\nProblem #2:: "); 
 	printf("\n------------\n");
	//Declare variables needed for Problem #2
	
 	//Function Calls for Problem #2
	populateSet (&mCurSet);
	displayVHeap (mVH);
	displaySet (mCurSet);

/*---------------------------------------------------------------------------------
 * 	Problem #3 ::  1) Converts the Cursor set into an Open Hash Dictionary        *      
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the empty Cursor set.                              * 
 *--------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #3:: "); 
 	printf("\n------------");
	//Declare variables needed for Problem #3
 	openDic mOpenCB;
	
 	//Function Calls for Problem #3
	mOpenCB = convertToOpenDict (&mCurSet);
	displayOpenDict (mOpenCB);
 
/*---------------------------------------------------------------------------------
 * 	Problem #4 ::  1) Perform 3 delete operations on the Open Hash Dictionary     *
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the Virtual Heap                                   * 
 *--------------------------------------------------------------------------------*/	
 	printf("\n\n\nProblem #4:: "); 
 	printf("\n------------");	
 //Declare variables needed for Problem #4
    char delete01[] = "1703";
    char delete02[] = "1358";    
	char delete03[] = "1601";
	
 
//Function Calls for Problem #4	    
    deleteDict (&mOpenCB, delete01);
	deleteDict (&mOpenCB, delete02);
	deleteDict (&mOpenCB, delete03);
	displayOpenDict (mOpenCB);
	displayVHeap (mVH);
    
/*------------------------------------------------------------------------------------
 * 	Problem #5 :: 1) Converts the Open Hash Dictionary into a Closed Hash Dictionary *
 *                2) Displays the Closed Hash Dictionary                             * 
 *                3) Displays the virtual heap                                       *
 *---------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #5:: ");
    printf("\n------------");
    //Declare variables needed for Problem #5
    closeDic *mCloseCB;							//product mCloseCb[];
    
    //Function Calls for Problem #5
	mCloseCB = convertToCloseDict (&mOpenCB);
	displayCloseDict (*mCloseCB);
	displayVHeap (mVH);
	
	printf("\n\n");
	return 0;
}


/************************************************************
 *  Problem 1:: Function Definitions                          *
 ************************************************************/
//?
 void initVHeap(VHeap *V) {
 	V->avail = VH_SIZE - 1;
	int x;
	for (x = V->avail; x > 0; --x) {
		strcpy(V->VH_node[x].elem.prodID, "    ");
		V->VH_node[x].next = x-1;
	}
	V->VH_node[x].next = -1;
 }

//?
cursorSet initCursorSet(VHeap *VH) {
	cursorSet newCS;
	newCS.VHptr = VH;
	if (newCS.VHptr != NULL) {
		newCS.elemIndex = -1;
		newCS.count = 0;
	}
	return newCS;     
}

//?
void displayVHeap(VHeap V) {
	//Variable Declaration here
	int i,j;

    printf("\n\nDetails of the Virtual Heap :: ");
    printf("\n------------------------------");
    printf("\nAvailable Index  ::  %d", V.avail  );       	//Complete this statement
	printf("\nVHeap Address    ::  %p" , &V );      		//Complete this statemet
	
    printf("\n\n%10s", "Index");
    printf("%10s", "Prod ID");
    printf("%15s", "Next Field");
	printf("\n%10s%10s%15s", "-----", "-------","----------");	
     
    //Write your code here 
	for(i=0; i<VH_SIZE; i++){
		printf("\n%8d%10s%13d",i, V.VH_node[i].elem.prodID, V.VH_node[i].next);
	}
	
	printf("\n\n"); system("Pause");
}

//?
void displaySet(cursorSet A) {
	int x;
	product p;
	
	printf("\n\nDetails of the Set :: ");
	printf("\n---------------------");
	printf("\nNo. of elements ::  %d", A.count );      //Complete this code
	printf("\n\n %-7s ", "ID");
	printf("%-12s","Choco Name");
	printf("%-15s","Choco Weight");
	printf("%-10s","VHeap Idx");
	printf("\n%-7s  %-12s%-15s%-10s", "----  ", "----------", "------------", "---------");

	// Write your code here
	int idx;
	for (x = A.elemIndex; x != -1; x = A.VHptr->VH_node[x].next) {
		printf("\n%-7s", A.VHptr->VH_node[x].elem.prodID);
		printf("%12s", A.VHptr->VH_node[x].elem.prodDesc.name);
		printf("%10d", A.VHptr->VH_node[x].elem.prodDesc.weight);
		printf("%10d", x);
	}
	 
	printf("\n\n"); system("Pause");	
}


/************************************************************
 *  Problem 2:: Function Definitions                         *
 ************************************************************/
//?
int mallocInVHeap(VHeap *VH) {
	int idx = VH->avail;
	if (idx != -1) {
		VH->avail = VH->VH_node[idx].next;
	}
	return idx;
}

//?
void insertSorted(cursorSet *A, product P) {
	if (A->count < VH_SIZE) {					//then there is still space
		int *trav;
		for (trav = &A->elemIndex; *trav != -1 && strcmp(A->VHptr->VH_node[*trav].elem.prodID, P.prodID) < 0; trav = &A->VHptr->VH_node[*trav].next) {}
		if (strcmp (A->VHptr->VH_node[*trav].elem.prodID, P.prodID) == 0) {
			printf("Product with ID: %s already exists in the set.\n", P.prodID);
		} else {
			int temp = mallocInVHeap (A->VHptr);
			A->VHptr->VH_node[temp].elem = P;
			A->VHptr->VH_node[temp].next = *trav;
			*trav = temp;
			A->count++;
		}
	} else {
		printf("No available space. Product with ID : %s cannot be inserted.\n", P.prodID);
	}
}

//?
void populateSet(cursorSet *A) {
	const int COUNT = 15;
	product data[] = { 	{"1701", {"Toblerone", 135}, 150.75, 20},
						{"1356", {"Ferrero", 200}, 250.75, 85},
						{"1109", {"Patchi", 50}, 99.75, 35},
						{"1550", {"Cadbury", 120}, 200.00, 30},
						{"1807", {"Mars", 100}, 150.75, 20},
						{"1201", {"Kitkat", 50}, 97.75, 40},
						{"1450", {"Ferrero", 100},150.50, 50},
						{"1701", {"Toblerone", 50}, 90.75, 80},
						{"1601", {"Meiji", 75}, 75.50, 60},
						{"1310", {"Nestle", 100}, 124.50, 70},
						{"1807", {"Valor", 120}, 149.50, 90},
						{"1455", {"Tango", 75}, 49.50, 100},
						{"1703", {"Toblerone", 100}, 125.75, 60},
						{"1284", {"Lindt", 100}, 250.75, 15},
						{"1688", {"Guylian", 50}, 99.75, 35},
					
		              };
    //Inserts each element of the array to the cursor set
    //Write your code here!!
   int x;
   for (x = 0; x < COUNT; ++x) {
		insertSorted (A, data[x]);
   }
}


/************************************************************
 *  Problem 3:: Function Definitions                        *
 ************************************************************/
//?
int openHash(char prodID[]) { 
    int x, sum;
	for (x = 0, sum = 0; x < strlen (prodID) ||  prodID[x] != '\0'; sum += prodID[x] - '0', ++x) {}
	return sum % OPEN_DSIZE;
}

//?
openDic initOpenDict(VHeap *VH) {
	openDic openCB;
	openCB.dicVHptr = VH;
	if (openCB.dicVHptr != NULL) {
		// printf("\nsuccess init of open dict\n");
		openCB.count = 0;
		int x;
		for (x = 0; x < OPEN_DSIZE; ++x) {
			openCB.header[x] = -1;
		}
	}
	return openCB;
}

//?
openDic convertToOpenDict(cursorSet *A) {
	openDic openCB = initOpenDict (A->VHptr);
	int *node;
	for (node = &A->elemIndex; *node != -1;) {
		int temp = *node;
		*node = A->VHptr->VH_node[temp].next;
		int hashKey = openHash (A->VHptr->VH_node[temp].elem.prodID);

		int *travSort;
		for (travSort = &openCB.header[hashKey]; *travSort != -1 
			&& strcmp (openCB.dicVHptr->VH_node[*travSort].elem.prodID, openCB.dicVHptr->VH_node[temp].elem.prodID) < 0;
			travSort = &openCB.dicVHptr->VH_node[*travSort].next) {}

		openCB.dicVHptr->VH_node[temp].next =*travSort;
		*travSort = temp;
		openCB.count++;
	}
	return openCB;
}

//?
void displayOpenDict(openDic D) {
	//Variable declaration here 
	
	printf("\n\nDetails of the Open Hash Dictionary:: ");
	printf("\n-------------------------------------");
	
	printf("\nNo. of elements :: %d", D.count);
	printf("\n\n%-7s", "GROUPS");
	printf("%15s","ID Numbers");
	printf("\n%-7s%15s", "------","----------");
	
	//Write your code here
	int x;
	for (x = 0; x < OPEN_DSIZE; ++x) {
		int trav;
		printf("\nGROUP[%d] :: ", x);
		for (trav = D.header[x]; trav != -1; trav = D.dicVHptr->VH_node[trav].next) {
			printf(" %s ", D.dicVHptr->VH_node[trav].elem.prodID);
		}
	}

    printf("\n\n"); system("Pause");	
}


/************************************************************
 *  Problem 4:: Function Definitions                        *
 ************************************************************/
//?
void freeInVHeap(VHeap *VH, int ndx) {
	VH->VH_node[ndx].next = VH->avail;
	strcpy (VH->VH_node[ndx].elem.prodID, "    ");
	VH->avail = ndx;
}

//?
void deleteDict(openDic *D, char IDen[]) {
	int hashKey = openHash (IDen);

	int *trav, idx;
	for (trav = &D->header[hashKey]; *trav != -1 && 
		strcmp (D->dicVHptr->VH_node[*trav].elem.prodID, IDen) != 0;
		trav = &D->dicVHptr->VH_node[*trav].next) {}

	if (*trav != -1) {
		idx = *trav;
		*trav = D->dicVHptr->VH_node[idx].next;
		strcpy (D->dicVHptr->VH_node[idx].elem.prodID, "    ");
		D->count--;
		freeInVHeap (D->dicVHptr, idx);
	}
}


 /************************************************************
 *  Problem 5:: Function Definitions                         *
 ************************************************************/
//?
int closeHash(char ID[]) {
    int x, sum;
	for (x = 0, sum = 0; ID[x] != '\0' || x < strlen (ID); sum += ID[x] - '0', ++x) {}
	return sum % CLOSE_DSIZE;
}

//?
void initCloseDict(closeDic CD) {
	int x;
	for (x = 0; x < CLOSE_DSIZE; ++x) {

		strcpy (CD[x].prodID, EMPTY);
		strcpy (CD[x].prodDesc.name, " ");
	}
}

//?
closeDic * convertToCloseDict(openDic *D) {
	closeDic *closeCB = malloc (sizeof (product) * CLOSE_DSIZE);
	List tempLoad = {.last = -1};
	if (closeCB != NULL) {
		initCloseDict (*closeCB);

		int x;
		for (x = 0; x < OPEN_DSIZE  && D->count != 0; ++x) {
			if (D->header[x] != -1) {
				int *trav;
				for (trav = &D->header[x]; *trav != -1; ) {
					product chocoElem = D->dicVHptr->VH_node[*trav].elem;
					int temp = *trav;
					*trav = D->dicVHptr->VH_node[*trav].next;
					freeInVHeap (D->dicVHptr, temp);
					--(D->count);

					int hashKey = closeHash (chocoElem.prodID);
					if (strcmp ((*closeCB)[hashKey].prodID, EMPTY) == 0) {
						(*closeCB)[hashKey] = chocoElem;
					} else if (tempLoad.last < LIST_SIZE) {
						tempLoad.prod[++(tempLoad.last)] = chocoElem;
					}
				}
			}
		}
		for (x = 0; x <= tempLoad.last; ++x) {
			int idx = closeHash (tempLoad.prod[x].prodID);
			int sl;
			for (sl = 1; sl != -1 && strcmp ((*closeCB)[idx].prodID, EMPTY) != 0 
				&& strcmp ((*closeCB)[idx].prodID, DELETED) != 0; idx = (idx + 1) % CLOSE_DSIZE, ++sl) {}
			if (sl != CLOSE_DSIZE) {
				(*closeCB)[idx] = tempLoad.prod[x];
			}
		}
	}
	return closeCB;
}	

//?
void displayCloseDict(closeDic CD) {
 	//Variable declaration here
 	
 	
	printf("\n\nDetails of Closed Hash Dictionary :: ");
	printf("\n-------------------------------------");
	printf("\n\n%-6s", "Index");
	printf("%-10s", "ChocoID");
	printf("%-15s", "Choco Name");
	printf("\n%-6s%-10s%-15s", "-----", "-------", "----------"); 
	
	//Write your code here
	int x;
	for (x = 0; x < CLOSE_DSIZE; ++x) {
		printf("\n%3d%10s%15s", x, CD[x].prodID, CD[x].prodDesc.name);
	}
	 
	printf("\n\n"); system("Pause");
 
}