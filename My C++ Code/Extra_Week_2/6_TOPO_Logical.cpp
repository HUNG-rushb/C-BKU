#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
using namespace std;

vector<int> topologicalSorting(vector<vector<int>> graph)
{
    //      https://iq.opengenus.org/topological-sort-bfs/

    //      KAHN's algorithm

    //     Step 1:  Create an adjacency list called graph

    //     Step 2:  Call the topological_sorting() function
    //         Step 2.1: Create a queue and an array called indegree[]
    //         Step 2.2: Calculate the indegree of all vertices by traversing over graph
    //         Step 2.3: Enqueue all vertices with degree 0

    //     Step 3:  While the queue is not empty repeat the below steps
    //         Step 3.1: Dequeue the element at front from the queue and push it into the solution vector
    //         Step 3.2: Decrease the indegree of all the neighbouring vertex of currently dequed element,
    //                   if indegree of any neigbouring vertex becomes 0 enqueue it.
    //         Step 3.3: Enqueue all vertices with degree 0.

    //     Step 4:  If the queue becomes EMPTY return the solution vector.

    //     Step 5:  Atlast after return from the topological_sorting() function,
    //              print contents of returned vector.
    // ---------------------------------------------------------------------------------------------------------------

    // In-degree (Bac toi)
    vector<int> in_degree(graph.size(), 0);
    //  Queue chua cac vertex cho duoc duyet
    queue<int> myQueue;
    // Solution - ket qua
    // Co the xai stack nhung kieu tra ve la vector
    vector<int> solution;

    // Truyen vao gia tri in-degree (Bac toi) cua tung vertex
    int graphSize = graph.size();
    for (int i = 0; i < graphSize; i++)
    {
        int current_vector_size = graph[i].size();
        for (int j = 0; j < current_vector_size; j++)
        {
            // Iterate over all edges
            // Vi day la do thi co huong
            in_degree[graph[i][j]]++;
        }
    }

    // Enqueue all nodes with in-degree 0
    // Bac toi cua dinh do = 0 nghia la khong co dinh nao tro vao no
    // Cho vao myQueue
    for (int i = 0; i < graphSize; i++)
    {
        if (in_degree[i] == 0)
        {
            myQueue.push(i);
        }
    }

    // Remove one node after the other
    while (myQueue.size() > 0)
    {
        int currentNode = myQueue.front();
        myQueue.pop();
        solution.push_back(currentNode);

        // Duyet vao nhung neighbour cua current Node
        int current_vector_size = graph[currentNode].size();
        for (int j = 0; j < current_vector_size; j++)
        {
            // Remove all edges
            // Xoa tat ca cac canh noi den current Node
            int neighbourNode = graph[currentNode][j];

            //The vertices directly connected to current Nodeare decrease by 1
            in_degree[neighbourNode]--;

            // Neu in-degree tai neighbour node nay = 0
            if (in_degree[neighbourNode] == 0)
            {
                // Current neighbour node has now no more incoming edges
                myQueue.push(neighbourNode);
            }
        }
    }

    // Neu nhu khong co thu tu TOPO
    // size cua solution se khong bang size cua graph
    // Clear solution
    int solution_size = solution.size();
    if (solution_size < graphSize)
        solution.clear();

    // Co thu tu TOPO
    return solution;
}

int main()
{
    int n = 6;
    int G[6][6] = {
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0}};

    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (G[i][j] == 1)
                graph[i].push_back(j);
        }
    }

    vector<int> res = topologicalSorting(graph);
    if (res.empty())
        printf("-1");
    else
    {
        for (int e : res)
            printf("%d ", e);
    }

    return 0;
}
