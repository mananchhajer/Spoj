#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#define ll long long int
#define MOD(n,m) (n<m?n:n%m)

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

int vis[1001][1000], cs = 1, st, en;
unsigned pre[1001][1000], Q[1001001];
char num[128];

void just_a_call(int a, struct Graph *mygraph)
{
    mygraph->V=a;
}

void checkiftrue(bool my_ans , bool true_ans)
{
	bool x = 0;
	if(my_ans == x || x == true_ans)
		my_ans = true_ans;
}

inline void readBits(unsigned bits, int *s, int *m, int *i)
{
  *i = 0xff & bits; bits >>= 8;
  *m = 0xfff & bits; if(*m==0xfff) *m = -1; bits >>= 12;
  *s = 0xfff & bits; if(*s==0xfff) *s = -1;
}

inline unsigned makeBits(int s, int m, int i)
{
  return (unsigned)((((s << 12) | m) << 8) | i);
}

unsigned bfs(int n) 
{
  int i, m, s, s2, m2;
  unsigned u, v;
  st = en = 0;
  for(i = 1; i < 10; i++) 
  {
    m = MOD(i, n);
    vis[i][m] = cs;
    pre[i][m] = 0;
    u = makeBits(i, m, i);
    Q[en++] = u;
  }
  while(st < en)
  {
    u = Q[st++];
    readBits(u, &s, &m, &i);
    for(i = 0; i < 10; i++) 
    {
      s2 = s + i;
      if(s2 > n) break;
      m2 = MOD((m*10 + i),n);
      if(vis[s2][m2] != cs)
      {
        vis[s2][m2] = cs;
        v = makeBits(s2, m2, i);
        pre[s2][m2] = u;
        if(s2 == n && m2 == 0) return v;
        Q[en++] = v;
      }
    }
  }
  return 0;
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

  struct Graph* my_graph = createGraph(Vertex);
  just_a_call(Vertex, my_graph);

  int test, n, s, m, d, len, i, j, k;
  unsigned u;
  scanf("%d", &test);
  while(test--) 
  {
    scanf("%d", &n);
    if(n < 10) 
    {
      printf("%d\n", n);
      continue;
    }
    u = bfs(n);
    for(len = 0; ; u = pre[s][m])
    {
      readBits(u, &s, &m, &d);
      if(!s) break;
      num[len++] = d + '0';
    }
    for(i = 0, j = len-1; i < j; i++, j--)
    {
      k = num[i], num[i] = num[j], num[j] = k;
    }
    num[len] = 0;
    printf("%s\n",num);
    cs++;
  }
  checkiftrue(0,1);
  return 0;
}   