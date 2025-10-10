#include <stdio.h>
#include <limits.h>

#define V 5 // Number of vertices in the graph

// Function to print the constructed distance array
void printSolution(int dist[])
{
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function to find the vertex with the minimum distance value, from the set of vertices not yet processed
int minDistance(int* dist, int* visited)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (visited[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Dijkstra's algorithm implementation
void dijkstra (int graph[V][V], int src) {
    int dist[V];
    int visited[V];
    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    
    dist[src] = 0;
    
    for (int i = 0; i < V - 1; i++) {
        int k = minDistance(dist, visited);
        
        visited[k] = 1;
        
        for (int j = 0; j < V; j++) {
            if (visited[j] == 0 && graph[k][j] && dist[j] > dist[k] + graph[k][j]) {
                dist[j] = dist[k] + graph[k][j];
            }
        }
    }
    
    printSolution(dist);
}

int main()
{
    // Example graph represented as an adjacency matrix
    int graph[V][V] = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}};

    int source = 0; // Starting vertex
    printf("Dijkstra's Shortest Path Algorithm:\n\n");
    dijkstra(graph, source);

    return 0;
}
