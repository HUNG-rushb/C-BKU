#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
using namespace std;

bool isBipartite(vector<vector<int>> graph)
{
    // Initially color all the vertices in WHITE and as algorithm advances, these vertices will be colored as RED or GREEN.

    // Initialize queue.
    // Pick a vertex with color WHITE, now color it with RED. Add it to the queue.

    // While the queue is not empty
    // take out a vertex from the queue. let’s say its vertex v.

    // Now check all the neighbors of vertex v.

    // If these neighbors are in WHITE color, color them with the alternate color of vertex v
    // means if v is RED, color the neighbors in GREEN and if v is GREEN, color the neighbors in RED.
    // and add these neighbors in the queue.

    // If any of these neighbors are not in WHITE color, which means it was already colored earlier,
    // check its color and if it has the same color as vertex v that means vertices connecting v
    // and this neighbor cannot be in two colors means the graph is not bipartite. return false.

    // ------------------------------------------------------ END ALGORITHM ------------------------------------------------------

    // STATUS
    enum Status
    {
        WHITE,
        RED,
        GREEN
    };

    // Array chua status cua cac dinh
    Status *vertex_Status = new Status[graph.size()]{WHITE};

    // Queue chua cac dinh
    queue<int> myQueue;

    int graphSize = graph.size();

    // Phai duyet qua tat ca cac dinh
    // vi co truong hop 1 dinh chi co 1 dinh hang xom
    for (int vertex = 0; vertex < graphSize; ++vertex)
    {
        if (vertex_Status[vertex] == WHITE)
        {
            vertex_Status[vertex] = RED;
            myQueue.push(vertex);

            // Duyet qua tat ca cac hang xom cua current Vertex
            while (!myQueue.empty())
            {
                int current_Vertex = myQueue.front();
                myQueue.pop();

                // Duyet qua cac neighbour trong graph[current_Vertex]
                vector<int>::iterator myIterator;
                for (myIterator = graph[current_Vertex].begin(); myIterator != graph[current_Vertex].end(); myIterator++)
                {
                    // Neighbour is WHITE
                    if (vertex_Status[*myIterator] == WHITE)
                    {
                        // Must be another color
                        if (vertex_Status[current_Vertex] == RED)
                        {
                            vertex_Status[*myIterator] = GREEN;
                            myQueue.push(*myIterator);
                        }
                        // Must be another color
                        else if (vertex_Status[current_Vertex] == GREEN)
                        {
                            vertex_Status[*myIterator] = RED;
                            myQueue.push(*myIterator);
                        }
                    }
                    // Neighbour NOT in WHITE color
                    else
                    {
                        if (vertex_Status[current_Vertex] == vertex_Status[*myIterator])
                            return false;
                    }
                }
            }
        }
    }

    return true; //if all vertices can be colored with alternate color
}

int main()
{
    int G[6][6] = {
        {0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0}};

    int n = 6;

    // Mang 2 chieu (2D Array)
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (G[i][j])
                graph[i].push_back(j);
        }
    }

    isBipartite(graph) ? cout << "Yes" : cout << "No";
}