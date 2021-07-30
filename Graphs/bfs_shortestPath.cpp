#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;


/*This algorithm to find shortest path from a starting node is similar to Bellman-Ford as it also so to speak iterate
throgh atmost |V|-1 times,where |V|= #vertices. But it uses a queue data structure and somewhat intuitive than Bellman-Ford.
As in B-F we goes through every edge in each iteration and sort of like brute-froce.
But in this case we first pop a vertex from queue and from the adjacent vertices we push the nodes
whose current shortest distance is relabelled and which is not already in queue

Although running time here also is same as Bellman-Ford O(VE)

*/


/*Adds a new edge to the graph*/
void addEdge(vector<pair<int, int>> adjList[], int x, int y, int w) {
	adjList[x].push_back(make_pair(y, w));
}

int bfs_shortestPath(vector<pair<int, int>> adjList[], int V, int s, int *dist, int *parent) {
	queue<int> q;
	int *inQueue = new int[V]; //To keep track of which vertices are in queue right now
	int count = V - 1, v, w, u;
	for (int i = 0; i < V; ++i)
	{
		inQueue[i] = 0;
	}
	dist[s] = 0;
	parent[s] = -1;
	inQueue[s]  = 1;
	q.push(s);
	q.push(-1); //-1 is used to count the phases, as there can be atmost V-1 phases/iteration
	while (count > 0 && !q.empty())
	{
		u = q.front();
		q.pop();
		if (u == -1 && !q.empty()) //If both conditions hold true means there can be possible another phase
		{
			q.push(-1);
			count--;
		} else if (u == -1) { //It means queue is now empty
			count--;
		}
		else {
			inQueue[u] = 0;
			for (auto node : adjList[u]) //Go through adjacent vertices of u
			{
				v = node.first;
				w = node.second;
				if (dist[v] > dist[u] + w) //If we can reduce the current shortest distance to v then reduce it
				{
					dist[v] = dist[u] + w;
					parent[v] = u;
					if (inQueue[v] == 0)
					{
						//If v is not already in queue then push it in the queue, else do nothing
						q.push(v);
						inQueue[v] = 1;
					}
				}
			}
		}
	}
	/*After atmost V-1 phases the queue must be empty,otherwise there is a negative weight cycle*/
	if (q.empty()) return 0;
	return 1;


}

/*Function to print the given graph*/
void printGraph(vector<pair<int, int>> adjList[], int V) {
	for (int i = 0; i < V; ++i)
	{

		printf("Nodes adjacent to %d --> ", i);
		vector<pair<int, int>> temp = adjList[i];

		for (auto node : temp) {
			printf("%d %d\t", node.first, node.second);
		}
		printf("\n");
	}
}



int main() {

	int V, n, x, y, w, s;
	scanf("%d %d", &V, &n);//Number of vertices and edges

	/*Creates a new graph*/
	vector<pair<int, int>> adjList[V];

	int *parent = new int[V];
	int *dist = new int[V];
	for (int i = 0; i < V; ++i)
	{
		parent[i] = -1;
		dist[i] = INT_MAX;
	}

	// Input format
	// 6 10
	// 0 1 2
	// 0 2 6
	// 1 2 7
	// 1 3 4
	// 1 4 2
	// 2 3 -1
	// 2 4 1
	// 3 4 -2
	// 5 0 5
	// 1 5 -30
	// 0
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d %d", &x, &y, &w);
		addEdge(adjList, x, y, w);
	}

	/*Function to print the given graph*/
	//printGraph(adjList, V);
	cin >> s;

	int negCycle = bfs_shortestPath(adjList, V, s, dist, parent);
	if (negCycle) {
		printf("There is a negative cycle reachable from %d\n", s);
	} else
	{
		printf("%s\n", "There is no negative cycle");
		printf("Shortest path distances from %d are--->\n", s);

		for (int i = 0; i < V; ++i)
		{
			if (dist[i] == INT_MAX)
				printf("Node %d is unreachable from %d\n", i, s);
			else
				printf("Node %d has shortest path distance %d\n", i, dist[i] );
		}
	}

	return 0;
}
