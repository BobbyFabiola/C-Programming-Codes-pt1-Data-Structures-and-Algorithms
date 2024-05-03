//! Author: 		Fabiola C. Villanueva
//! Description:	Converting an Adjacency List to an Adjacency Matrix
//! Date:           04/28/24 (30mins)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 6
#define SENTINEL 0XFFFF

//structure definition
typedef char  vertexType;               	// 'A', 'B', 'C', 'D', 'E', 'F'    
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

/**************************************************
 * Function Prototypes                            *
 **************************************************/
/* PROBLEM 1 */
void initDirectedAdjList(directedAdjList * L);
directedAdjList populateDirectedAdjList();
void displayAdjList(directedAdjList L);

/* PROBLEM 2 */
void initLabeledAdjMatrix (labeledAdjMatrix * M);
labeledAdjMatrix convertAdjListToMatrix (directedAdjList L);
void displayAdjMatrix (labeledAdjMatrix M);

int main( ) {	
	system("cls");
 /*------------------------------------------------------------------------------------
 * 	Problem #1 ::  a) Creates a Labeled Adjacency List via populateDirectedAdjList()  *
 *                 b) Calls displayAdjList().                                         *
 *------------------------------------------------------------------------------------*/
  	printf("\n\n\nProblem #1:: "); 
   	printf("\n------------"); 
   
   	//Write the code for main here
	directedAdjList mDL = populateDirectedAdjList();
	displayAdjList (mDL);

    printf("\n\nProblem #2:: "); 
   	printf("\n------------");
    labeledAdjMatrix mLM = convertAdjListToMatrix (mDL);
    displayAdjMatrix (mLM);
	
 	return 0;
}

/************************************************************
 *  Problem 1 Function Definitions                          *
 ************************************************************/ 
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

	const int COUNT = 14;
    edgeType data[] =     {  {'A', 'E', 6}, {'C', 'A', 4}, { 'E', 'C' , 6 },
                             {'A', 'F', 3}, {'C', 'D', 6}, { 'E', 'F' , 6 },
                             {'B', 'A', 4}, {'D', 'A', 8}, { 'F', 'B' , 3 },
                             {'B', 'C', 3}, {'D', 'B', 6}, { 'D', 'E' , 3 }, 
							 {'B', 'E', 6}, {'F', 'D' ,3 },{ 'B', 'F' , 10 }, 
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
 
	//Write your code here 
	for ( x = 0; x < MAX_VERTEX; ++x) {											//at head
		printf("\n  %c :: ", 'A' + x);
		if (L.head[x] == NULL) {
			printf(" NULL");
		} else {
			for (temp = L.head[x]; temp != NULL; temp = temp->link) {			//printf elements
				printf(" %c (%d)\t", temp->info.adjVertex, temp->info.weight);
			}
		}
	}
	printf("\n\nNumber of arcs: %d\n\n", L.edgeCount);
}

/************************************************************
 *  Problem 2 Function Definitions                          *
 ************************************************************/ 
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
	printf("%-15s", "TAIL");
	printf("\n%-8s", "------");
	printf("%-19s", "-----------------");

    int x, z;
    for (x = 0; x < MAX_VERTEX; ++x) {
        printf("\n  %c :: ", 'A' + x);
        for (z = 0; z < MAX_VERTEX; ++z) {
            if (M.matrix[x][z] == SENTINEL) {
                printf(" SENTINEL ");
            } else {
                printf("    %2d    ", M.matrix[x][z]);
            }
        }
    }
    printf("\n\nNumber of arcs: %d\n\n", M.edgeCount);
}