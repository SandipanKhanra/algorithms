#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

/*In Bellman-Ford the graph representation actually doesn't matter whether is Adjacency list or Adjacency matrix
As it goes through all the edges in each iteration for |V|-1 times
    Time Complexity O(VE)
*/

/*Bellman-Ford Algorithm for detecting negative edge weight cycle in the graph
If there is a negative weight cycle then it will report that.
Else it will find the shortest distances to all vertices reachable from s*/
int bellman_ford(vector<vector<int>> edges, int V, int s)
{
    //Initially shortest distance to every vertex is Infinity
    vector<int> dist(V, INT_MAX);

    int src, dst, wt, isCycle = 0;
    dist[s] = 0;//Shortest distance to starting vertex is 0

    for (int i = 1; i < V; i++) //Runs for |V|-1 times
    {
        /*In each iteration relaxed an edge if possible*/
        for (auto edge : edges) // Runs for |E| times
        {
            src = edge[0];
            dst = edge[1];
            wt = edge[2];
            /*Relaxation step, if current distance is greater than candidate shortest distance then update*/
            if (dist[src] != INT_MAX && dist[dst] > dist[src] + wt)
            {
                dist[dst] = dist[src] + wt;
            }
        }
    }

    /*This is the checking for negative weight cycle*/
    for (auto edge : edges)
    {
        src = edge[0];
        dst = edge[1];
        wt = edge[2];
        if (dist[src] != INT_MAX && dist[dst] > dist[src] + wt)
        {
            /*If this condition is true it means still we can relax an edge and it will introduce a cycle as it repeats a vetex
            As we are are still able to reduce the weight thats why its a negative weight cycle*/
            isCycle = 1;
            break;
        }
    }
    return isCycle;
}



int main()
{

    int V, n, x, y, w, src;
    scanf("%d %d", &V, &n);//Number of vertices and edges

    vector<vector<int>> edges; //To store edges

    /*Input for the edges*/
    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d %d", &x, &y, &w);
        vector<int> t;
        t.push_back(x);
        t.push_back(y);
        t.push_back(w);
        edges.push_back(t);
        t.clear();
    }
    cin >> src;

    int isCycle = bellman_ford(edges, n, src);
    if (isCycle)
    {
        printf("%s\n", "Graph contains a negative cycle");
    }
    else
    {
        printf("%s\n", "Graph doesn't contains a negative cycle");
    }

    return 0;
}
