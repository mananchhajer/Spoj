#include <stdio.h>
#include <stdlib.h>

#define limit 10010
#define c char

int readL ( c * strng ) 
{
	int i;
	c ch;
	for( i=0 ;(ch=getchar()) != '\n' ; )
	{
		strng[i++] = ch;
	}
	strng[i] = '\0';
	return i;
}

struct root
{
	int a;
	int b;
};

struct root arr[limit];
int lis[limit];

int comp ( const void * a , const void * b ) 
{
	struct root * x = (struct root *) a;
	struct root * y = (struct root *) b;

	if ( x->a == y->a ) 
	{
		return x->b - y->b;
	}
	return x->a - y->a;
}

int main () 
{
	int t , z , i , j , k;
	scanf("%d" , &t);
	for ( z = 1 ; z <= t ; z++ )
	{
		int n;
		scanf("%d" , &n);
		k=0;
		while( k < n) 
		{
			scanf("%d" , &arr[k].a);
			++k;
		}
		k=0;
		while( k < n )
		{
			scanf("%d" , &arr[k].b);
			++k;
		}

		qsort( arr , n , sizeof(struct root) , comp);

		i=0;
		while( i < n ) 
		{
			lis[i] = 1;
			++i;
		}

		i=1;
		do
		{
			j = 0 ;
			while( j < i ) 
			{
				if ( arr[i].b >= arr[j].b && lis[i] < lis[j]+1 )
					lis[i] = lis[j] + 1;
				j++; 
			}
			++i;
		}while(i<n);

		int max = lis[0];
		i=1;
		while ( i < n )
		{
			if ( lis[i] > max )
				max = lis[i];
			++i;
		}

		printf("%d\n" , max);
	}
	return 0;
}