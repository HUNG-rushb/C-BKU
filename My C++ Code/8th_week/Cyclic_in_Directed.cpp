#include <iostream>
#include <list>
using namespace std;

class DirectedGraph
{
    int V;
    list<int> *adj;
    bool isCyclicUtil(int v, bool visited[], bool *rs);

public:
    DirectedGraph()
    {
        V = 0;
        adj = NULL;
    }
    DirectedGraph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }
    bool is_cyclic_util(int v, bool *visited, bool *result)
    {
        if (visited[v] == false)
        {
            visited[v] = true;
            result[v] = true;
            list<int>::iterator i;
            for (i = this->adj[v].begin(); i != this->adj[v].end(); i++)
            {
                if (!visited[*i] && is_cyclic_util(*i, visited, result))
                {
                    return true;
                }
                else if (result[*i])
                {
                    return true;
                }
            }
        }
        result[v] = false;
        return false;
    }
    bool isCyclic()
    {
        // Student answer
        bool *visited = new bool[V];
        bool *result = new bool[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
            result[i] = false;
        }
        for (int i = 0; i < V; i++)
        {
            if (is_cyclic_util(i, visited, result))
            {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    DirectedGraph g(8);
    int edege[][2] = {{0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1}};

    for (int i = 0; i < 9; i++)
        g.addEdge(edege[i][0], edege[i][1]);

    if (g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";
}
