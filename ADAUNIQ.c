#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
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

typedef long long ll;
#define max_n 200050
int block=3430;
struct Query
{
    int ind,l,r,t;
};

struct Upd {
    int ind,curr,undo;
};
int cmp(const void  *a, const void * b)
{
    int l1=((struct Query *) a)->l;
    int l2=((struct Query *) b)->l;
    int r1=((struct Query *) a)->r;
    int r2=((struct Query *) b)->r;
    int t1=((struct Query *) a)->t;
    int t2=((struct Query *) b)->t;
    int i1=((struct Query *) a)->ind;
    int i2=((struct Query *) b)->ind;
      if (l1/block != l2/block)
        return l1/block - l2/block;
      else if(r1/block!=r2/block)
      return r1/block-r2/block;
      else if(t1!=t2)
    return t1-t2;
else
    return i1-i2;
}
typedef struct{
	int top;
	int items[10]
}stack;
void push(stack *s, int val){
	s->items[++s->top]=val;
}
int empty(stack *s){
	if(s->top==-1)
		return 1;
	else
		return 0;
}
int pop(stack *s){
	if(!empty(s))
		return(s->items[s->top--]);
}
int Top(stack *s){
	return(s->items[s->top]);
}
int main()
{
	stack *s=(stack*)malloc(sizeof(stack));
	push(s,1);
	push(s,2);

    int n;
    scanf("%d",&n);
        int q;
    scanf("%d",&q);
    int a[n],ans[q];
    struct Upd upd[q];
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    struct Query query[q];
    int x,y,tmp;
    int ucnt=0,qcnt=0;
    for(int i=0;i<q;i++)
    {
        scanf("%d",&tmp);
        if(tmp==1)
        {
            scanf("%d%d",&x,&y);
            upd[ucnt].ind=x;
            upd[ucnt].curr=a[x];
            upd[ucnt].undo=y;
            ucnt++;
            a[x]=y;
        }
        else
        {
         scanf("%d%d",&x,&y);
         query[qcnt].l=x;
         query[qcnt].r=y;
         query[qcnt].t=ucnt;
         query[qcnt].ind=qcnt;
         qcnt++;
        }
    }
    block=pow(n,2.0/3);
    qsort(query,qcnt,sizeof(struct Query),cmp);
    int curl=0,curr=n-1,curt=ucnt;
    int diff=0;
      int freq[max_n]={};
    for(int i=0;i<n;i++)
    {
        freq[a[i]]++;
        if(freq[a[i]]==1)
            diff++;
        else
            if(freq[a[i]]==2)
                diff--;
    }

    for(int i=0;i<qcnt;i++)
    {
        int L=query[i].l;
        int R=query[i].r;
        int T=query[i].t;
      for(int i=curt+1;i<=T;i++)
        {
           
            int idx=upd[i-1].ind;
            int novo=upd[i-1].undo;
            if(curl <= idx && idx <= curr)
            {
                freq[a[idx]]--;
                if(freq[a[idx]]==0)
                    diff--;
                else if(freq[a[idx]]==1)
                    diff++;

                a[idx] = novo;
                freq[a[idx]]++;
                if(freq[a[idx]]==2)
                    diff--;
                else if(freq[a[idx]]==1)
                    diff++;
            }
            else{
            a[idx] = novo;
            }
        }
        for(int i=curt;i>T;i--)
        {
            int idx=upd[i-1].ind;
            int novo=upd[i-1].curr;
            if(curl <= idx && idx <= curr)
            {
                freq[a[idx]]--;
                if(freq[a[idx]]==0)
                    diff--;
                else if(freq[a[idx]]==1)
                    diff++;

                a[idx] = novo;
                freq[a[idx]]++;
                if(freq[a[idx]]==2)
                    diff--;
                else if(freq[a[idx]]==1)
                    diff++;
            }
            else{
            a[idx] = novo;
            }

        }
        curt=T;
     
        for(int i=curr+1;i<=R;i++)
         {
           
             freq[a[i]]++;
             if(freq[a[i]]==1)
             diff++;
             else if(freq[a[i]]==2)
             diff--;
         }
        for(int i=curl-1;i>=L;i--)
        {
            freq[a[i]]++;
            if(freq[a[i]]==1)
                diff++;
            else if(freq[a[i]]==2)
                diff--;
           
         }
          for(int i=curr;i>R;i--)
         {
             freq[a[i]]--;
             if(freq[a[i]]==0)
             diff--;
             else if(freq[a[i]]==1)
             diff++;
           
         }
         for(int i=curl;i<L;i++)
        {
            freq[a[i]]--;
            if(freq[a[i]]==0)
            diff--;
            else if(freq[a[i]]==1)
            diff++;
           
        }
         ans[query[i].ind]=diff;
         curr=R;curl=L;
    }
    for(int i=0;i<qcnt;i++)
    printf("%d\n",ans[i]);
}