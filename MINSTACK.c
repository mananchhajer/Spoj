#include<stdio.h>
#include<stdlib.h>
#define MAX 1000000000

typedef struct Stack{
	long long int top;
	long long int min;
	long long int items[MAX];
}stack;

void Min(stack *s)
{ 
    if (empty(s)) 
        printf("EMPTY\n"); 
    else
        printf("%lld\n",s->min);
}

int empty(stack* s)
{
	if(s->top==-1)
		return 1;
	else
		return 0;
}

void push(stack* s, int x)
{
	if (empty(s))
	{
		s->min = x;
		s->items[++s->top] = x;
		return;
	}

	if (x < s->min)
	{
		s->items[++s->top]=(2 * x) - s->min;
		s->min = x;
	}

	else
		s->items[++s->top]=x;
}

void pop(stack* s)
{ 
    if (empty(s)) 
    { 
        printf("EMPTY\n");
        return; 
    }
    long long int t;
    t = s->items[s->top]; 
    s->top--;
    if (t < s->min) 
    {
        s->min = ( 2* s->min ) - t;
	}
	
}


int main()
{
	stack *s=(stack*)(malloc(sizeof(stack)));
	s->top=-1;
	int t,i;
	long long int j;
	scanf("%d",&t);
	char str[4];
	for(i=0;i<t;++i)
	{
		scanf("%s",str);
		if(str[2]=='S')
		{
			scanf("%lld",&j);
			push(s,j);
		}
		if(str[2]=='P')
		{
			pop(s);
		}
		if(str[2]=='N')
		{
			Min(s);
		}

	}

	return 0;
}