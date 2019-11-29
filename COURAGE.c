#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define ll long long int
#define MAX 100005
#define MAX2 (long)1000000000

ll getMid(ll s, ll e)
{
    return s + (e -s)/2;
}

ll minVal(ll x, ll y)
{
    return (x < y)? x: y;
}

ll RMQUtil(ll *st, ll ss, ll se, ll qs, ll qe, ll index) 
{ 
	if (qs <= ss && qe >= se) 
		return st[index]; 

	if (se < qs || ss > qe) 
		return INT_MAX; 

	ll mid = getMid(ss, se); 
	return minVal(RMQUtil(st, ss, mid, qs, qe, 2*index+1), 
				RMQUtil(st, mid+1, se, qs, qe, 2*index+2)); 
} 

ll RMQ(ll *st, ll n, ll qs, ll qe) 
{ 
	if (qs < 0 || qe > n-1 || qs > qe) 
	{ 
		printf("Invalid Input"); 
		return -1; 
	}

	return RMQUtil(st, 0, n-1, qs, qe, 0); 
} 

ll constructSTUtil1(ll arr[], ll ss, ll se, ll *st, ll si) 
{ 
	if (ss == se) 
	{ 
		st[si] = arr[ss]; 
		return arr[ss]; 
	} 

	ll mid = getMid(ss, se); 
	st[si] = minVal(constructSTUtil1(arr, ss, mid, st, si*2+1), 
					constructSTUtil1(arr, mid+1, se, st, si*2+2)); 
	return st[si]; 
} 

ll *constructST1(ll arr[], ll n) 
{
	ll x = (ll)(ceil(log2(n))); 

	ll max_size = 2*(ll)pow(2, x) - 1; 

	ll *st = (ll*)malloc(max_size * sizeof(ll*)); 

	constructSTUtil1(arr, 0, n-1, st, 0); 

	return st; 
}

ll getSumUtil(ll *st, ll ss, ll se, ll qs, ll qe, ll si) 
{ 
	if (qs <= ss && qe >= se) 
		return st[si]; 

	if (se < qs || ss > qe) 
		return 0; 

	ll mid = getMid(ss, se); 
	return getSumUtil(st, ss, mid, qs, qe, 2*si+1) + 
		getSumUtil(st, mid+1, se, qs, qe, 2*si+2); 
}

void updateValueUtil(ll *st, ll ss, ll se, ll i, ll diff, ll si) 
{ 
	if (i < ss || i > se) 
		return; 

	st[si] = st[si] + diff; 
	if (se != ss) 
	{ 
		ll mid = getMid(ss, se); 
		updateValueUtil(st, ss, mid, i, diff, 2*si + 1); 
		updateValueUtil(st, mid+1, se, i, diff, 2*si + 2); 
	} 
} 

void updateValue(ll arr[], ll *st, ll n, ll i, ll new_val) 
{ 
	if (i < 0 || i > n-1) 
	{ 
		printf("Invalid Input"); 
		return; 
	} 

	ll diff = new_val - arr[i]; 

	arr[i] = new_val; 

	updateValueUtil(st, 0, n-1, i, diff, 0); 
}

ll getSum(ll *st, ll n, ll qs, ll qe) 
{
	if (qs < 0 || qe > n-1 || qs > qe) 
	{ 
		printf("Invalid Input"); 
		return -1; 
	} 

	return getSumUtil(st, 0, n-1, qs, qe, 0); 
} 

ll constructSTUtil(ll arr[], ll ss, ll se, ll *st, ll si) 
{
	if (ss == se) 
	{ 
		st[si] = arr[ss]; 
		return arr[ss]; 
	} 

	ll mid = getMid(ss, se); 
	st[si] = constructSTUtil(arr, ss, mid, st, si*2+1) + 
			constructSTUtil(arr, mid+1, se, st, si*2+2); 
	return st[si]; 
} 

ll *constructST(ll arr[], ll n) 
{
	ll x = (ll)(ceil(log2(n))); 

	ll max_size = 2*(ll)pow(2, x) - 1; 

	ll *st =(ll*)malloc(max_size * sizeof(ll*));

	constructSTUtil(arr, 0, n-1, st, 0); 

	return st; 
}

ll Minimum(ll a, ll b)
{
    return a<b?a:b ;  
}

int main() 
{ 
	ll arr[MAX];
	ll n ;
    scanf("%lld",&n);
    ll i;
    for(i=0; i<n; ++i)
    {
        scanf("%lld",&arr[i]);
    }

	ll *st = constructST(arr, n);
    ll *st1 = constructST1(arr, n);
    ll p;
    scanf("%lld",&p);

    while(p--)
    {
        char arr1[8];
        ll x,y,res,min;
        scanf("%s %lld %lld", arr1 , &x , &y);
        res = 0;
        min = MAX2;
        char q = arr1[0];
        switch (q)
        {
            case 'C':
                {
                    res = getSum(st, n, x, y);
                    
                    printf("Res before : %lld \n",res);
                    // ll j = 0;
                    // for(j=x;j<=y;++j)
                    // {
                    //     min = Minimum(arr[j],min);
                    // }
                    min = RMQ(st1, n, x, y);
                    res = res - min;
                    printf("min = %lld \n", min);
                    printf("%lld \n",res);
                    break;
                }
            case 'G':
            {
                ll add = arr[y] + x;
                arr[y] = add;
	            updateValue(arr, st, n, y, add); 
                printf("NEW = %lld \n", arr[y]);
                break;
            }
            case 'E':
            {
                ll deduct = arr[y] - x;
                updateValue(arr, st, n, y, deduct); 
                break;
            }
            default:
                break;
        }
    }
	return 0; 
} 