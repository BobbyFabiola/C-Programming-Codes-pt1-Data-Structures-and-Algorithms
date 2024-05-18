#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 8
#define INF INT_MAX

// Typedef for Edge structure
typedef struct {
    int src, dest, weight;
} Edge;

// Function to perform Depth-First Search (DFS)
void dfs(int graph[MAX_SIZE][MAX_SIZE], int node, bool visited[]) {
    visited[node] = true;
    printf("%c ", 'A' + node);

    for (int x = 0; x < MAX_SIZE; x++) {
        if (graph[node][x] != INF && !visited[x]) {
            dfs(graph, x, visited);
        }
    }
}

// Function to perform Breadth-First Search (BFS)
void bfs(int graph[MAX_SIZE][MAX_SIZE], int start) {
    bool visited[MAX_SIZE] = {false};
    int queue[MAX_SIZE];
    int front = 0, rear = -1;

    visited[start] = true;
    queue[++rear] = start;

    while (front <= rear) {
        int node = queue[front++];

        printf("%c ", 'A' + node);

        for (int x = 0; x < MAX_SIZE; x++) {
            if (graph[node][x] != INF && !visited[x]) {
                visited[x] = true;
                queue[++rear] = x;
            }
        }
    }
}

// Function to perform Dijkstra's algorithm on an adjacency matrix
int *dijkstra(int graph[MAX_SIZE][MAX_SIZE], int start) {
    int *shortest_distances = (int*) calloc(MAX_SIZE, sizeof(int));
    bool visited[MAX_SIZE] = {false};

    if (shortest_distances != NULL) {
        for (int x = 0; x < MAX_SIZE; x++)
            shortest_distances[x] = INF;

        shortest_distances[start] = 0;

        for (int x = 0; x < MAX_SIZE; x++) {
            int min_distance = INF, min_index;

            for (int y = 0; y < MAX_SIZE; y++) {
                if (!visited[y] && shortest_distances[y] < min_distance) {
                    min_distance = shortest_distances[y];
                    min_index = y;
                }
            }

            visited[min_index] = true;

            for (int y = 0; y < MAX_SIZE; y++) {
                if (!visited[y] && graph[min_index][y] != INF &&  shortest_distances[min_index] + graph[min_index][y] < shortest_distances[y]) {
                    shortest_distances[y] = shortest_distances[min_index] + graph[min_index][y];
                }
            }
        }
    }

    return shortest_distances;
}

// Function to display the shortest paths
void displayShortestPaths(int *shortest_distances) {
    printf("\nShortest Path\n");
    for (int i = 0; i < MAX_SIZE; ++i) {
        printf("%c: %d\n", 'A' + i, shortest_distances[i]);
    }
}

// Function to find the parent of a node in disjoint set union-find
int findParent(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return findParent(parent, parent[i]);
}

// Function to perform union of two sets
void unionSet(int parent[], int rank[], int x, int y) {
    int xRoot = findParent(parent, x);
    int yRoot = findParent(parent, y);

    if (rank[xRoot] < rank[yRoot])
        parent[xRoot] = yRoot;
    else if (rank[xRoot] > rank[yRoot])
        parent[yRoot] = xRoot;
    else {
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

// Kruskal's algorithm to find Minimum Spanning Tree (MST)
int kruskal(int graph[MAX_SIZE][MAX_SIZE], int edges) {
    // Array to store the resulting MST
    Edge result[MAX_SIZE];
    int resultIndex = 0;

    // Sort all the edges in non-decreasing order of their weight
    Edge sortedEdges[MAX_SIZE * MAX_SIZE];
    int sortedEdgesIndex = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (graph[i][j] != INF) {
                sortedEdges[sortedEdgesIndex++] = (Edge){i, j, graph[i][j]};
            }
        }
    }

    // Sort the edges based on their weight
    for (int i = 0; i < sortedEdgesIndex - 1; i++) {
        for (int j = 0; j < sortedEdgesIndex - i - 1; j++) {
            if (sortedEdges[j].weight > sortedEdges[j + 1].weight) {
                Edge temp = sortedEdges[j];
                sortedEdges[j] = sortedEdges[j + 1];
                sortedEdges[j + 1] = temp;
            }
        }
    }

    // Array to store the parent of each vertex
    int parent[MAX_SIZE];
    // Array to store the rank of each vertex
    int rank[MAX_SIZE] = {0};

    // Initialize parent array
    for (int i = 0; i < MAX_SIZE; i++)
        parent[i] = i;

    int i = 0; // Index variable for sortedEdges
    while (resultIndex < MAX_SIZE - 1 && i < sortedEdgesIndex) {
        Edge nextEdge = sortedEdges[i++];

        int x = findParent(parent, nextEdge.src);
        int y = findParent(parent, nextEdge.dest);

        // If including this edge doesn't cause cycle, include it in result and increment the index of result
        if (x != y) {
            result[resultIndex++] = nextEdge;
            unionSet(parent, rank, x, y);
        }
    }

    // Calculate total weight of MST
    int minCost = 0;
    for (int i = 0; i < resultIndex; i++)
        minCost += result[i].weight;

    return minCost;
}

// Function to find the vertex with minimum distance value, from
// the set of vertices not yet included in the shortest path tree
int minDistance(int distance[], bool inMST[]) {
    int min = INF, min_index;

    for (int v = 0; v < MAX_SIZE; v++) {
        if (inMST[v] == false && distance[v] < min) {
            min = distance[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the constructed MST stored in parent[]
int printMST(int parent[], int graph[MAX_SIZE][MAX_SIZE]) {
    printf("Edge   Weight\n");
    int mstWeight = 0;
    for (int i = 1; i < MAX_SIZE; i++) {
        printf("%c - %c    %d \n", 'A' + parent[i], 'A' + i, graph[i][parent[i]]);
        mstWeight += graph[i][parent[i]];
    }
    printf("\nMinimum Spanning Tree Weight: %d\n", mstWeight);
    return mstWeight;
}

// Function to construct and print MST for a graph represented using adjacency matrix
int prims(int graph[MAX_SIZE][MAX_SIZE], int start) {
    int parent[MAX_SIZE]; // Array to store constructed MST
    int distance[MAX_SIZE]; // Key values used to pick minimum weight edge in cut
    bool inMST[MAX_SIZE]; // To represent set of vertices not yet included in MST

    // Initialize all distances as INFINITE and inMST[] as false
    for (int i = 0; i < MAX_SIZE; i++) {
        distance[i] = INF;
        inMST[i] = false;
    }

    // Distance of source vertex from itself is always 0
    distance[start] = 0;
    parent[start] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < MAX_SIZE - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet included in MST
        int u = minDistance(distance, inMST);

        // Add the picked vertex to the MST set
        inMST[u] = true;

        // Update distance value of the adjacent vertices of the picked vertex
        for (int v = 0; v < MAX_SIZE; v++) {
            // Update distance[v] only if is not inMST[v], there is an edge from u to v, and total weight of path from start to v through u is smaller than current value of distance[v]
            if (!inMST[v] && graph[u][v] && graph[u][v] < distance[v]) {
                parent[v] = u;
                distance[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    return printMST(parent, graph);
}

int main() {
    int graph[MAX_SIZE][MAX_SIZE] = {
        /* A    B    C    D    E    F    G    H*/
        {INF,   6, INF,   1, INF, INF, INF, INF},
        {  6, INF,   5,   2,   4, INF, INF, INF},
        {INF,   5, INF, INF,   5, INF, INF, INF},
        {  1,   2, INF, INF,   1, INF, INF, INF},
        {INF,   4,   5,   1, INF,   5, INF,   2},
        {INF, INF, INF, INF,   5, INF,   3,   7},
        {INF, INF, INF, INF, INF,    3, INF,   4},
        {INF, INF, INF, INF,   2,    7,   4, INF}
    };

    // Perform DFS
    bool visited[MAX_SIZE] = {false};
    printf("DFS Traversal: ");
    dfs(graph, 0, visited);
    printf("\n");

    // Perform BFS
    printf("BFS Traversal: ");
    bfs(graph, 0);
    printf("\n");

    // Perform Dijkstra's algorithm
    printf("Dijkstra's Shortest-Path:\n");
    int *shortest_distances = dijkstra(graph, 0);
    displayShortestPaths(shortest_distances);
    free(shortest_distances);

    // Perform Prim's algorithm
    printf("Prim's Minimum Spanning Tree Weight: %d\n", prims(graph, 0));

    // Perform Kruskal's algorithm
    printf("Kruskal's Minimum Spanning Tree Weight: %d\n", kruskal(graph, MAX_SIZE));

    return 0;
}
