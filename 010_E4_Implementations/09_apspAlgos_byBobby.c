//! Author:         Fabiola C. Villanueva
//! Description:    Warshall and Floyd-Warshall Algorithms in Adjacency Matrix
//! Date:           05/03/2024

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

#define SENTINEL        INT_MAX
#define MAX_VERTEX      5

//structure definition
typedef char vertexType;        //'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',

typedef struct {
    vertexType tail;
    vertexType head;
    int weight;
} edgeType;

typedef enum {FALSE, TRUE} Boolean;
typedef int adjMatrix [MAX_VERTEX][MAX_VERTEX];
typedef Boolean BooleanMatrix[MAX_VERTEX][MAX_VERTEX];

/* Problem 1 Function Prototypes */
void initAdjMatrix (adjMatrix *M);
void populateAdjacencyMatrix (adjMatrix *M);
void displayMatrix  (adjMatrix M);

/* Problem 2 Function Prototypes */
void warshallTransitiveClosure (adjMatrix M, BooleanMatrix *W);
void displayBoolean (BooleanMatrix W);

/* Problem 3 Function Prototypes */
void floyWarshallAlgo (adjMatrix M, adjMatrix *spMatrix);
void displayMatrixSP (adjMatrix spMatrix);

//* MAIN
int main () {
    system ("cls");

    printf("\nProblem #1::  THE MATRIX"); 
   	printf("\n------------"); 

    adjMatrix mAdjM;

    initAdjMatrix (&mAdjM);
    populateAdjacencyMatrix (&mAdjM);
    displayMatrix (mAdjM);

    printf("\n\nProblem #2::  WARSHALL BY TRANSITIVE CLOSURE"); 
   	printf("\n------------");

    BooleanMatrix TCW; // Initialize the first row
    for (int i = 1; i < MAX_VERTEX; ++i) {
        for (int j = 0; j < MAX_VERTEX; ++j) {
            TCW[i][j] = FALSE;
        }
    }

    warshallTransitiveClosure (mAdjM, &TCW);
    displayBoolean (TCW);

    printf("\n\nProblem #3::  FLOYD-WARSHALL BY APSP"); 
   	printf("\n------------");

    adjMatrix spFW;
    floyWarshallAlgo (mAdjM, &spFW);
    displayMatrixSP (spFW);



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
    int count = 10;
    edgeType arr[] = {     
        {'A', 'B', 4}, {'A', 'D', 5},
        {'B', 'C', 1}, {'B', 'E', 6},
        {'C', 'A', 1}, {'C', 'D', 3},
        {'D', 'C', 1}, {'D', 'E', 2},
        {'E', 'A', 1}, {'E', 'D', 4}
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
void warshallTransitiveClosure (adjMatrix M, BooleanMatrix *W) { //? DEBUG LATER
    int a, b, c;

    //copy entries from adjacency matrix into boolean
    for (a = 0; a < MAX_VERTEX; ++a) {
        for (b = 0; b < MAX_VERTEX; ++b) {
            if (M[a][b] != SENTINEL) {
                (*W)[a][b] = TRUE;
            }
        }
    }

    //warshall matters: if a is reachable from b VIA c and if a is reachable from a and b
    for (a = 0; a < MAX_VERTEX; ++a) {
        for (b = 0; b < MAX_VERTEX; ++b) {
            for (c = 0; c < MAX_VERTEX; ++c) {
                if ((*W)[b][a] == TRUE && (*W)[a][c] == TRUE) {
                    (*W)[b][c] = TRUE;
                }
            }
        }
    }
}

void displayBoolean (BooleanMatrix W) {
    printf("\n<< Boolean Matrix >> ::\n");
    printf("%-8s%-20s\n", "VERTEX", "PATH RELATIONS :: 1-PATH / 0-NO PATH");
    printf("%-8s%-20s\n", "------", "------------------------------------");

    for (int a = 0; a < MAX_VERTEX; ++a) {
        printf("  %c :: ", 'A' + a);
        for (int b = 0; b < MAX_VERTEX; ++b) {
            printf("  %2d  ", W[a][b]);
        }
        printf("\n");
    }
}

//! PROBLEM 3
void floyWarshallAlgo (adjMatrix M, adjMatrix *spMatrix) {
    int a, b, c;

    //initialize component
    for (a = 0; a < MAX_VERTEX; ++a) {
        for (b = 0; b < MAX_VERTEX; ++b) {
            if (a != b) {
                (*spMatrix)[a][b] = (M[a][b] != SENTINEL) ? M[a][b] : INT_MAX;
            } else {
                (*spMatrix)[a][b] = 0;
            }
        }
    }

    //actual Floyd's
    for (a = 0; a < MAX_VERTEX; ++a) {
        for (b = 0; b < MAX_VERTEX; ++b) {
            for (c = 0; c < MAX_VERTEX; ++c) {
                if ((*spMatrix)[a][c] != SENTINEL && (*spMatrix)[c][b] != SENTINEL) {                   //check if degrees are sentinel
                    (*spMatrix)[a][b] = ((*spMatrix)[a][c] + (*spMatrix)[c][b] < (*spMatrix)[a][b]) ?   //comparing minimum cost and value assignment
                    (*spMatrix)[a][c] + (*spMatrix)[c][b]: (*spMatrix)[a][b];
                }
            }
        }
    }
}

void displayMatrixSP (adjMatrix spMatrix) {
    printf("\n<< Shortest Path Matrix >> ::\n");
    printf("%-8s%-20s\n", "VERTEX", "ALL PAIRS TO ALL PAIRS");
    printf("%-8s%-20s\n", "------", "------------------------------------");

    int x, v;
    for (x = 0; x < MAX_VERTEX; ++x) {
        printf("  %c :: ", 'A' + x);
        for (v = 0; v < MAX_VERTEX; ++v) {
            if (spMatrix[x][v] == SENTINEL) {
                printf("  ~~  ");
            } else {
                printf("  %2d  ", spMatrix[x][v]);
            }
        }
        printf("\n");
    }
}