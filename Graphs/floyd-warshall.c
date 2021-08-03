#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int min(int a, int b) {
	return a < b ? a : b;
}

/*Floyd-Warshall works on the basis of a recursive definition of shortedt path between two nodes
D(x,y,k) = Shortest path between node x and y that uses nodes 1 to k as intermediates nodes
So D(x,y,0) = Shortest path between x and y that doesn't use any intermediate node,
			= direct edge weight or infinity if there is no edge between x and y

	D(x,y,k) = min(shortest path from x to y that doesn't uses k as intermediate node, shortest path from x to y that does uses k as intermediatory
			 = min(D(x,y,k-1), D(x,k,k-1)+D(k,y,k-1))
	When we use k as intermediate node then it splits up into part 1. Shortest path from x to k which uses 1 to k-1 as intermediate nodes
																   2.  Shortest path from k to y which uses 1 to k-1 as intermediate nodes
																   k-1 because we have used k

	D(x,y,n) = Is what we are looking for, shortest path from x to y using 1 to n as intermediate nodes
	If we simply run this recursive code it will take exponential time and there are overlapping subproblems
	Now number of sub-problems = O(n^3) as 1<=x,y<=n, 0<=k<=n
	Hence we using Bottom-Up approach*/
void floyd_warshall(int V, int (*dist)[V]) {  //Time = O(n^3)
	for (int k = 1; k < V; ++k)
	{
		for (int i = 0; i < V; ++i)
		{
			for (int j = 0; j < V; ++j)
			{
				/*This is just to avoid overflow*/
				if (dist[i][j] == INT_MAX || dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) continue;

				/*dist[i][j] = shortest path from i to j that doesn't uses k as intermediate node
				dist[i][k] = shortest path from i to k that  uses k as intermediate node
				dist[k][j] = shortest path from k to j that  uses k as intermediate node*/
				dist[i][j] = min(dist[i][j], (dist[i][k] + dist[k][j]));
			}
		}
	}
}


int main() {

	int V, n, x, y, w, bidir;

	//Input for number of vertices and edges
	scanf("%d %d", &V, &n);

	int dist[V][V];

	long adjMat[V][V];
	for (int i = 0; i < V; ++i)
	{
		for (int j = 0; j < V; ++j)
		{
			adjMat[i][j] = INT_MAX;
		}
	}

	/*Input for the graph*/
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d %d %d", &x, &y, &w, &bidir);
		adjMat[x][y] = w;
		if (bidir) {
			adjMat[y][x] = w;
		}
	}

	for (int i = 0; i < V; ++i)
	{
		for (int j = 0; j < V; ++j)
		{
			/*dist[i][j] = adj[i][j] = shortest path from x to y without any intermediate nodes*/
			dist[i][j] = adjMat[i][j];
		}
	}

//	print(V, adjMat);
	floyd_warshall(V, dist);
	for (int i = 0; i < V; ++i)
	{
		printf("\t%d", i);
	} printf("\n");

	for (int i = 0; i < V; ++i)
	{
		printf("%d\t", i );
		for (int j = 0; j < V; ++j)
		{
			if (dist[i][j] == INT_MAX) {
				/*Means there is no path*/
				printf("%d\t", -1);
			} else

				printf("%2d\t", dist[i][j]);
		} printf("\n");
	}


	return 0;
}