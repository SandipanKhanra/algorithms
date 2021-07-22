#include<stdio.h>
#include <stdlib.h>

/*Simple node*/
struct node {
	int data, wt;
	struct node *next;
};

struct graph {
	int V;
	struct node** adjList;
};
typedef struct graph Graph;

/*Creates a new simple node*/
struct node* makeNode(int x, int wt) {
	struct node*  temp = (struct node* )malloc(sizeof(struct node));
	temp->data = x;
	temp->wt = wt;
	temp->next = NULL;
	return temp;
}

Graph* createGraph(int V) {

	Graph* g = (Graph*)malloc(1 * sizeof(Graph));
	g->V = V;
	g->adjList = (struct node**)calloc(V , sizeof(struct node*));
	return g;
}

/*This function adds an edge to the graph,but implementation is for simpler graph
with few information regarding any node*/
void addEdge(struct node **adjList, int x, int y, int w, int bidir )
{
	if (adjList[x] == NULL)
		adjList[x] = makeNode(y, w);
	else {
		struct node *temp = adjList[x];
		while (temp->next && temp->wt <= w) {
			temp = temp->next;
		}
		temp->next = makeNode(y, w);
	}

	if (bidir && adjList[y] == NULL)
		adjList[y] = makeNode(x, w);
	else if (bidir) {
		struct node *temp = adjList[y];
		while (temp->next && temp->wt <= w) {
			temp = temp->next;
		}
		temp->next = makeNode(x, w);
	}
}

/*Function to print the graph*/
void printGraph(struct node **adjList, int V) 
{
	for (int i = 0; i < V; ++i)
	{
		printf("Nodes adjacent to %d --> ", i);
		struct node *temp = adjList[i];

		while (temp) {
			printf("%d %d(Wt) ", temp->data, temp->wt);
			temp = temp->next;
		}
		printf("\n");
	}
}

/*Driver code*/
int main() {
  /*Declaring variables for taking input of #vertices,#edges,starting point,ending point,edge weight*/
	int V, n, x, y, w, bidir;
  
  /*Taking input #vertices,#edges*/
	scanf("%d %d", &V, &n);
  
  /*Initializing a graph with V vertices*/
	Graph* G = createGraph(V);
  
  /*Taking input for the edges*/
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d %d %d", &x, &y, &w, &bidir);
		addEdge(G->adjList, x , y  , w, bidir);
	}
  
  /*Printing the given graph*/
	printGraph(G->adjList, V);
  
  //Freeing the space allocated for the graph G
	free(G);
  
	return 0;
}
