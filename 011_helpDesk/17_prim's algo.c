#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX // Infinite weight for disconnected edges

// Function to find the vertex with the minimum key value
int minKey(int key[], bool mstSet[], int V) {
    int min = INF, minIndex;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the MST
void printMST(int parent[], int** graph, int V) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

// Prim's Algorithm
void primMST(int** graph, int V) {
    int parent[V];     // Stores the MST
    int key[V];        // Key values to pick the minimum edge
    bool mstSet[V];    // To represent vertices included in MST

    // Initialize all keys as infinite and mstSet as false
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    // Start from the first vertex
    key[0] = 0;       // Include the first vertex in MST
    parent[0] = -1;   // Root node of MST

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            // Update the key only if:
            // 1. There is an edge from u to v
            // 2. v is not in mstSet
            // 3. The edge weight is smaller than the current key[v]
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the MST
    printMST(parent, graph, V);
}

// Utility function to allocate memory for the adjacency matrix
int** createGraph(int V) {
    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
    }
    return graph;
}

// Free allocated memory for the graph
void freeGraph(int** graph, int V) {
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
}

// Main function
int main() {
    int V = 5; // Number of vertices
    int** graph = createGraph(V);

    // Adjacency matrix representation of the graph
    int graphData[5][5] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    // Copy graph data to dynamically allocated graph
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = graphData[i][j];
        }
    }

    printf("Prim's Minimum Spanning Tree:\n");
    primMST(graph, V);

    // Free the memory
    freeGraph(graph, V);

    return 0;
}
