#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 5

// Function to perform Depth-First Search (DFS)
void dfs(int graph[MAX_SIZE][MAX_SIZE], int node, bool visited[]) {
    visited[node] = true;
    printf("%c ", 'A' + node);

    for (int x = 0; x < MAX_SIZE; x++) {
        if (graph[node][x] != INT_MAX && !visited[x]) {
            dfs(graph, x, visited);
        }
    }
}

// Function to perform Breadth-First Search (BFS) with minimum weight priority
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
            if (graph[node][x] != INT_MAX && !visited[x]) {
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
        for (int i = 0; i < MAX_SIZE; i++)
            shortest_distances[i] = INT_MAX;

        shortest_distances[start] = 0;

        for (int count = 0; count < MAX_SIZE - 1; count++) {
            int min_distance = INT_MAX, min_index;

            for (int v = 0; v < MAX_SIZE; v++) {
                if (!visited[v] && shortest_distances[v] <= min_distance) {
                    min_distance = shortest_distances[v];
                    min_index = v;
                }
            }

            visited[min_index] = true;

            for (int v = 0; v < MAX_SIZE; v++) {
                if (!visited[v] && graph[min_index][v] != INT_MAX && shortest_distances[min_index] != INT_MAX &&  
                                        shortest_distances[min_index] + graph[min_index][v] < shortest_distances[v]) {
                    shortest_distances[v] = shortest_distances[min_index] + graph[min_index][v];
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


int main() {
    system("cls");

    int graph[MAX_SIZE][MAX_SIZE] = {
        {INT_MAX, 6, INT_MAX, 1, INT_MAX},
        {6, INT_MAX, 5, 2, 4},
        {INT_MAX, 5, INT_MAX, INT_MAX, 5},
        {1, 2, INT_MAX, INT_MAX, 1},
        {INT_MAX, 4, 5, 1, INT_MAX}
    };
    int *shortest_distances[MAX_SIZE];
    bool visited[MAX_SIZE] = {false};

    printf("DFS Traversal: ");
    dfs(graph, 0, visited);
    printf("\n");

    printf("BFS Traversal: ");
    bfs(graph, 0);
    printf("\n");

    printf("Dijkstra Shortest-Path:");
    shortest_distances[0] = dijkstra(graph, 0);
    displayShortestPaths(shortest_distances[0]);

    printf("\nFloyd-Warshall Shortest-Path: ");
    for(int x = 1; x < MAX_SIZE; x++) {
        shortest_distances[x] = dijkstra(graph, x);
        displayShortestPaths(shortest_distances[x]);
    }

    for(int x = 0; x < MAX_SIZE; x++) {
        free(shortest_distances[x]);
    }
    return 0;
}
