#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define INF 1000000000;

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

int min(int a,int b)
{
    return a<b?a:b;
}

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int Vertex = 5;
	struct Graph* graph = createGraph(Vertex);
	addEdge(graph, 0, 1);
	addEdge(graph, 0, 4);
	addEdge(graph, 1, 2);
	addEdge(graph, 1, 3);
	addEdge(graph, 1, 4);
	addEdge(graph, 2, 3);
	addEdge(graph, 3, 4);

    int n,m,a,b,k,g,mygraph[1000][1000],adjacent[1000][1000],graphpath[1000],check,Marked[1000],travel[1000];
    scanf("%d %d",&n,&m);
    int i;
    for(i=0;i<n;i++)
    {
        int j;
        for(j=0;j<n;j++)
            adjacent[i][j]=mygraph[i][j]=INF;
    }
    scanf("%d %d %d %d",&a,&b,&k,&g);
    a--;
    b--;
    for(i=0;i<g;i++)
    {
        scanf("%d",&graphpath[i]);
        graphpath[i]--;
    }
    int x,y,t;
    for(i=0;i<m;i++)
    {
        scanf("%d %d %d",&x,&y,&t);
        x--;
        y--;
        adjacent[x][y]=t;
        adjacent[y][x]=t;
    }
    for(i=1,t=0;i<g;i++)
    {
        mygraph[graphpath[i-1]][graphpath[i]]=t;
        mygraph[graphpath[i]][graphpath[i-1]]=t;
        t=t+adjacent[graphpath[i-1]][graphpath[i]];
    }
    for(i=0;i<n;i++)
    {
        travel[i]=INF;
        Marked[i]=0;
    }
    travel[a]=k;
    for(i=0;i<n;i++)
    {
        check=-1;
        int j;
        for(j=0;j<n;j++)
        {
            if(Marked[j])
                continue;
            if(check==-1 || travel[j]<travel[check])
                check=j;
        }
        Marked[check]=1;
        for(j=0;j<n;j++)
        {
            if(travel[check] < mygraph[check][j])
                travel[j]=min(adjacent[check][j]+travel[check],travel[j]);
            else
                travel[j]=min(travel[j],max(mygraph[check][j]+adjacent[check][j],travel[check])+adjacent[check][j]);
        }
    }
    printf("%d\n",travel[b]-travel[a]);
    return 0;
}
