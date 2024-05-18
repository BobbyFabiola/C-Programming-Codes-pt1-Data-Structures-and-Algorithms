//! Author:         Fabiola C. Villanueva
//! Description:    Graph Traversals via Depth First Search and Breadth First Search
//!                  - The algorithm shall apply for both undirected and directed graphs.
//! Date:           05/04/2024

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define MAX_VERTEX  5
#define SENTINEL    INT_MAX

//structure definition
typedef enum { FALSE, TRUE } Boolean;
typedef char vertexType;        //'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
typedef int labeledType;

typedef struct {
    vertexType tail;
    vertexType head;
    int weight;
} edgeType;                     //for data set array

typedef struct {
    vertexType adjVertex;
    int weight;
} adjType;

typedef struct adjNode {
    adjType info;
    struct adjNode *link;
} *AdjList;

typedef struct {
    AdjList headArr[MAX_VERTEX];
    int edgeCount;
} directedAdjList;

typedef struct {
    labeledType graphMatrix[MAX_VERTEX][MAX_VERTEX];
    int edgeCount;
} directedAdjMatrix;

typedef struct {
    vertexType elems[MAX_VERTEX];
    int front, rear;
} QUEUE;

/* Problem 1 Function Prototype */
void initDirectedAdjList(directedAdjList *DL);
directedAdjList populateAdjacencyList (void);
void displayAdjList (directedAdjList L);

void initAdjMatrix (directedAdjMatrix *DM);
void convertListToMatrix (directedAdjList DL, directedAdjMatrix *DM);
void displayAdjMatrix (directedAdjMatrix M);

/* Problem 2 Function Prototypes */
void recursionListDFS (directedAdjList G, vertexType src, Boolean visArr[]);
void recursionMatrixDFS (directedAdjMatrix G, vertexType src, Boolean visArr[]);

/* Problem 3 Function Prototypes */
void iterativeListBFS (directedAdjList G, vertexType src);
void iterativeMatrixBFS (directedAdjMatrix G, vertexType src);

//* main
int main () {
    system("cls");

    printf("\n\nProblem #1:: "); 
   	printf("\n------------"); 

    directedAdjList mAL = populateAdjacencyList();
    displayAdjList (mAL);

    directedAdjMatrix mAM;
    convertListToMatrix (mAL, &mAM);
    displayAdjMatrix (mAM);

    printf("\n\nProblem #2:: "); 
   	printf("\n------------");

    printf("\n\nDEPTH FIRST SEARCH (LIST)\n");
    Boolean boolVisited[MAX_VERTEX] = { FALSE };
    int x;
    for (x = 0; x < MAX_VERTEX; ++x) {
        if (boolVisited[x] == FALSE) {
            recursionListDFS (mAL, 'A' + x, boolVisited);
        }
    }

    printf("\n\nDEPTH FIRST SEARCH (MATRIX)\n");
    Boolean setVisited[MAX_VERTEX] = { FALSE };
    for (x = 0; x < MAX_VERTEX; ++x) {
        if (setVisited[x] == FALSE) {
            recursionMatrixDFS (mAM, 'A' + x, setVisited);
        }
    }
    
    printf("\n\nProblem #3:: "); 
   	printf("\n------------");

    printf("\n\nBREADTH FIRST SEARCH (LIST)\n");
    iterativeListBFS (mAL, 'B');

    printf("\n\nBREADTH FIRST SEARCH (MATRIX)\n");
    iterativeMatrixBFS (mAM, 'B');

    printf("\n\n");
    return 0;
}

//! SETTING DATA
void initDirectedAdjList(directedAdjList *DL) {
	// Write the code 
	int x;
	for (x= 0; x < MAX_VERTEX; ++x) {
		DL->headArr[x] = NULL;
	}
	DL->edgeCount = 0;
}

directedAdjList populateAdjacencyList (void) {
    int count = 10;                     //data set
    edgeType arr[] = {     
        {'A', 'B', 4}, {'A', 'D', 5},
        {'B', 'C', 1}, {'B', 'E', 6},
        {'C', 'A', 1}, {'C', 'D', 3},
        {'D', 'C', 1}, {'D', 'E', 2},
        {'E', 'A', 1}, {'E', 'D', 4}
    };

    directedAdjList adjList;            //insert sorted ascending order via weights
    initDirectedAdjList (&adjList);
    int x;
    for (x = 0; x < count; ++x) {
        AdjList *trav, temp;
        for (trav = &(adjList.headArr[arr[x].head - 'A']); *trav != NULL /*&& (*trav)->info.weight < arr[x].weight*/; trav = &(*trav)->link) {}
        temp = malloc (sizeof (struct adjNode));
        if (temp != NULL) {
            temp->info.adjVertex = arr[x].tail;
            temp->info.weight = arr[x].weight;
            temp->link = *trav;
            *trav = temp;
        }
        adjList.edgeCount++;
    }
    return adjList;
}

void displayAdjList (directedAdjList L) {
    printf("\n\nTHE ADJACENCY LIST ::");
	printf("\n%-8s", "VERTEX");
	printf("%-20s", "ADJACENT VERTICES");
	printf("\n%-8s", "------");
	printf("%-19s", "-----------------");

    AdjList trav;
    int x;
    for (x = 0; x < MAX_VERTEX; ++x) {
        printf("\n  %c :: ", 'A' + x);
        for (trav = L.headArr[x]; trav != NULL; trav = trav->link) {
            printf(" %c (%d) ", trav->info.adjVertex, trav->info.weight);
        }
    }
}

void initAdjMatrix (directedAdjMatrix *DM) {
    int x, v;
    for (x = 0; x < MAX_VERTEX; ++x) {
        for (v = 0; v < MAX_VERTEX; ++v) {
            DM->graphMatrix[x][v] = SENTINEL;
        }
    }
}

void convertListToMatrix (directedAdjList DL, directedAdjMatrix *DM) {
    initAdjMatrix (DM);

    int x;
    AdjList trav;
    for (x = 0; x < MAX_VERTEX; ++x) {
        for (trav = DL.headArr[x]; trav != NULL; trav = trav->link) {
            DM->graphMatrix[x][trav->info.adjVertex - 'A'] = trav->info.weight;
            DM->edgeCount++;
        }
    }
}

void displayAdjMatrix (directedAdjMatrix M) {
    printf("\n\nTHE ADJACENCY MATRIX ::");
	printf("\n%-8s", "HEAD");
	printf("%-15s", "TAIL");
	printf("\n%-8s", "------");
	printf("%-19s", "-----------------");

    int x, v;
    for (x = 0; x < MAX_VERTEX; ++x) {
        printf("\n  %c :: ", 'A' + x);
        for (v = 0; v < MAX_VERTEX; ++v) {
            if (M.graphMatrix[x][v] != SENTINEL) {
                printf("    %2d    ", M.graphMatrix[x][v]);
            } else {
                printf("    ~~    ");
            }
        }
    }
}

//! DEPTH FIRST SEARCH
void recursionListDFS (directedAdjList G, vertexType src, Boolean visArr[]) {
    visArr[src - 'A'] = TRUE;
    printf(" %c ", src);

    AdjList trav;
    for (trav = G.headArr[src - 'A']; trav != NULL; trav = trav->link) {
        if (visArr[trav->info.adjVertex - 'A'] == FALSE) {
            recursionListDFS (G, trav->info.adjVertex, visArr);
        }
    }
}

void recursionMatrixDFS (directedAdjMatrix G, vertexType src, Boolean visArr[]) {
    visArr[src - 'A'] = TRUE;
    printf(" %c ", src);

    int x;
    for (x = 0; x < MAX_VERTEX; ++x) {
        if (G.graphMatrix[src - 'A'][x] != SENTINEL && visArr[x] == FALSE) {
            recursionMatrixDFS (G, 'A' + x, visArr);
        }
    }
}

//! BREADTH FIRST SEARCH
void iterativeListBFS (directedAdjList G, vertexType src) {
    QUEUE mQ = { .front = 0, .rear = -1 };
    Boolean visArr[MAX_VERTEX] = { FALSE };

    visArr[src - 'A'] = TRUE;                       //visit and enqueue src
    mQ.rear = (mQ.rear + 1) % MAX_VERTEX;
    mQ.elems[mQ.rear] = src;

    while ((mQ.rear + 1) % MAX_VERTEX != mQ.front) {
        vertexType currV = mQ.elems[mQ.front];      //get front
        printf(" %c ", currV);

        mQ.front = (mQ.front + 1) % MAX_VERTEX;     //dequeue
        AdjList trav;                               //queue adjacent vertices
        for (trav = G.headArr[currV - 'A']; trav != NULL; trav = trav->link) {
            if (visArr[trav->info.adjVertex - 'A'] == FALSE) {
                visArr[trav->info.adjVertex - 'A'] = TRUE;
                mQ.rear = (mQ.rear + 1) % MAX_VERTEX;
                mQ.elems[mQ.rear] = trav->info.adjVertex;
            }
        }
    }
}

void iterativeMatrixBFS (directedAdjMatrix G, vertexType src) {
    QUEUE mQ = { .front = 0, .rear = -1 };
    Boolean visArr[MAX_VERTEX] = { FALSE };

    visArr[src - 'A'] = TRUE;                       //visit and enqueue src
    mQ.rear = (mQ.rear + 1) % MAX_VERTEX;
    mQ.elems[mQ.rear] = src;
    
    while ((mQ.rear + 1) % MAX_VERTEX != mQ.front) {
        vertexType currV = mQ.elems[mQ.front];      //get front
        printf(" %c ", currV);

        mQ.front = (mQ.front + 1) % MAX_VERTEX;     //dequeue
        int x;
        for (x = 0; x < MAX_VERTEX; ++x) {          //queue adjacent vertices
            if (G.graphMatrix[currV - 'A'][x] != SENTINEL && visArr[x] == FALSE) {
                visArr[x] = TRUE;
                mQ.rear = (mQ.rear + 1) % MAX_VERTEX;
                mQ.elems[mQ.rear] = 'A' + x;
            }
        }
    }
}