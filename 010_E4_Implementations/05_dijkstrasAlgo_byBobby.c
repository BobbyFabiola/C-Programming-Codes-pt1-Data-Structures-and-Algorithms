//! Author:         Fabiola C. Villanueva
//! Description:    Dijsktra's Algorithm in Adjacency Matrix and List
//! Date:           04/30/24 (2 WHOLE days to understand Dijkstra's)

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define SENTINEL        INT_MAX
#define MAX_VERTEX      9

//structure definition
typedef char vertexType;        //'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',

typedef struct {
    vertexType tail;
    vertexType head;
    int weight;
} edgeType;

typedef int adjMatrix [MAX_VERTEX][MAX_VERTEX];

typedef enum {FALSE, TRUE} Boolean;

/* Problem 1 Function Prototypes */
void initAdjMatrix (adjMatrix *M);
void populateAdjacencyMatrix (adjMatrix *M);
void displayMatrix  (adjMatrix M);

/* Problem 2 Function Prototypes */
int *ssspDijkstraAlgoMatrix (vertexType src, adjMatrix M);
void srcDisplaySSSP (vertexType src, int distSP[]);

/* Problem 3 Function Prototypes */
// void populateAdjacencyList ();

int main () {
    system ("cls");

    printf("\nProblem #1::  THE MATRIX"); 
   	printf("\n------------"); 

    adjMatrix mAdjM;

    initAdjMatrix (&mAdjM);
    populateAdjacencyMatrix (&mAdjM);
    displayMatrix (mAdjM);

    printf("\nProblem #2::  DIJKSTRA'S via MATRIX"); 
   	printf("\n------------");

    int *spArr;

    spArr = ssspDijkstraAlgoMatrix ('A', mAdjM);
    if (spArr != NULL) {
        srcDisplaySSSP ('A', spArr);
    } else {
        printf("\nERROR ALLOCATING MEMORY.\n");
    }

    spArr = ssspDijkstraAlgoMatrix ('E', mAdjM);
    if (spArr != NULL) {
        srcDisplaySSSP ('E', spArr);
    } else {
        printf("\nERROR ALLOCATING MEMORY.\n");
    }

    printf("\n\n\n");
    system("pause");
    system ("cls");

    printf("\nProblem #3::  THE LIST"); 
   	printf("\n------------"); 

    printf("\n\n");
    return 0;
}


//! PROBLEM 1
void initAdjMatrix (adjMatrix *M) {
    int i, j;
    for (i = 0; i < MAX_VERTEX; ++i) {
        for (j = 0; j < MAX_VERTEX; ++j) {
            (*M)[i][j] = SENTINEL;
        }
    }
}

void populateAdjacencyMatrix (adjMatrix *M) {
    //data of edges
    int count = 28;
    edgeType arr[] = {     
        {'A', 'B',  4}, {'A', 'H',  8}, {'B', 'A',  4}, {'B', 'C', 8},
        {'B', 'H', 11}, {'C', 'B',  8}, {'C', 'D',  7}, {'C', 'F', 4},
        {'C', 'I',  2}, {'D', 'C',  7}, {'D', 'E',  9}, {'D', 'F', 14},
        {'E', 'D',  9}, {'E', 'F', 10}, {'F', 'C',  4}, {'F', 'D', 14},
        {'F', 'E', 10}, {'F', 'G',  2}, {'G', 'F',  2}, {'G', 'H',  1},
        {'G', 'I',  6}, {'H', 'A',  8}, {'H', 'B', 11}, {'H', 'G',  1},
        {'I', 'C',  2}, {'I', 'G',  6}, {'I', 'H',  7}, {'H', 'I', 7}
    };

    int x;
    for (x = 0; x < count; ++x) {
        (*M)[arr[x].tail - 'A'][arr[x].head - 'A'] = arr[x].weight;
    }
}

void displayMatrix  (adjMatrix M) {
    printf("\n<< Adjacency Matrix >> ::\n");
    printf("%-8s%-20s\n", "VERTEX", "ADJACENT VERTICES :: SENTINEL AS \'~~\'");
    printf("%-8s%-20s\n", "------", "------------------------------------");

    for (int a = 0; a < MAX_VERTEX; ++a) {
        printf("  %c :: ", 'A' + a);
        for (int b = 0; b < MAX_VERTEX; ++b) {
            if (M[a][b] == SENTINEL) {
                printf("  ~~  ");
            } else {
                if (a == 5 && b == 3) {
                    printf(" [!!] ");
                } else {
                    printf("  %2d  ", M[a][b]);
                }
            }
        }
        printf("\n");
    }
}

//! PROBLEM 2
void srcDisplaySSSP (vertexType src, int distSP[]) {
    printf("\n\nSource: \'%c\'", src);
    int x;
    for (x = 0; x < MAX_VERTEX; ++x) {
        printf("\n  %c :: %3d", 'A' + x, distSP[x]);
    }
}

int *ssspDijkstraAlgoMatrix (vertexType src, adjMatrix M) {
    Boolean boolVisited[MAX_VERTEX] = { FALSE };
    int *ptrSP = (int *) malloc (sizeof (int) * MAX_VERTEX);
    if (ptrSP != NULL) {

        //initialize components
        int a;
        for (a = 0; a < MAX_VERTEX; ++a) {
            ptrSP[a] = SENTINEL;
        }
        ptrSP[src - 'A'] = 0;

        int v, x;
        for (v = 0; v < MAX_VERTEX; ++v) {                              //iterating through unvisited vertices
            int min = INT_MAX, minIdx;

            for (x = 0; x < MAX_VERTEX; ++x) {                          //find the unvisited and smallest path in the SP[]
                if (boolVisited[x] == FALSE && ptrSP[x] < min) {
                    minIdx = x;
                    min = ptrSP[minIdx];
                }
            }
            boolVisited[minIdx] = TRUE;                                 //declare new current vertex to visited

            for (a = 0; a < MAX_VERTEX; ++a) {
                if (boolVisited[a] == FALSE && M[minIdx][a] != SENTINEL && M[minIdx][a] + ptrSP[minIdx] < ptrSP[a]) {
                    ptrSP[a] = M[minIdx][a] + ptrSP[minIdx];
                }
            }
        }
    }
    return ptrSP;
}

//! PROBLEM 3