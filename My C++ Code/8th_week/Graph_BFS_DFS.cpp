#include <iostream>
#include <list>
#include <queue>
#include <stack>
using namespace std;

class Adjacency
{
private:
    list<int> adjList;
    int size;

public:
    Adjacency() {}
    Adjacency(int V) {}

    void push(int data)
    {
        adjList.push_back(data);
        size++;
    }

    void print()
    {
        for (auto const &i : adjList)
            cout << " -> " << i;
    }

    void printArray()
    {
        for (auto const &i : adjList)
            cout << i << " ";
    }

    int getSize()
    {
        return adjList.size();
    }

    int getElement(int idx)
    {
        auto it = adjList.begin();
        advance(it, idx);
        return *it;
    }
};

class Graph
{
private:
    int V;
    Adjacency *adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj = new Adjacency[V];
    }

    void addEdge(int v, int w)
    {
        adj[v].push(w);
        adj[w].push(v);
    }

    void printGraph()
    {
        for (int v = 0; v < V; ++v)
        {
            cout << "\nAdjacency list of vertex " << v << "\nhead ";
            adj[v].print();
        }
    }

    // BFS------------------------------------------------------------------------------------
    Adjacency *BFS(int v)
    {
        // v is a vertex we start BFS
        Adjacency *result = new Adjacency();

        queue<int> Traveled_node;

        bool *Visited = new bool[V];

        for (int i = 0; i < V; i++)
            Visited[i] = false;

        Traveled_node.push(v);
        Visited[v] = true;

        while (!Traveled_node.empty())
        {
            int counter = 1;

            int current = Traveled_node.front();
            Traveled_node.pop();

            result->push(current);

            for (int i = 0; i < this->adj[current].getSize(); i++)
            {
                if (Visited[this->adj[current].getElement(i)] == false)
                {
                    Visited[this->adj[current].getElement(i)] = true;
                    Traveled_node.push(this->adj[current].getElement(i));
                }
            }
        }

        return result;
    }

    // DFS------------------------------------------------------------------------------------
    void DFS_helper(int v, bool *traveled, Adjacency *result)
    {
        traveled[v] = true;
        result->push(v);

        for (int a = 0; a < this->adj[v].getSize(); a++)
        {
            if (traveled[this->adj[v].getElement(a)] == false)
            {
                DFS_helper(this->adj[v].getElement(a), traveled, result);
            }
        }
    }

    Adjacency *DFS(int v)
    {
        // v is a vertex we start DFS
        bool *Traveled = new bool[V];

        for (int i = 0; i < V; i++)
        {
            Traveled[i] = false;
        }

        Adjacency *result = new Adjacency();

        DFS_helper(v, Traveled, result);

        return result;
    }

    // TOPO logical---------------------------------------------------------------------------
    void topological_sort_helper(int start, bool *visited, stack<int> &S)
    {
        visited[start] = true;

        for (int i = 0; i < this->adj[start].getSize(); i++)
        {
            if (visited[this->adj[start].getElement(i)] == false)
            {
                topological_sort_helper(this->adj[start].getElement(i), visited, S);
            }
        }

        S.push(start);
    }

    void topologicalSort()
    {
        stack<int> my_stack;

        // Mark all the vertices as not visited
        bool *traveled = new bool[V];
        for (int i = 0; i < V; i++)
            traveled[i] = false;

        // Call the recursive helper function to store Topological
        // Sort starting from all vertices one by one
        for (int i = 0; i < V; i++)
            if (traveled[i] == false)
                topological_sort_helper(i, traveled, my_stack);

        // Print contents of stack
        while (my_stack.empty() == false)
        {
            cout << my_stack.top() << " ";
            my_stack.pop();
        }
    }
};

int main()
{

    int V = 6;
    int visited = 0;

    Graph g(V);
    Adjacency *arr = new Adjacency(V);
    int edge[][2] = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 4}, {3, 5}, {4, 5}};

    for (int i = 0; i < 8; i++)
    {
        g.addEdge(edge[i][0], edge[i][1]);
    }

    arr = g.BFS(visited);
    arr->printArray();
    delete arr;

    // int V = 8, visited = 0;

    // Graph g(V);
    // Adjacency *arr;
    // int edge[][2] = {{0,1}, {0,2}, {0,3}, {0,4}, {1,2}, {2,5}, {2,6}, {4,6}, {6,7}};
    // for(int i = 0; i < 9; i++)
    // {
    //     g.addEdge(edge[i][0], edge[i][1]);
    // }

    // // g.printGraph();
    // // cout << endl;
    // arr = g.DFS(visited);
    // arr->printArray();
    // delete arr;

    // Graph g(6);
    // g.addEdge(5, 2);
    // g.addEdge(5, 0);
    // g.addEdge(4, 0);
    // g.addEdge(4, 1);
    // g.addEdge(2, 3);
    // g.addEdge(3, 1);

    // g.topologicalSort();

    return 0;
}
