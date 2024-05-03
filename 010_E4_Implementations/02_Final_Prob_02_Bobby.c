//! Author: 		Fabiola C. Villanueva
//! Description:	
//! Date: 			

/************************************************************************
 * Prim's Algorithm : It grows a spanning tree, one edge at a time.     *
 * Given:                                                               *
 *   1)  Graph G = (V, E)                                               *
 *   2)  V = {0, 1, 2, 3, 4}                                            *
 *                                                                      *
 * Steps of Prim�s Algorithm:                                           *
 *   1) Initialize set U to contain { 0 }                               *
 *      //In the program, starting vertex will be inputted by the user  *
 *   2) While (U != V)                                                  *
 *       a) Find the minimum cost edge (u, v) such that                 *
 *          u is an element  U and   v is not yet in U                  *
 *       b)  Add v to U                                                 *
 ************************************************************************/
 
#include <unistd.h>    // for sleep(), to add in code if display leaves blank screen  
#include <stdio.h> 
#include <string.h>   

                 
#define MAX  6              // Number of vertices in the graph  
#define INFINITY  0XFFFF    
   
/***** Data Structure Definition *****/  
typedef int graphType[MAX][MAX];    // A[x][y] = INFINITY  if there is not edge ;  A[x][y] = weight of the edge (x,y)
typedef int set[MAX];               // Bit-vector implementation of Set

typedef struct {
	int u, v;     // (u,v) represents the edge  
	int weight;   // weight of the edge
}edgetype;

typedef struct {
    edgetype edges[MAX];
    int edgeCount;   //actual number of edges
	int minCost;	 //Cost of the MST
}primMST;

/***** Function Prototypes *****/

void populateGraph(graphType G);
primMST primAlgo(graphType graph, int startVertex);
void displayPrimMST(primMST tree);

int main() { 
     /*---------------------------------------------------------------------------------
    * 	Problem #2 ::  a) Allows user to input from keyboard the starting vertex      *
    *                  b) Calls populateGraph() to populate the given graph           *
    *                  c) Calls primAlgo() and displayPrimMST()                       *
    *                                                                                 *
    * printf("\n\n\nProblem #2:: ");                                                  *  
    * printf("\n------------");                                                       *
    *---------------------------------------------------------------------------------*/
 	printf("\n\n\nProblem #2:: "); 
    printf("\n------------"); 
    
    //Write code here
 	
    return 0; 
} 

/************************************************************
 * Function Definitions                                     *
 ************************************************************/
void populateGraph(graphType G) {
	graphType graph = {  INFINITY, 1, 5, 4, 6, 5, 1, INFINITY, 5, INFINITY, INFINITY, 6, 5, 5, INFINITY, 2, INFINITY, INFINITY, 4,
                             INFINITY, 2, INFINITY, 1, INFINITY, 6, INFINITY,INFINITY, 1, INFINITY, 3, 5, 6, INFINITY, INFINITY, 3, INFINITY} ;   //5

	memcpy(G, graph, sizeof(graph));
}

 

primMST primAlgo(graphType graph, int startVertex) {
	 //Write code here
}

void displayPrimMST(primMST T) {
	int x;
		
	printf("\n%5s%5s", "Edge", "Cost");
 
    //Write code here
	
}