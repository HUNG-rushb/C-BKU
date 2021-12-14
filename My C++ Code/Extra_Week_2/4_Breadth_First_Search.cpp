#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
using namespace std;

void bfs(vector<vector<int>> graph, int start)
{
    // create a queue Q
    // mark v as visited and put v into Q
    // while Q is non-empty
    //     remove the head u of Q
    //     mark and enqueue all (unvisited) neighbours of u

    bool *visited = new bool[graph.size()]{false};

    visited[start] = true;

    queue<int> myQueue;
    myQueue.push(start);

    while (!myQueue.empty())
    {
        int current_Vertex = myQueue.front();
        cout << current_Vertex << " ";
        myQueue.pop();

        vector<int>::iterator myIterator;
        for (myIterator = graph[current_Vertex].begin(); myIterator != graph[current_Vertex].end(); myIterator++)
        {
            if (visited[*myIterator] == false)
            {
                visited[*myIterator] = true;
                myQueue.push(*myIterator);
            }
        }
    }
}

int main()
{
    int init_graph[10][10] =
        {
            {0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
            {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
            {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
            {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 1, 0}};

    int n = 10;

    vector<vector<int>> graph(n, vector<int>());

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // 1
            if (init_graph[i][j])
                graph[i].push_back(j);
        }
    }

    bfs(graph, 0);
}