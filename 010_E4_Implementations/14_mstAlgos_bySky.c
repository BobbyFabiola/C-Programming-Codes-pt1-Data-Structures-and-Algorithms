//! Author:         Fabiola C. Villanueva
//! Description:    Prim's and Kruskal's Algorithm to produce an MST
//! Date:           05/04/2024

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_VERTEX  7
#define SENTINEL    INT_MAX

//structure definition
typedef char  vertexType;    // 'A', 'B', 'C', 'D', 'E', 'F', 'G'   
typedef int labelType;

typedef struct {
	vertexType tail;         // vertex at the tail of the arc or edge  
	vertexType head;         // vertex at the head of the arc or edge  
	int weight;
} edgeType;                  // data type of the list of edges in the file and edge list  

typedef struct {
	vertexType adjVertex;
	int weight;
} adjType;

typedef struct adjNode {
	adjType  info;
	struct adjNode *link;
} *AdjList;

/* Labeled Adjacency list */
typedef struct {
   AdjList head[MAX_VERTEX];       /* vertices adjacent to Vertex A are stored at index 0, Vertex B at index 1, etc.. */          
   int edgeCount;                  /* total number of edges in the graph */             
} directedAdjList;

/* Labeled Adjacency Matrix */
typedef struct {
    labelType matrix[MAX_VERTEX][MAX_VERTEX];       /* 2D array of labels (weights) */
    int edgeCount;                                  /* total number of edges in the graph */
} labeledAdjMatrix;

typedef struct { 
	edgeType edges[MAX_VERTEX];
	int totalCost;
} MST;

typedef enum { FALSE, TRUE } Boolean;

/**************************************************
 * Function Prototypes                            *
 **************************************************/
/* PROBLEM 1 */
void initDirectedAdjList(directedAdjList * L);
directedAdjList populateDirectedAdjList();
void displayAdjList(directedAdjList L);

void initLabeledAdjMatrix (labeledAdjMatrix * M);
labeledAdjMatrix convertAdjListToMatrix (directedAdjList L);
void displayAdjMatrix (labeledAdjMatrix M);

/* PROBLEM 2 */
MST primsAlgoMatrix (labeledAdjMatrix G, vertexType src);
MST primsAlgoList (directedAdjList G, vertexType src);
void displayMST (MST M);

//* MAIN
int main () {
    system ("cls");

    printf("\n\n\nProblem #1:: "); 
   	printf("\n------------"); 

	directedAdjList mDL = populateDirectedAdjList();
	displayAdjList (mDL);
    labeledAdjMatrix mLM = convertAdjListToMatrix (mDL);
    displayAdjMatrix (mLM);

    printf("\n\nProblem #2:: "); 
   	printf("\n------------");
	printf("\nTHE MST (PRIMS) ::");

	MST mstMatrix, mstList;
	mstMatrix = primsAlgoMatrix (mLM, 'C');
	printf("\n\nADJACENCY MATRIX ::");
	displayMST (mstMatrix);

	mstList = primsAlgoList  (mDL, 'D');
	printf("\n\nADJACENCY LIST ::");
	displayMST (mstList);

	printf("\n\n\n");
    return 0;
}

//! PROBLEM 1 - SET DATA
void initDirectedAdjList(directedAdjList *DL) {
	// Write the code 
	int x;
	for (x= 0; x < MAX_VERTEX; ++x) {
		DL->head[x] = NULL;
	}
	DL->edgeCount = 0;
}

directedAdjList populateDirectedAdjList() {											//insert the given arcs into the adjacency list
	directedAdjList DL;
	initDirectedAdjList (&DL);

	const int COUNT = 22;
    edgeType data[] =     { 
		{'A', 'B', 2}, {'A', 'C', 3}, {'A', 'D', 3},
		{'B', 'A', 2}, {'B', 'C', 4}, {'B', 'E', 3}, 
		{'C', 'A', 3}, {'C', 'B', 4}, {'C', 'D', 5}, {'C', 'E', 1}, {'C', 'F', 6},
		{'D', 'A', 3}, {'D', 'C', 5}, {'D', 'F', 7},
		{'E', 'B', 3}, {'E', 'C', 1}, {'E', 'F', 8},
		{'F', 'E', 8}, {'F', 'C', 6}, {'F', 'D', 7}, {'F', 'G', 9},
		{'G', 'F', 9}
	};

	AdjList *trav, temp;
	int x;
	for (x = 0; x <= COUNT; ++x) {													//visiting all elements in the array
		for (trav = &(DL.head[data[x].tail - 'A']); *trav != NULL && (*trav)->info.adjVertex <= data[x].head; trav = &(*trav)->link) {}
		if (*trav != NULL && (*trav)->info.adjVertex == data[x].head) {				//if adjacent vertex already exists in the list, get small
			(*trav)->info.weight = (data[x].weight < (*trav)->info.weight)? data[x].weight: (*trav)->info.weight;
		} else {
			temp = malloc (sizeof (struct adjNode));
			if (temp != NULL) {
				temp->info.adjVertex = data[x].head;
				temp->info.weight = data[x].weight;
				temp->link = *trav;
				*trav = temp;
			}
			DL.edgeCount++;
		}
	}
	return DL;
}

void displayAdjList(directedAdjList L) {
 	int x;
	AdjList temp;
		
	printf("\n\nTHE ADJACENCY LIST ::");
	printf("\n%-8s", "VERTEX");
	printf("%-20s", "ADJACENT VERTICES");
	printf("\n%-8s", "------");
	printf("%-19s", "-----------------");
 
	for ( x = 0; x < MAX_VERTEX; ++x) {
		printf("\n  %c :: ", 'A' + x);
		if (L.head[x] == NULL) {
			printf(" NULL");
		} else {
			for (temp = L.head[x]; temp != NULL; temp = temp->link) {
				printf(" %c (%d)\t", temp->info.adjVertex, temp->info.weight);
			}
		}
	}
	printf("\n\nNumber of edges : %d\n\n", L.edgeCount);
}

void initLabeledAdjMatrix (labeledAdjMatrix * M) {
    M->edgeCount = 0;
    int x, z;
    for (x = 0; x < MAX_VERTEX; ++x) {
        for (z = 0; z < MAX_VERTEX; ++z) {
            M->matrix[x][z] = SENTINEL;
        }
    }
}

labeledAdjMatrix convertAdjListToMatrix (directedAdjList L) {
    labeledAdjMatrix M;
    initLabeledAdjMatrix (&M);

    int x;
    AdjList trav;
    for (x = 0; x < MAX_VERTEX; ++x) {
        for (trav = L.head[x]; trav != NULL; trav = trav->link) {
            M.matrix[x][trav->info.adjVertex - 'A'] = trav->info.weight;
            M.edgeCount++;
        }
    }
    return M;
}

void displayAdjMatrix (labeledAdjMatrix M) {
    printf("\n\nTHE ADJACENCY MATRIX ::");
	printf("\n%-8s", "HEAD");
	printf("%-15s", "TAILS ADJACENT TO");
	printf("\n%-8s", "------");
	printf("%-19s", "-----------------");

    int x, z;
    for (x = 0; x < MAX_VERTEX; ++x) {
        printf("\n  %c :: ", 'A' + x);
        for (z = 0; z < MAX_VERTEX; ++z) {
            if (M.matrix[x][z] == SENTINEL) {
                printf("  ~~  ");
            } else {
                printf("  %2d  ", M.matrix[x][z]);
            }
        }
    }
    printf("\n\nNumber of arcs: %d\n\n", M.edgeCount);
}

//! PROBLEM 2 PRIM'S ALGORITHM
void displayMST(MST M) {
    printf("\n%-8s", "EDGE");
    printf("%-15s", "WEIGHT");
    printf("\n%-8s", "------");
    printf("%-19s", "-------");

    int x;
    for (x = 0; x < MAX_VERTEX; ++x) {
        printf("\n (%c, %c)::  %d", M.edges[x].head, M.edges[x].tail, M.edges[x].weight);
    }
    printf("\n\nTotal cost: %d", M.totalCost);
}

MST primsAlgoMatrix (labeledAdjMatrix G, vertexType src) {
	Boolean visArr[MAX_VERTEX] = { FALSE };
	MST M = {.totalCost = 0};

	int x;
	for (x = 0; x < MAX_VERTEX; ++x) {
		M.edges[x].weight = INT_MAX;
	}
	M.edges[src - 'A'].weight = 0;					//path to itself
	M.edges[src - 'A'].head = src;
	M.edges[src - 'A'].tail = src;

	//make the spanning tree by visiting n times
	for (x = 0; x < MAX_VERTEX; ++x) {
		int min = INT_MAX, minIdx, a;
		for (a = 0; a < MAX_VERTEX; ++a)  {			//iterate through the edges array
			if (visArr[a] == FALSE && M.edges[a].weight < min) {
				minIdx = a;
				min = M.edges[minIdx].weight;
			}
		}
		visArr[minIdx] = TRUE;						//mark as visited
		for (a = 0; a < MAX_VERTEX; ++a) {
			if (visArr[a] == FALSE && G.matrix[minIdx][a] < M.edges[a].weight) {
				M.edges[a].head = minIdx + 'A';
				M.edges[a].tail = a + 'A';
				M.edges[a].weight = G.matrix[minIdx][a];
			}
		}
	}
	for (x = 0; x < MAX_VERTEX; ++x) {				//get the sum of the total cost
		M.totalCost += M.edges[x].weight;
	}
	return M;
}

MST primsAlgoList (directedAdjList G, vertexType src) {
	Boolean visArr[MAX_VERTEX] = { FALSE };
	MST M = {.totalCost = 0};

	int x;
	for (x = 0; x < MAX_VERTEX; ++x) {
		M.edges[x].weight = INT_MAX;
	}
	M.edges[src - 'A'].weight = 0;					//path to itself
	M.edges[src - 'A'].head = src;
	M.edges[src - 'A'].tail = src;

	int a;
	for (a = 0; a < MAX_VERTEX; ++a) {
		int min = INT_MAX, minIdx;
		for (x = 0; x < MAX_VERTEX; ++x) {
			if (visArr[x] == FALSE && M.edges[x].weight < min) {
				minIdx = x;
				min = M.edges[minIdx].weight;
			}
		}
		visArr[minIdx] = TRUE;
		AdjList trav;
		for (trav = G.head[minIdx]; trav != NULL; trav = trav->link) {
			if (visArr[trav->info.adjVertex - 'A'] == FALSE && trav->info.weight < M.edges[trav->info.adjVertex - 'A'].weight) {
				M.edges[trav->info.adjVertex - 'A'].head = minIdx + 'A';
				M.edges[trav->info.adjVertex - 'A'].tail = trav->info.adjVertex;
				M.edges[trav->info.adjVertex - 'A'].weight = trav->info.weight;
			}
		}
	}
	for (a = 0; a < MAX_VERTEX; ++a) {
		M.totalCost += M.edges[a].weight;
	}
	return M;
}