#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent an edge
typedef struct Edge {
    int src, dest, weight;
} Edge;

// Structure to represent a subset for Union-Find
typedef struct Subset {
    int parent;
    int rank;
} Subset;

// Comparator function for qsort
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Find function with path compression
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Union function with union by rank
void unionSets(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Function to convert adjacency matrix to edge list
Edge* createEdgeList(int** adjMatrix, int V, int* edgeCount) {
    int maxEdges = V * (V - 1) / 2; // Maximum number of edges in an undirected graph
    Edge* edges = (Edge*)malloc(maxEdges * sizeof(Edge));
    *edgeCount = 0;

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) { // Avoid duplicates for undirected graph
            if (adjMatrix[i][j] != 0) {  // Include only valid edges
                edges[*edgeCount].src = i;
                edges[*edgeCount].dest = j;
                edges[*edgeCount].weight = adjMatrix[i][j];
                (*edgeCount)++;
            }
        }
    }
    return edges;
}

// Kruskal's Algorithm
void kruskalMST(int** adjMatrix, int V) {
    int edgeCount = 0;
    Edge* edges = createEdgeList(adjMatrix, V, &edgeCount);

    // Step 1: Sort edges by weight
    qsort(edges, edgeCount, sizeof(edges[0]), compareEdges);

    // Step 2: Allocate memory for subsets
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Step 3: Pick edges one by one
    Edge* result = (Edge*)malloc((V - 1) * sizeof(Edge)); // Resultant MST
    int e = 0; // Index for result[]
    for (int i = 0; i < edgeCount && e < V - 1; i++) {
        Edge nextEdge = edges[i];
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // If no cycle, add edge to result
        if (x != y) {
            result[e++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    // Print the resultant MST
    printf("Edges in the Minimum Spanning Tree:\n");
    int totalWeight = 0;
    for (int i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total weight of MST: %d\n", totalWeight);

    // Free allocated memory
    free(edges);
    free(result);
    free(subsets);
}

// Driver code
int main() {
    int V = 4; // Number of vertices
    int** adjMatrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        adjMatrix[i] = (int*)malloc(V * sizeof(int));
    }

    // Example adjacency matrix
    int matrix[4][4] = {
        {0, 10, 6, 5},
        {10, 0, 0, 15},
        {6, 0, 0, 4},
        {5, 15, 4, 0}
    };

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adjMatrix[i][j] = matrix[i][j];
        }
    }

    kruskalMST(adjMatrix, V);

    for (int i = 0; i < V; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);

    return 0;
}
