#include <stdio.h> 
#include <stdlib.h>

int main() 
{ 
    int n,a;
    scanf("%d",&n);
	int* arr;
	arr = (int*)malloc(n * sizeof(int)); 
	for(a=0;a<n;++a)
	    scanf("%d",&arr[a]);
	int j, max; 
	int k ;
  	scanf("%d",&k);
	for (int i = 0; i <= n - k; i++)
	{ 
		max = arr[i]; 
	    for (j = 1; j < k; j++)
	    { 
			if (arr[i + j] > max) 
				max = arr[i + j]; 
		} 
		printf("%d ", max); 
	}
	return 0; 
}