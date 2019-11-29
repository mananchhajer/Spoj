#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#define MAX 1000005
#define _INFINITY 1073741824

struct node
{
    long long int value;
    long long int priority;
    long long int subtree_value;
    long long int subtreeSize;
    bool reversed;
    struct node* leftChild;
    struct node* rightChild;
    struct node* parent;
    long long int state;
};

typedef struct node tree;

long long int getValue(tree *t)
{
    return t? t->subtree_value : _INFINITY;
}
long long int getSize(tree *t)
{
    return t? t->subtreeSize : 0;
}
long long int Min(long long int a, long long int b)
{
    return a<b ? a : b;
}
void update(tree *t)
{
    if(t)
    {
        t->subtree_value = Min(getValue(t->leftChild), 
                    Min(t->value, getValue(t->rightChild)));
        t->subtreeSize = getSize(t->leftChild) + 1 + getSize(t->rightChild);
        if(t->leftChild)
        {
            t->leftChild->parent = t;
            t->leftChild->state = 0;
        }
        if(t->rightChild)
        {
            t->rightChild->parent = t;
            t->rightChild->state = 0;
        }
    }
}
void swap(tree *t1, tree *t2)
{
    tree *temp;
    temp = t1;
    t1 = t2;
    t2 = temp;
    free(temp);
}
void push(tree *t)
{
    if(t && t->reversed)
    {
        update(t);
        t->reversed=0;
        swap(t->leftChild, t->rightChild);
        if(t->leftChild)
        {
            t->leftChild->reversed ^= 1;
            t->leftChild->state ^= 1;
        }
        if(t->rightChild)
        {
            t->rightChild->reversed ^= 1;
            t->rightChild->state ^= 1;
        }
    }
}
long long int add = 0;
void Split(tree *t, tree* l, tree* r, long long int pos, long long int add)
{
    if(!t)
    {
        l = NULL;
        r = NULL;
        return ;
    }
    push(t);
    long long int cur_pos = getSize(t->leftChild) + add;
    if(cur_pos + 1 <= pos)
    {
        Split(t->leftChild, t->rightChild, r, pos, cur_pos+1);
        l = t;
    }
    else
    {
        Split(t->leftChild, l, t->rightChild, pos, add);
        r = t;
    }
    update(t);
}
void Merge(tree *t, tree *l, tree *r)
{
    push(l);
    push(r);
    if(!l || !r)
        t = l? l : r;
    else if (l->priority > r->priority)
    {
        Merge(l->rightChild, l->rightChild, r);
        t = l;
    }
    else
    {
        Merge(r->leftChild, l, r->leftChild);
        t = r;
    }
    update(t);
}
tree* Initialize(long long int key)
{
    tree* p = (tree*)malloc(sizeof(tree*));
    p->value = key;
    p-> priority = rand();
    p->subtree_value = key;
    p->subtreeSize = 1;
    p->reversed = 0;
    p->leftChild = NULL;
    p->rightChild = NULL;
    p->parent = NULL;
    p->state = 0;
    return p;
}
void Insert(tree *t, tree *item, long long int position)
{
    tree *l1,*r1;
    Split(t, l1, r1, position - 1, add);
    Merge(l1, r1, item);
    Merge(t, l1, r1);
}
void InsertI(tree *t, long long int position, long long int key)
{
    tree *p = Initialize(key);
    Insert(t, p, position);
}
void Erase(tree *t, long long int position)
{
    tree *l1, *r1;
    Split(t, l1, r1, position-1, add);
    tree *l2, *r2;
}
void Reverse(tree *t, long long int l, long long int r)
{
    tree *l1, *r1;
    Split(t, l1, r1, l - 1, add);
    tree *l2, *r2;
    Split(r1, l2, r2, r - l + 1, add);
    l2->reversed ^= 1;
    Merge(r1, l2, r2);
    Merge(t, l1, r1);
}
long long int Query(tree *t, long long int l, long long int r){
    tree *l1, *r1;
    Split(t, l1, r1, l - 1, add);
    tree *l2, *r2;
    Split(r1, l2, r2, r - l + 1, add);
    long long int ans = getValue(l2);
    Merge(r1, l2, r2);
    Merge(t, l1, r1);
    return ans;
}
bool Find(tree *t, long long int key)
{
    push(t);
    if(!t)
        return false;
    if(t->value == key)
        return true;
    if(t->value > key)
        return Find(t->leftChild, key);
    return Find(t->rightChild, key);
}
long long int Get_index(tree *t, long long int key, long long int add)
{
    push(t);
    if(t->value == key && getValue(t->leftChild) > key)
        return getSize(t->leftChild) + add + 1;
    else if(getValue(t->leftChild) <= key)
        return Get_index(t->leftChild, key, add);
    return Get_index(t->rightChild, key, add + getSize(t->leftChild) + 1);
}
long long int Kth_element(tree *t, long long int k)
{
    push(t);
    if(getSize(t->leftChild) + 1 == k)
        return t->value;
    if(getSize(t->leftChild) + 1 > k)
        return Kth_element(t->leftChild, k);
    return Kth_element(t->rightChild, k - getSize(t->leftChild) - 1);
}
void fixPath(tree *t)
{
    if (!t) return;
    fixPath(t->parent);
    push(t);
}
long long int calculatePosition(tree *t, long long int lastState)
{
    long long int skipped = 0;
    if (lastState == 1) skipped = 1 + getSize(t->leftChild);
    if (t->parent == NULL) return skipped;
    else return skipped + calculatePosition(t->parent, t->state);
}
long long int positionOfElement(tree *t)
{
    fixPath(t);
    return calculatePosition(t, +1);
}
void assignParents(tree *t)
{
    if (!t) return;
    if (t->leftChild) {
        t->leftChild->parent = t;
        t->leftChild->state = 0;
    }
    if (t->rightChild) {
        t->rightChild->parent = t;
        t->rightChild->state = 1;
    }
    assignParents(t->leftChild);
    assignParents(t->rightChild);
}
void Print(tree *t)
{
    if(!t)
        return;
    push(t);
    Print(t->leftChild);
    printf("%lld ", t->value);
    Print(t->rightChild);
}

long long int N, Q;
long long int type, x, l, r;
tree *t = NULL;
tree *nodes[MAX];

int main()
{
    scanf("%lld %lld",&N, &Q);
    long long int i;
    for(i = 1; i <= N; ++i)
    {
        nodes[i] = Initialize(i);
        Insert(t, nodes[i], i);
    }
    assignParents(t);
    while(Q--)
    {
        scanf("%lld", &type);
        switch(type)
        {
            case 1 :
            {
                scanf("%lld %lld", &l, &r);
                Reverse(t, l, r);
                break;
            }
            case 2 :
            {
                scanf("%lld", &x);
                printf("%lld\n", Kth_element(t, x));
                break;
            }
            case 3 :
            {
                scanf("%lld", &x);
                printf("%lld\n", positionOfElement(nodes[x]));
                break;
            }
        }
    }
    return 0;
}