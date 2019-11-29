#include <stdio.h>
#include <stdlib.h>
#define ll long long int
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

int main()
{
    int t;
    scanf("%d",&t);
    ll n, r, m, x, y;
    while(t--)
    {
        scanf("%lld %lld %lld", &n, &r, &m);
        struct Graph* graph = createGraph(n);
        int i;
        for(i=0;i<r;++i)
        {
            scanf("%lld %lld", &x, &y);
            addEdge(graph, x, y);
        }
    }
    return 0;
}