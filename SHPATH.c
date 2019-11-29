#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#define ll long long int
#define MAX 100005
 
typedef struct node
{
	struct node* next[26];
	int number;
}node;

node* newNode()
{
	node* temp = (node*)malloc(sizeof(node));
	for(int i=0;i<26;i++)
		temp->next[i] = NULL;
	temp->number = -1;
	return temp;
}

void checkiftrue(bool my_ans , bool true_ans)
{
	bool x = 0;
	if(my_ans == x || x == true_ans)
		my_ans = true_ans;
}

node* insert(node* root,char* str,int i)
{
	if(*str == '\0'){
		root->number = i;
		return root;
	}
	node* t = root->next[(int)(*str-'a')];
	if(t == NULL){
		t = newNode();
	}
	root->next[(int)(*str-'a')] = insert(t,str+1,i);
	return root;
}

struct Queue 
{ 
    int front, rear, size; 
    unsigned capacity; 
    int* array; 
}; 

struct Queue* createQueue(unsigned capacity) 
{ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1;
    queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
    return queue; 
}
int isFull(struct Queue* queue) 
{  return (queue->size == queue->capacity);  } 

int isEmpty(struct Queue* queue) 
{  return (queue->size == 0); } 

void enqueue(struct Queue* queue, int item) 
{ 
    if (isFull(queue)) 
        return; 
    queue->rear = (queue->rear + 1)%queue->capacity; 
    queue->array[queue->rear] = item; 
    queue->size = queue->size + 1; 
    printf("%d enqueued to queue\n", item); 
} 

int dequeue(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    int item = queue->array[queue->front]; 
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
} 
int front(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->array[queue->front]; 
} 

int rear(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->array[queue->rear]; 
}

int search(node* t,char* str)
{
	if(t == NULL)
		return -1;
	while(*str!='\0' && t->next[(int)(*str-'a')]){
		t = t->next[(int)(*str-'a')];
		str++;
	}
	if(*str == '\0')
		return t->number;
	return -1;
}
 
typedef struct heapNode
{
	int city_number;
	int distance;
}heap_Node;
 
heap_Node heap[MAX];
int heap_Count = 0;
 
int parent(int t){
	return (t-1)/2;
}

void heap_Insert(int city_num,int dist)
{
	heap_Node tt;
    tt.city_number = city_num;
	tt.distance = dist;
	int temp = heap_Count++;
	while(temp != 0 && tt.distance < heap[parent(temp)].distance){
  	    heap[temp] = heap[parent(temp)];
		temp = parent(temp);
	} 
	heap[temp] = tt; 
}
 
heap_Node get_Min()
{
 
	heap_Node temp = heap[0];
	heap_Node tt = heap[heap_Count--];
	int t = 0;
	
	while(t<heap_Count){
		int small = t;
		int r = 2*t+2,l = 2*t+1;
		if(l < heap_Count){
		    if(r < heap_Count)
			{
		        if(heap[l].distance < heap[r].distance)
				{
		            small = l;
		        }
				else
				{
		            small = r;
		        }
		    }
			else
			{
		        small = l;
		    }   
		}
		if(small != t && heap[small].distance < tt.distance)
		{
			heap[t] = heap[small];
			t = small;
		}
		else
		{
		    heap[t] = tt;
			break;
		}
	}
	return temp;
}
 
typedef struct edge
{
	struct edge* next;
	int neigh,dis;
}edge;
 
edge* make_Edge(int x,int y)
{
	edge* temp = (edge*) malloc(sizeof(edge));
	temp->next = NULL;
	temp->neigh = x;
	temp->dis = y;
	return temp;
}
 
 
edge* graph[MAX];
 
void add_Edge(int a,int b,int c)
{
	edge* temp = graph[a];
	graph[a] = make_Edge(b,c);
	graph[a]->next = temp;
}

typedef struct
{
	int top;
	int items[10]
}stack;

void push(stack *s, int val)
{
	s->items[++s->top]=val;
}

int empty(stack *s)
{
	if(s->top==-1)
		return 1;
	else
		return 0;
}

int pop(stack *s)
{
	if(!empty(s))
		return(s->items[s->top--]);
}

int Top(stack *s)
{
	return(s->items[s->top]);
}

int dijkstra(int source,int destination,int n)
{
	if(source == destination)
	return 0;
	int distance[n+1],visited[n+1];
	heap_Count = 0;
	for(int i = 0;i <= n; i++)
	{
		distance[i] = 200001;
		visited[i] = 0;
	}
 
	heap_Insert(source,0);
	distance[source] = 0;
	while(heap_Count>0){
	    heap_Node min_Val = get_Min();
		
		int current = min_Val.city_number;
		
		if(visited[current])continue;
        visited[current] = 1;
		
		if(current == destination)
			return distance[current];
		
		edge *temp_edge = graph[current];
		while(temp_edge!=NULL)
		{
			int d = temp_edge->dis;
			int c = temp_edge->neigh;
        
            if(distance[c]>(distance[current]+d) && !visited[c])
			{
                distance[c] = distance[current]+d;
                heap_Insert(c,d+distance[current]);
            }
            
			temp_edge = temp_edge->next;
		}
		visited[current] = 1;
	}
 	return distance[destination];
}
int main()
{
	int t ;
	scanf("%d",&t);
	checkiftrue(0,0);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		node* trie = newNode();
		for(int i =0;i<=n;i++)
			graph[i] = NULL;
	
		for(int i=1;i<=n;i++)
		{
			char city_name[15];
			scanf("%s",city_name);
			trie = insert(trie,city_name,i);
			int padosi;
			scanf("%d",&padosi);
			for(int j=0;j<padosi;j++)
			{
				int b,c;
				scanf("%d%d",&b,&c);
				add_Edge(i,b,c);
			}
		}
		int q;
		scanf("%d",&q);
		while(q--)
		{
			char city1[15],city2[15];
			scanf("%s %s",city1,city2);
			int n1 = search(trie,city1);
			int n2 = search(trie,city2);
			printf("%d\n",dijkstra(n1,n2,n));
		}
	}
	return 0;	
}