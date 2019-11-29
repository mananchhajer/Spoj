#include <stdio.h>
#include <stdlib.h>

#define ll long long int

struct stack
{
    ll top;
    ll items[100000];
};
void push(struct stack *s, ll val)
{
    s->items[++s->top]=val;
}
int empty(struct stack *s)
{
    if(s->top==-1)
        return 1;
    else
        return 0;
}
ll pop(struct stack *s)
{
    if(!empty(s))
        return(s->items[s->top--]);
}
ll Top(struct stack *s)
{
    return(s->items[s->top]);
}

int main()
{
    int t, c = 1;
    char ch;
    scanf("%d",&t);
    while (t--) 
    {
        printf("Case %d:\n",c);
        ll n, max = 0, ip;
        struct stack *mango=(struct stack*)malloc(sizeof(struct stack));
        mango->top=-1;
        scanf("%lld",&n);
        //printf("Case %d:\n",c);
        
        while (n--)
        {
            scanf(" %c",&ch);
            switch (ch)
            {
                case 'A':
                {
                    scanf("%lld",&ip);
                    if (ip > max)
                        max = ip;
                    push(mango,max);
                    break;
                } 
                case 'Q':
                {
                    if (empty(mango))
                    {
                        max=0;
                        printf("Empty\n");
                    }
                    else
                        printf("%lld\n",Top(mango));
                    break;
                }  
                case 'R':
                {
                    if (!empty(mango))
                    {
                        pop(mango);
                        if (!empty(mango))
                            {
                                if(Top(mango) < max)
                                    max = Top(mango);
                            }
                            else max = 0;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        c++;
    }
    return 0;
}