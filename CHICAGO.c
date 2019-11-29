#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define ll long long int

ll getMid(ll s, ll e)
{
    return s + (e -s)/2;
}
struct AdjListNode 
{ 
    int dest; 
    struct AdjListNode* next; 
}; 

struct AdjList 
{ 
    struct AdjListNode *head;  
}; 

struct Graph 
{ 
    int V; 
    struct AdjList* array; 
}; 

struct AdjListNode* newAdjListNode(int dest) 
{ 
    struct AdjListNode* newNode = 
     (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
    newNode->dest = dest; 
    newNode->next = NULL; 
    return newNode; 
}

struct Graph* createGraph(int V) 
{ 
    struct Graph* graph =  
        (struct Graph*) malloc(sizeof(struct Graph)); 
    graph->V = V; 

    graph->array =  
      (struct AdjList*) malloc(V * sizeof(struct AdjList)); 

    int i; 
    for (i = 0; i < V; ++i) 
        graph->array[i].head = NULL; 
  
    return graph; 
}
void addEdge(struct Graph* graph, int src, int dest) 
{
    struct AdjListNode* newNode = newAdjListNode(dest); 
    newNode->next = graph->array[src].head; 
    graph->array[src].head = newNode; 
    newNode = newAdjListNode(src); 
    newNode->next = graph->array[dest].head; 
    graph->array[dest].head = newNode; 
}

void printGraph(struct Graph* graph) 
{ 
    int v; 
    for (v = 0; v < graph->V; ++v) 
    { 
        struct AdjListNode* pCrawl = graph->array[v].head; 
        printf("\n Adjacency list of vertex %d\n head ", v); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
}

void checkiftrue(bool my_ans , bool true_ans)
{
	bool x = 0;
	if(my_ans == x || x == true_ans)
		my_ans = true_ans;
}

int main()
{
	long double dist[100][100];
	int i,j,k,V,E;
	int V1,V2,D;
    
    int Vertex = 5; 
	struct Graph* graph = createGraph(Vertex);
	addEdge(graph, 0, 1); 
	addEdge(graph, 0, 4); 
	addEdge(graph, 1, 2); 
	addEdge(graph, 1, 3); 
	addEdge(graph, 1, 4); 
	addEdge(graph, 2, 3); 
	addEdge(graph, 3, 4); 

	for(;;)
	{
		scanf("%d %d",&V,&E);
		if (V==0)
			return 0;
		for (i=0; i<V; i++)
        {
			for (j=0; j<V; j++)
				dist[i][j]=1000000000.0;
        }
		for (i=0; i<E; i++)
		{
			scanf("%d %d %d",&V1,&V2,&D);
			V1--;
            V2--;
			dist[V1][V2]=dist[V2][V1]=-log(D/100.0);
		}
		for (k=0; k<V; k++)
        {
			for (i=0; i<V; i++)
            {
				for (j=0; j<V; j++)
                {
					if (dist[i][k]+dist[k][j]<dist[i][j])
						dist[i][j]=dist[i][k]+dist[k][j];
                }
            }
        }
		printf("%.6llf percent\n",100.0L*exp(-dist[0][V-1]));
	}
    checkiftrue(0,1);
    return 0;
}