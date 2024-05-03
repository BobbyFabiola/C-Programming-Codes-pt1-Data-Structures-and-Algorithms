//! Author: 		Fabiola C. Villanueva
//! Description:	
//! Date: 			

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VH_SIZE     0XF   //size of Virtual Heap
#define MAX         0xF  // MAX size of the list
/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct {  
	char name[24];          // Chocolate name  
 	int  weight;            // Chocolate weight in grams  
}chocoDesc;
 
typedef struct {
   char prodID[8];          //  product ID uniquely identifies the products; EMPTY or DELETED   
  	chocoDesc prodDesc;     //  product description 
 	float prodPrice;        //  product price 
  	int prodQty;            //  product count or quantity   
}product;                   //  product record  

/**************************************
 * Cursor-based implementation of BST *
 **************************************/
typedef int BST;   //Definition of BST
 
typedef struct {
  product elem;            
  int LC;        //holds the index of the left child
  int RC;        //holds the index of the Right Child; USE as link to next node in the Virtual heap               
}BSTnode;        // Product node, used in cursor-based implementation of BST  


/************************
 * Virtual Heap         *
 ************************/
typedef struct {
   BSTnode VH_node[VH_SIZE];
   int avail;
}VHeap;

/************************
 * List definition       *
 ************************/
typedef struct {
	product prod[MAX];
	int last;     //index of the last element	
}ArrayList;

      
/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
//---Problem #3 ---
BST createMagicalBSTvheap(VHeap *VH);    // Complete
void displayVHeap(VHeap V);              // Partially coded
void displayProduct(product P);          // Complete
ArrayList convertBstToList(BST *B, VHeap *VH);   //Removes from the BST smallest element to the biggest until BST is empty
void displayList(ArrayList A);                //displays the elements of the list
 
 
int main( ) {	
	/*---------------------------------------------------------------------------------
	* 	Problem #3 ::  1) Populate the Virtual heap and the BST by calling the function *
	*                    createMagicalBSTvheap()                                       *  
	*                 2) Call displayVHeap() to show the state of the virtual heap     * 
	*                 3) Call convertBstToList() and displayList()                     *
	*                 4) Call displayVHeap() to show the state of the virtual heap     * 
	*--------------------------------------------------------------------------------*/
	printf("\n\n\nProblem #3:: "); 
	printf("\n------------");
	//Declare variables needed for Problem #1

	//Write your code here


}

/************************************************************
 *  Problem 1:: Function Definitions                          *
 ************************************************************/
BST createMagicalBSTvheap(VHeap *VH) {
	VHeap v = { { {{"1356", {"Ferrero", 200}, 250.75, 85},  8,  2 },
					{{"1703", {"Toblerone", 100}, 125.75, 60 }, -1, -1 },
					{{"1550", {"Cadbury", 120}, 200.00, 30}, 3, 13 },
					{{"1450", {"Ferrero", 100},150.50, 50},  4, 10 }, 
					{{"1310", {"Nestle", 100}, 124.50, 70}, -1, -1 }, 
					{{"1688", {"Guylian", 50}, 99.75, 35}, -1, -1 },
					{{"1901", {"Reese", 135}, 150.75, 20}, -1, 11 },
					{{"1701", {"Toblerone", 50}, 90.75, 80},  0,  9 },
					{{"1109", {"Patchi", 50}, 99.75, 35}, -1, 14 },
					{{"1807", {"Mars", 100}, 150.75, 20},  1, -1 }, 
					{{"1455", {"Tango", 75}, 49.50, 100}, -1, -1 }, 
					{{"1150", {"Valor", 120}, 149.50, 90}, -1, -1 },
					{{"1284", {"Lindt", 100}, 250.75, 15}, -1, -1 }, 
					{{"1601", {"Meiji", 75}, 75.50, 60}, -1,  5 }, 
					{{"1201", {"Kitkat", 50}, 97.75, 40}, -1, 12 },
				} ,  6 };
	*VH = v;
	return 7;	 	    
}
 
void displayProduct(product P) {
	printf("\n%-8s", P.prodID);
    printf("%-10s", P.prodDesc.name);
    printf("%-6d", P.prodDesc.weight);
    printf("%-10.2f", P.prodPrice);
    printf("%-6d", P.prodQty);	
}
 
 
void displayVHeap(VHeap V) {
	int x;

    printf("\n\nDetails of the Virtual Heap :: ");
    printf("\n------------------------------");
    printf("\nAvailable Index  :: %d",  V.avail);
	
    printf("\n\n%10s", "Index");
    printf("%10s", "Prod ID");
    printf("%15s", "LC Field");   
	printf("%15s", "RC Field");
	printf("\n%10s%10s%15s%15s", "-----", "-------","--------","--------");	
     
	//Write code here 
	 
	 
	printf("\n\n"); system("Pause");
}
 
ArrayList convertBstToList(BST *B, VHeap *VH) {   //Removes from the BST smallest element to the biggest until BST is empty 
      //Write code here

}

void displayList(ArrayList A) {

     //Write code here

}


 
