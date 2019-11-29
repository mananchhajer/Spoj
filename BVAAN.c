#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200
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
		return 1;
     
	else
		return 0;
}
int pop(stack *s)
{
    ++manan;
	if(!empty(s))
		return(s->items[s->top--]);
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
		return 1;
	else
		return 0;
}
int enqueue(queue* q,int value)
{
    ++manan;
	if(q->rear<9)
        q->items[++q->rear]=value;
     
    else
	    printf("overflow\n");
}
int dequeue(queue* q)
{
    ++manan;
	if(!isempty(q))
		return q->items[q->front++];
    else
		printf("Empty");
}
int result[MAX][MAX][MAX];
int max(int a, int b)
{
    ++manan; 
    return a>b?a:b;
}
int solve(char *a,char *b,int i,int j, int K)
{
    ++manan;
    int score1=-1;
    ++manan;
    if(K==0)
    {
        ++manan;
        return 0;
    }
    ++manan;
    if(i==-1 || j==-1)
    {
        ++manan;
        return -1;
    }
     
    if(result[i][j][K]!=-2)
    {
        ++manan;
	    return result[i][j][K];
    }
    ++manan;
    if(a[i]==b[j])
    {
        ++manan;
        score1=solve(a,b,i-1,j-1,K-1);
        ++manan;
        score1=score1==-1?-1:(score1+a[i]);
    }
    ++manan;
    int score2=-1;
    ++manan;
    int score3=-1;
    ++manan;
    score2 =solve(a,b,i-1,j,K);
    ++manan;
    score3 =solve(a,b,i,j-1,K);
    ++manan;

    result[i][j][K]=max(score1,max(score2,score3));
      ++manan;
    return result[i][j][K];
}
int main()
{
      ++manan;
    int T=1;
      ++manan;
    int K;
      ++manan;
    scanf("%d",&T);
      ++manan;
    char a[MAX],b[MAX];
      ++manan;
    for(int i =0;i<T;i++)
    {
          ++manan;
        scanf("%s",&a);
          ++manan;
        scanf("%s",&b);
          ++manan;
        scanf("%d",&K);
          ++manan;
		for(int x=0;x<102;x++)
        {
              ++manan;
			for(int y=0;y<102;y++)
            {
                  ++manan;
				for(int z=0;z<102;z++)
                {
                      ++manan;
					result[x][y][z]=-2;
                      ++manan;
                }
                  ++manan;
            }
              ++manan;
        }
          ++manan;
        int res=solve(a,b,strlen(a)-1,strlen(b)-1,K);
          ++manan;
        res=res==-1?0:res;
          ++manan;
        printf("%d\n",res);
          ++manan;
    }
      ++manan;
    return 0;
}