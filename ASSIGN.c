#include <stdio.h>
#include <stdlib.h>
#define ll long long int
int manan=0;
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
typedef struct
{
	int top;
	int items[10]
}stack;
void push(stack *s, int val)
{
	++manan;
	s->items[++s->top]=val;
}
int empty(stack *s)
{
	++manan;
	if(s->top==-1)
	{
		++manan;
		return 1;
	}
	else
	{
		++manan;
		return 0;
	}
}
int pop(stack *s)
{
	++manan;
	if(!empty(s))
	{
		++manan;
		return(s->items[s->top--]);
	}
}
int Top(stack *s)
{
	++manan;
	return(s->items[s->top]);
}
typedef struct
{
	int items[10];
	int front,rear;
}queue;
int isempty(queue* q)
{
	++manan;
	if(q->rear+ q->front +1 ==0)
	{
		++manan;
		return 1;
	}
	else
	{
		++manan;
		return 0;
	}
}
int enqueue(queue* q,int value)
{
	++manan;
	if(q->rear<9)
	{
		++manan;
        q->items[++q->rear]=value;
	}
    else
	{
		++manan;
	    printf("overflow\n");
	}
}
int dequeue(queue* q)
{
	++manan;
	if(!isempty(q))
	{
		++manan;
		return q->items[q->front++];
	}
	else
	{
		++manan;
		printf("Empty");
	}
}
int main()
{
	++manan;
	int T,i,j,N;
	++manan;
	int likes[20][20];
	++manan;
	long long dp[1<<20];
	++manan;
	scanf("%d",&T);
	++manan;
	while (T--)
	{
		++manan;
		scanf("%d",&N);
		++manan;
		for (i=0; i<N; i++)
		{
			++manan;
			for (j=0; j<N; j++)
			{
				++manan;
				scanf("%d",likes[i]+j);
				++manan;
			}
			++manan;
		}
		++manan;
		dp[0]=1;
		++manan;
		for (i=1; i<(1<<N); i++)
		{
			++manan;
			dp[i]=0;
			++manan;
			int pop=0;
			++manan;
			for (j=0; j<N; j++)
			{
				++manan;
				if (i&(1<<j))
				{
					++manan;
					pop++;
					++manan;
				}
				++manan;
			}
			for (j=0; j<N; j++)
			{
				++manan;
				if (i&(1<<j)&&likes[pop-1][j])
				{
					++manan;
					dp[i]+=dp[i-(1<<j)];
					++manan;
				}
				++manan;
			}
			++manan;
		}
		++manan;
		printf("%lld\n",dp[(1<<N)-1]);
		++manan;
	}
	++manan;
	return 0;
}