#include <iostream>
#include <queue>
#include <vector>
#include <math.h>

using namespace std;

// Some helping functions
#define INF 1e9
int minDistance(int dist[], bool sptSet[], int V)
{
    // Initialize min value
    int min = INF, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

int Dijkstra(int **graph, int src, int dst)
{
    if (src == dst)
        return 0;
    int i = 0;
    int V = 0;
    while (graph[0][i] <= INT8_MAX)
    {
        ++V;
        ++i;
    }
    V = sqrt(V);

    int *dist = new int[V];
    bool *sptSet = new bool[V];
    for (int i = 0; i < V; i++)
        dist[i] = INF, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    return dist[dst];
}

int main()
{
    int n = 6;
    int init[6][6] = {
        {0, 10, 20, 0, 0, 0},
        {10, 0, 0, 50, 10, 0},
        {20, 0, 0, 20, 33, 0},
        {0, 50, 20, 0, 20, 2},
        {0, 10, 33, 20, 0, 1},
        {0, 0, 0, 2, 1, 0}};

    int **graph = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        graph[i] = init[i];
    }

    cout << Dijkstra(graph, 0, 1);

    return 0;
}