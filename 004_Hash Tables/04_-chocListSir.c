/******************************************************************
 * Project Name:  Dictionary and Priority Queue                   *
 * Programmer  :  Put your Name here                              *
 * Date Completed: August 11, 2016                                *
 ******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 		0X20
#define SIZE 		0XC
#define PRIME_SIZE	0XD
#define SYN_SIZE    0X7
#define EMPTY		"empty"
#define DELETED		"deleted"
#define HEAPSIZE	0XA


/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef enum {TRUE, FALSE} boolean;

typedef struct {  
	char name[LENGTH];       /* Chocolate name */  
 	int  weight;             /* Chocolate weight in grams */
}chocoDesc;
 
typedef struct {
    char prodID[SIZE];      /*  product ID uniquely identifies the products; EMPTY or DELETED */ 
  	chocoDesc prodDesc;     /*  product description*/  
 	float prodPrice;        /*  product price*/  
  	int prodQty;            /* product count or quantity  */
}product;                   /* product record */

/* Closed hashing with separate synonym area */
typedef struct {
	product elem;           /* Element of the dictionary */
	int next;               /* pointer to a synonym */
}node;

typedef struct Dic {
 	node prime[PRIME_SIZE];   /* Prime Data Area, where elements are stored if slot is empty or deleted */
	node syn[SYN_SIZE];       /* Synonym Area, where elements are stored if prime data is occupied  */
	int avail;				  /* Holds the index of the first available node in the synonym area */		
}*Dictionary;


/* Priority Queue */
typedef struct {
	chocoDesc data[HEAPSIZE];
	int last;                   /* index of last element in the Heap or List */
}Heap;


/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
void initDictionary(Dictionary *D); 
void displayDictionary(Dictionary D);
 
int hash(char *IDen);
boolean isMember(Dictionary D, char *IDen);
void insertDic(Dictionary D, product P);
void populateDictionary(Dictionary D);
 
void deleteDic(Dictionary D, char *IDen); 

void initMaxHeap(Heap *H); 
void insertMaxHeap(Heap *H, chocoDesc C);
void populateMaxHeap(Heap *H, Dictionary D);
void displayMaxHeap(Heap H);
 
void swapChoco(chocoDesc *X, chocoDesc *Y) ;
void heapSort(Heap *H); 
 
/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *   4)  Uncomment or copy the print statement in each PROBLEM#  if the task is     *
 *       completed.                                                                 *
 ***********************************************************************************/
 int main( ) 
 {	
  /*-------------------------------------------------------------------------------
   * Write all variable declaration here.                                         *
   *------------------------------------------------------------------------------*/
   	Dictionary A;
   	
    char delete01[] = "170145";
    char delete02[] = "15507";
    product insert01 = {"1501978", {"Hersheys", 100}, 100.50, 10};
    product insert02 = {"99094", {"Lindt", 100}, 175.50, 80};
    Heap B;
   
  
/*---------------------------------------------------------------------------------
 * 	Problem #1 ::  Display the newly initialized dictionary.                      *
 *                                                                                * 
 *  printf("\n\n\nProblem #1:: ");                                                *
 *--------------------------------------------------------------------------------*/
 	 printf("\n\n\nProblem #1:: "); 
 	 initDictionary(&A);
 	 displayDictionary(A);
  	
  	 printf("\n\n\nProblem #2:: ");  
  	populateDictionary(A);
  	 displayDictionary(A);
    
    
  	deleteDic(A, delete01);
  	deleteDic(A, delete02);
  	printf("\n\n\nProblem #3:: After Delete ");   
  	displayDictionary(A);
  	
  	insertDic(A, insert01);
  	insertDic(A,insert02);
  	printf("\n\n\nProblem #3:: After Insert "); 
  	displayDictionary(A);
  	
  	initMaxHeap(&B); 
    populateMaxHeap(&B,A); system("cls");
    printf("Problem #4:: ");
    displayMaxHeap(B); system("cls");
    
    heapSort(&B);
    printf("\n\n\nProblem #5:: ");  
    displayMaxHeap(B);
/*---------------------------------------------------------------------------------
 * 	Problem #2 ::  Call populateDictionary() and display resulting dictionary.    *
 *                                                                                *
 *                                               *
 *--------------------------------------------------------------------------------*/
 
 
 /*---------------------------------------------------------------------------------
 * 	Problem #3 ::  Call deleteDic() two times passing delete01 and delete02        * 
 *                 variables and display resulting dictionary. Call insertDic two  *
 *                 times passing insert01 and insert02 variables and display       *
 *                 resulting dictionary.                                           *  
 *                                    *
 *                                   *
 *---------------------------------------------------------------------------------*/
 

/*---------------------------------------------------------------------------------
 * 	Problem #4 ::  Initialize and populate the max Heap and call displayMaxHeap().*
 *                                                                                *
 *                                                *
 *--------------------------------------------------------------------------------*/	
 
       	
	     
 
/*---------------------------------------------------------------------------------
 * 	Problem #5 ::  Perform heapSort and display the resulting sorted list of choco *
 *                 records.                                                        *
 *  printf("\n\n\nProblem #5:: ");                                                 *
 *---------------------------------------------------------------------------------*/		     
 
    
	
	getch();
	return 0;
}

/************************************************************
 *  Problem 1 Function Definitions                          *
 ************************************************************/

void initDictionary(Dictionary *D)
{
	(*D) = (Dictionary)malloc(sizeof(struct Dic));
	
	int i;
	for(i=0;i<PRIME_SIZE;i++){
		strcpy((*D)->prime[i].elem.prodID,EMPTY);
		(*D)->prime[i].next=-1;
	}
	for(i=SYN_SIZE-1;i>=0;i--){
		(*D)->syn[i].next = i-1;
	}
	(*D)->avail =SYN_SIZE-1;
	
}
void displayDictionary(Dictionary D)
{
int p,trav;
	printf("\n\n%-7s", "Index");
	printf("%-12s","Prime Area");
	printf("%-10s","Synonyms");
    for(p=0;p<PRIME_SIZE;p++){
         printf("\n%5d", p);    
         if(strcmp(D->prime[p].elem.prodID,EMPTY)==0 || strcmp(D->prime[p].elem.prodID,DELETED)==0){
               if(strcmp(D->prime[p].elem.prodID,DELETED)==0){
                     printf("%9s",D->prime[p].elem.prodID); 
               }else{
                     printf("%7s",D->prime[p].elem.prodID);
               }
         }else{
               if(strlen(D->prime[p].elem.prodDesc.name)==4){
                     printf("%6s",D->prime[p].elem.prodDesc.name);                                            
               }else if(strlen(D->prime[p].elem.prodDesc.name)==5){  
                     printf("%7s",D->prime[p].elem.prodDesc.name);
               }else if(strlen(D->prime[p].elem.prodDesc.name)==6){
                     printf("%8s",D->prime[p].elem.prodDesc.name); 
               }else if(strlen(D->prime[p].elem.prodDesc.name)==7){
                     printf("%9s",D->prime[p].elem.prodDesc.name); 
               }else if(strlen(D->prime[p].elem.prodDesc.name)==8){
                     printf("%10s",D->prime[p].elem.prodDesc.name); 
               }else{
                     printf("%11s",D->prime[p].elem.prodDesc.name);
               }

         } 
         if(D->prime[p].next!=-1){                    
              trav=D->prime[p].next;    
              while(trav!=-1){   
                  if(strlen(D->syn[trav].elem.prodDesc.name)==9){
                        printf("%16s",D->syn[trav].elem.prodDesc.name);                                         
                  }else if(strlen(D->syn[trav].elem.prodDesc.name)==6){
                        if(strlen(D->prime[p].elem.prodID)==7){
                            printf("%11s",D->syn[trav].elem.prodDesc.name);
                        }else{
                            printf("%9s",D->syn[trav].elem.prodDesc.name);
                        }
                  }else if(strlen(D->syn[trav].elem.prodDesc.name)==7){                                  
                        printf("%13s",D->syn[trav].elem.prodDesc.name); 
                  }else if(strlen(D->prime[p].elem.prodDesc.name)==8){                                  
                        printf("%9s",D->syn[trav].elem.prodDesc.name); 
                  }else{
                        printf("%10s",D->syn[trav].elem.prodDesc.name);
                  }
                  trav=D->syn[trav].next;
              }
         }
         
    }
    printf("\n\nAvail :: %d",D->avail);

	printf("\n\nPress any key to continue. "); getch();		
}

/************************************************************
 *  Problem 2 Function Definitions                          *
 ************************************************************/
void populateDictionary(Dictionary D)
{
	const int COUNT = 12;
	product data[] = { 	{"170145" , {"Toblerone", 135}, 150.75, 20},
						{"1356",    {"Ferrero", 200}, 250.75, 85},
						{"15507",   {"Cadbury", 120}, 200.00, 30},
						{"180731",  {"Mars", 100}, 150.75, 20},
						{"12015",   {"Kitkat", 50}, 97.75, 40},
						{"1450",    {"Ferrero", 100},150.50, 50},
						{"170145",  {"Toblerone", 50}, 90.75, 80},
						{"1601",	{"Meiji", 75}, 75.50, 60},
						{"13101813",{"Nestle", 100}, 124.50, 70},
						{"154535", 	{"Valor", 120}, 149.50, 90},
						{"14551",   {"Tango", 75}, 49.50, 100},
						{"1703451", {"Toblerone", 100}, 125.75, 60},
		              };

           /* ***********************
            *    Put your code here           *
           ************************/
	int i;
	for(i=0;i<COUNT;i++){
		insertDic(D, data[i]);
		
	}
}

int hash(char *IDen)
{
	
	int sum = 0, i;
	for(i=0;IDen[i]!='\0';i++){
		sum+=IDen[i]-48;
	}
	return sum%PRIME_SIZE;
}

boolean isMember(Dictionary D, char *IDen)
{
	boolean ret;
	int h = hash(IDen), i;
	
	if(strcmp(D->prime[h].elem.prodID,IDen)!=0){
		if(strcmp(D->prime[h].elem.prodID,EMPTY)==0){
			ret = FALSE;
		}else{
			i = D->prime[h].next;
			while(i!=-1 && strcmp(D->syn[i].elem.prodID, IDen)!=0){
				i = D->syn[i].next;
			}
			if(i==-1){
				ret = FALSE;
			}else{
				ret = TRUE;
			}
		}
	}else{
		ret = TRUE;
	}
	
	return ret;
}

void insertDic(Dictionary D, product P)
{
	int h = hash(P.prodID), trav, temp;
	
	if(isMember(D, P.prodID) == FALSE){
		if(strcmp(D->prime[h].elem.prodID, EMPTY )== 0|| strcmp(D->prime[h].elem.prodID, DELETED)==0){
			D->prime[h].elem = P;
		}else{
			temp = D->avail;
			D->avail = D->syn[D->avail].next;
			D->syn[temp].elem = P;
			D->syn[temp].next = D->prime[h].next;
			D->prime[h].next = temp;
		}
	}
}
/************************************************************
 *  Problem 3 Function Definition                           *
 ************************************************************/
 void deleteDic(Dictionary D, char *IDen)
 {
 	int temp, *trav, hv;
 	
 	hv = hash(IDen);
 	if(isMember(D,IDen) == TRUE){
 		if(strcmp(D->prime[hv].elem.prodID, IDen)==0){
 			strcpy(D->prime[hv].elem.prodID, DELETED);
		 }else{
		 	trav = &hv;
			while(*trav!=-1 && (strcmp(D->syn[*trav].elem.prodID, IDen)!=0)){
				trav = &D->syn[*trav].next;
			}
			temp = (*trav);
			(*trav) = D->syn[temp].next;
			D->syn[temp].next = D->avail;
			D->avail = temp;
		 }
	 }
 }


/************************************************************
 *  Problem 4 Function Definition                           *
 ************************************************************/
void initMaxHeap(Heap *H)
{
	int i;
	for(i=0;i<HEAPSIZE;i++){
		H->data[i].weight = 0;
	}
	H->last = -1;
}
 
void insertMaxHeap(Heap *H, chocoDesc C)
{
	int child, parent;
	if(H->last < HEAPSIZE-1){
		child = ++H->last;
		for(parent = (child-1)/2;child!=0 && strcmp(H->data[parent].name, C.name)<0;child = parent, parent = (child-1)/2){
			H->data[child] = H->data[parent];
		}
			H->data[child] = C;
	}
}
void populateMaxHeap(Heap *H, Dictionary D)
{
	const int COUNT = 14;
	product data[] = { 	{"170145" , {"Toblerone", 135}, 150.75, 20},
						{"1356",    {"Ferrero", 200}, 250.75, 85},
						{"15507",   {"Cadbury", 120}, 200.00, 30},
						{"180731",  {"Mars", 100}, 150.75, 20},
						{"12015",   {"Kitkat", 50}, 97.75, 40},
						{"1450",    {"Ferrero", 100},150.50, 50},
						{"170145",  {"Toblerone", 50}, 90.75, 80},
						{"1501978", {"Hersheys", 100}, 100.50, 10},
     					               {"99094",   {"Lindt", 100}, 175.50, 80},
						{"1601",	{"Meiji", 75}, 75.50, 60},
						{"13101813",{"Nestle", 100}, 124.50, 70},
						{"154535", 	{"Valor", 120}, 149.50, 90},
						{"14551",   {"Tango", 75}, 49.50, 100},
						{"1703451", {"Toblerone", 100}, 125.75, 60},
		              };
          /* ***********************
            *    Put your code here           *
           ************************/
    int i;
    for(i=0;i<COUNT;i++){
    	if(isMember(D, data[i].prodID)==TRUE){
    		insertMaxHeap(H, data[i].prodDesc);
		}
	}
}	

void displayMaxHeap(Heap H)
{
	printf("\n\n%-7s", "Index");
	printf("%-12s","Choco Name");
	printf("%-10s","Choco Weight");
    int i;
    if(H.last!=-1){
         for(i=0;i<=H.last;i++){
              printf("\n%5d  ",i);
	          printf("%-12s",H.data[i].name);
	          printf("%-10d",H.data[i].weight);
         }
    }
	printf("\n\nPress any key to continue. "); getch();	
}

void heapSort(Heap *H)
{
	int left, right, parent, tree, oldLast,i;
	oldLast = H->last;
	for(i=H->last;i>0;i--){
		swapChoco(&H->data[0], &H->data[H->last--]);
		for(tree = (H->last-1)/2;tree >=0;tree--){
			printf("tree: %d\n", tree);
			parent = tree;
			
			left = (parent*2)+1;
			right = left+1;
			
			while(left < H->last && 
			(strcmp(H->data[parent].name, H->data[left].name)<0 || (right > H->last || strcmp(H->data[parent].name, H->data[right].name)<0 ))){
				if(right <=H->last){
					if(strcmp(H->data[parent].name, H->data[left].name)<0 && strcmp(H->data[left].name, H->data[right].name)>0){
						swapChoco(&H->data[parent], &H->data[left]);
						parent = left;
					}else if(strcmp(H->data[parent].name, H->data[right].name)<0 && strcmp(H->data[left].name, H->data[right].name)<=0){
						swapChoco(&H->data[parent], &H->data[right]);
						parent = right;
					}
				}else{
					if(strcmp(H->data[parent].name, H->data[left].name)<0){
						swapChoco(&H->data[parent], &H->data[left]);
						parent = left;
				}
			}
			left = (parent*2)+1;
			right = left+1;
		}
	}
	}
	H->last = oldLast;
}
void swapChoco(chocoDesc *X,chocoDesc *Y)
{
     chocoDesc temp;
     temp=(*X);
     (*X)=(*Y);
     (*Y)=temp;
}




/************************************************************
 *  Problem 5 Function Definitions                          *
 ************************************************************/