#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

/*Simple node*/
struct node {
	int data, wt;
	struct node *next;
};

/*Node having info regarding indegree and outdegree
It is used as head node for each list*/
struct nodeHead {
	int inDegree, outDegree;
	struct node *adjNode;
};


struct graph {
	int V;
	struct nodeHead *adjList;
};
typedef struct graph Graph;


/*Creates a new simple node*/
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
	g->adjList = (struct nodeHead*)calloc(V, sizeof(struct nodeHead));
	return g;
}


/*Adds a new edge to the graph, bidir acts as if the edge is bidirectional or not*/
void addEdgeModified(struct nodeHead *adjList, int x, int y, int w, int bidir ) {

	/*Checks if given adjacency list is empty*/
	if (adjList[x].adjNode == NULL) {
		adjList[x].adjNode = makeNode(y, w);
		adjList[x].outDegree += 1;
		adjList[y].inDegree += 1;

	}
	else { /*Else adds the new vertex to the end of the list*/
		struct node *temp = adjList[x].adjNode;
		while (temp->next) {
			temp = temp->next;
		}
		adjList[x].outDegree += 1;
		adjList[y].inDegree += 1;
		temp->next = makeNode(y, w);
	}

	/*If edge is bidirectional then execute this portion of code*/
	if (bidir && adjList[y].adjNode == NULL) {
		adjList[y].adjNode = makeNode(x, w);
		adjList[y].outDegree += 1;
		adjList[x].inDegree += 1;
	}
	else if (bidir) { /*Similarly adds the next vertex to the end of the list*/
		struct node *temp = adjList[y].adjNode;
		while (temp->next) {
			temp = temp->next;
		}
		adjList[y].outDegree += 1;
		adjList[x].inDegree += 1;
		temp->next = makeNode(x, w);
	}
}

/*Utility function to do depth-first-search on a vertex*/
int dfsVisit(struct nodeHead *adjList, int src, int *visited, int* callStack) {
	visited[src] = 1;
	callStack[src] = 1; //To indicate that the current vertex is in call stack
	struct node *temp = adjList[src].adjNode;
	int flag = 0;

	/*Visiting all the vertices adjacent to src*/
	while (temp) {
		int j  = temp->data;
		if (visited[j] == 0 && dfsVisit(adjList, j, visited, callStack)) {
			return 1;
		} else if (callStack[j] == 1) { //If the current vertex is in call stack that means there is a back edge
			return 1;
		}
		temp = temp->next;
	}
	callStack[src] = 0; //Indicates that the src vertex is now out of call stack
	return 0;
}

/*Function to go over all the vertices and if necessory then do dfs on that vertex*/
int dfs(struct nodeHead *adjList, int V) {
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
			if ((isCycle = dfsVisit(adjList, i, visited, callStack)) == 1)
				return isCycle;

		}
	}
	return isCycle;
}

/*Function to do topological sort*/
vector<int> topologicalSort(struct nodeHead *adjList, int V) {
	queue<int> q;
	vector<int> topologicalOrder;
	int i;
	/*Going over all the vertices,if outdegree is 0 then push that vertex on the queue*/
	for (i = 0; i < V; ++i)
	{
		if (adjList[i].inDegree == 0)
			q.push(i);
	}
	while (!q.empty()) {
		i = q.front();
		topologicalOrder.push_back(i);
		q.pop();
		struct node *temp = adjList[i].adjNode;
		while (temp) {
			int j = temp->data;
			adjList[j].inDegree--;
			if (adjList[j].inDegree == 0)
				q.push(j);
			temp = temp->next;
		}
	}
	return topologicalOrder;
}

/*Function to print the given graph*/
void printGraph(struct nodeHead *adjList, int V) {
	for (int i = 0; i < V; ++i)
	{
		printf("inDegree and outDegree of node %d is %d and %d\n", i, adjList[i].inDegree, adjList[i].outDegree);
		printf("Nodes adjacent to %d --> ", i);
		struct node *temp = adjList[i].adjNode;

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
		addEdgeModified(G->adjList, x, y, w, bidir);
	}

	/*Function to print the given graph*/
	printGraph(G->adjList, V);

	int isCycle = 0;
	struct nodeHead *adjList = G->adjList;

	/*Calling  topologicalSort function to do a topological sort*/
	vector<int> topoOrder = topologicalSort(G->adjList, V);

	/*Check for cycle*/
	for (int i = 0; i < V; ++i)
	{
		if (adjList[i].inDegree > 0) {
			isCycle = 1;
			break;
		}
	}

	if (isCycle) { //If there is a cycle, prints error message
		printf("There is a cycle in the graph\n");
	}
	else { //Else prints the topological ordering
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

