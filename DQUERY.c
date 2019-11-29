#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

typedef struct {
	int items[10];
	int front,rear;
}queue;
int isempty(queue* q){
	if(q->rear+ q->front +1 ==0){
		return 1;
	}
	else{
		return 0;
	}
}
int enqueue(queue* q,int value){
	if(q->rear<9){
	q->items[++q->rear]=value;
}
else{
	printf("overflow\n");
}
}
int dequeue(queue* q){
	if(!isempty(q)){
		return q->items[q->front++];
	}
	else{
		printf("Empty");
	}
}
struct event {
	struct QueryEvent *qe;
	struct NumberEvent *ne;
	int type;
};

struct QueryEvent {
	int i, j, ans;
};

struct NumberEvent {
	int num, ind;
};

struct node {
	int l, r, v;
};

int reg[1000001];

struct node *root;

int cmpFun(const void *a, const void *b){
	struct event *f = (struct event *)a;
	struct event *s = (struct event *)b;
	int r = 0;
	if(f->type==1){
		if(s->type==1){
			r = f->ne->ind - s->ne->ind;
		}else{
			r = f->ne->ind - s->qe->j;
			if(r==0)r=-1;
		}
	}else if(f->type==2){ 
		if(s->type==1){ 
			r = f->qe->j - s->ne->ind;
			if(r==0)r = 1;
		}else{ 
			r = f->qe->j - s->qe->j; 
		}
	} 
	return r;
}

int insert(int start, int end, int index, int pos){
	if(start==end){
		root[index].l = 0;
		root[index].r = 0;
		root[index].v = 1;
		return 1;
	}

	int mid = (start+end)/2;

	if(pos <= mid){
		int l = insert(start, mid, index*2+1, pos); 
		root[index].l = l;
	}else{
		int r = insert(mid+1, end, index*2+2, pos);
		root[index].r = r;
	}

	return root[index].v = root[index].l + root[index].r;
}

int removee(int start, int end, int del, int index){
	int pos = del;
	if(start==end){
		root[index].l = 0;
		root[index].r = 0;
		root[index].v = 0;
		return 0;
	}

	int mid = (start+end)/2;

	if(pos <= mid){
		int l = removee(start, mid, del, index*2+1); 
		root[index].l = l;
	}else{
		int r = removee(mid+1, end, del, index*2+2);
		root[index].r = r;
	}

	return root[index].v = root[index].l + root[index].r;
}

int query(int start, int end, int qi, int qj, int index){ 
	if(start>=qi && end <= qj){
		return root[index].v;
	}

	if(qj<start || qi>end){
		return 0;
	}

	int mid = (start+end)/2;
	return query(start, mid, qi, qj, index*2+1)
		+  query(mid+1, end, qi, qj, index*2+2);
}

int main()
{
	memset(reg, -1, 1000001*sizeof(int));
	int n, q;
	struct event *events;
	scanf("%d", &n);

	root = (struct node*)malloc(sizeof(struct node)*(2*pow(2, ceil(log((double)n)/log((double)2)))));

	events = (struct event *)malloc(sizeof(struct event)*(n+200000));
	int ind=0;
	for(int i=0;i<n;++i){
		struct event *e = events+ind++;
		struct NumberEvent *ne = (struct NumberEvent *)malloc(sizeof(struct NumberEvent));
		scanf("%d", &ne->num);
		ne->ind = i;
		e->ne = ne;
		e->type = 1;
	}

	scanf("%d", &q);
	struct QueryEvent **original_Queries = (struct QueryEvent **)malloc(q*sizeof(struct QueryEvent*));

	for(int i=0;i<q;++i){
		struct event *q = events+ind++;
		struct QueryEvent *e = (struct QueryEvent *)malloc(sizeof(struct QueryEvent));
		int a, b;
		scanf("%d%d", &a, &b);
		q->type = 2;
		e->i = a-1;
		e->j = b-1;
		q->qe = e;
		original_Queries[i] = e;
	}

	qsort(events, ind, sizeof(struct event), cmpFun);

	for(int i=0;i<ind;++i){
		struct event *e = events+i; 
		if(e->type==1){
			if(reg[e->ne->num]==-1){
				insert(0, n-1, 0, e->ne->ind);
				reg[e->ne->num] = e->ne->ind;
			}else{
				int del = reg[e->ne->num];
				removee(0, n-1, del, 0);
				reg[e->ne->num] = e->ne->ind;
				insert(0, n-1, 0, e->ne->ind);
			}
		}else{
			int i = e->qe->i;
			int j = e->qe->j;
			int ans = query(0, n-1, i, j, 0);
			e->qe->ans = ans;
		}
	}

	for(int i=0;i<q;++i){
		printf("%d\n", original_Queries[i]->ans);
	}
	return 0;
}