#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

/*Simple node*/
struct node {
	int data, wt;
	struct node *next;
};

struct graph {
	int V;
	struct node **adjList;
};
typedef struct graph Graph;


/*Creates a new node*/
struct node* makeNode(int x, int w) {
	struct node*  temp = (struct node* )malloc(sizeof(struct node));
	temp->data = x;
	temp->wt = w;
	temp->next = NULL;
	return temp;
}

/*Creates a new graph with given number of vertices*/
Graph* createNewGraph(int V) {
	Graph* g = (Graph*)calloc(1, sizeof(struct graph));
	g->V = V;
	/*Creates an array of head nodes*/
	g->adjList = (struct node**)calloc(V, sizeof(struct node*));
	return g;
}


/*Adds a new edge to the graph, bidir acts as if the edge is bidirectional or not*/
void addEdgeModified(struct node **adjList, int x, int y, int w, int bidir) {

	/*Checks if given adjacency list is empty*/
	if (adjList[x] == NULL) {
		adjList[x] = makeNode(y, w);

	}
	else { /*Else adds the new vertex to the end of the list*/
		struct node *temp = adjList[x];
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = makeNode(y, w);
	}

	/*If edge is bidirectional then execute this portion of code*/
	if (bidir && adjList[y] == NULL) {
		adjList[y] = makeNode(x, w);
	}
	else if (bidir) { /*Similarly adds the next vertex to the end of the list*/
		struct node *temp = adjList[y];
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = makeNode(x, w);
	}
}

/*Utility function to do Depth-First-Search on a vertex*/
int dfsVisit(struct node **adjList, int src, int *visited, int *parent, int* callStack) {
	visited[src] = 1;
	callStack[src] = 1; //To indicate that the current vertex is in call stack
	struct node *temp = adjList[src];
	int flag = 0;

	/*Visiting all the vertices adjacent to src*/
	while (temp) {
		int j  = temp->data;
		if (visited[j] == 0 ) {
			parent[j] = src;
			if (dfsVisit(adjList, j, visited, parent, callStack) == 1) {
				printf("Cycle Edge from %d to %d\n", src, j);
				return 1;
			}
		} else if (callStack[j] == 1) {
			printf("Back Edge from %d to %d\n", src, j);//If the current vertex is in call stack that means there is a back edge
			return 1;
		}
		temp = temp->next;
	}
	callStack[src] = 0; //Indicates that the src vertex is now out of call stack
	return 0;
}

/*Function to go over all the vertices and if necessory then do dfs on that vertex*/
int dfs(struct node **adjList, int *parent, int V) {
	/*Initialization*/
	int *visited = new int[V];
	int *callStack = new int[V];

	int isCycle;

	for (int i = 0; i < V; ++i)
	{
		visited[i] = 0;
		callStack[i] = 0;
	}
	/*Going over every vertex*/
	for (int i = 0; i < V; ++i)
	{
		if (visited[i] == 0) {
			parent[i] = -1;
			if ((isCycle = dfsVisit(adjList, i, visited, parent, callStack)) == 1)
				return isCycle;

		}
	}
	return isCycle;
}

/*Function to do topological sort,on the basis of indegree of a vertex*/
vector<int> topologicalSort(struct node **adjList, int *inDegree , int V) {
	queue<int> q;
	vector<int> topologicalOrder;
	int i;
	/*Going over all the vertices,if indegree is 0 then push that vertex on the queue
	As there is no pe-requisite for this vertex*/
	for (i = 0; i < V; ++i)
	{
		if (inDegree[i] == 0)
			q.push(i);
	}
	while (!q.empty()) {
		i = q.front();
		topologicalOrder.push_back(i);
		q.pop();
		struct node *temp = adjList[i];
		while (temp) {
			int j = temp->data;
			inDegree[j]--;
			if (inDegree[j] == 0)
				q.push(j);
			temp = temp->next;
		}
	}
	return topologicalOrder;
}

/*Function to print the given graph*/
void printGraph(struct node **adjList, int *inDegree, int V) {
	for (int i = 0; i < V; ++i)
	{
		printf("inDegree of node %d is %d\n", i, inDegree[i]);
		printf("Nodes adjacent to %d --> ", i);
		struct node *temp = adjList[i];

		while (temp) {
			printf("%d %d\t", temp->data, temp->wt);
			temp = temp->next;
		}
		printf("\n");
	}
}



int main() {

	int V, n, x, y, w, bidir;
	scanf("%d %d", &V, &n);//Number of vertices and edges

	/*Creates a new graph*/
	Graph* G = createNewGraph(V);
	int *inDegree = (int *)calloc(V, sizeof(int));
	int *parent = new int[V];
	for (int i = 0; i < V; ++i)
	{
		parent[i] = -1;
	}

	/*Take input for the edges*/
	// 6 10
	// 0 1 2 0
	// 0 2 6 0
	// 1 2 7 0
	// 1 3 4 0
	// 1 4 2 0
	// 2 3 -1 0
	// 2 4 1 0
	// 3 4 -2 0
	// 5 0 5 0
	// 5 1 3 0
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d %d %d", &x, &y, &w, &bidir);
		if (bidir) {
			inDegree[x]++;
			inDegree[y]++;
		} else {
			inDegree[y]++;
		}
		addEdgeModified(G->adjList, x, y, w, bidir);
	}

	/*Function to print the given graph*/
	//printGraph(G->adjList, inDegree, V);

	int isCycle = dfs(G->adjList, parent, V);

	/*Check for cycle*/
	if (isCycle) { //If there is a cycle, prints error message
		printf("There is a cycle in the graph\n");
		for (int i = 0; i < V; ++i)
		{
			printf("%d ", parent[i]);
		} printf("\n");
	}
	else {
		/*Calling  topologicalSort function to do a topological sort*/
		vector<int> topoOrder = topologicalSort(G->adjList, inDegree, V);
		//Prints the topological ordering
		printf("%s", "Topological ordering is --> ");
		for (int i = 0; i < topoOrder.size(); ++i)
		{
			printf("%d ", topoOrder[i]);
		} printf("\n");
	}

	/*Finally frees the space allocated for the graph*/
	free(G);
	return 0;
}

