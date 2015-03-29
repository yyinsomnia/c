#include <stdio.h>

int bitcount(unsigned x)
{
	int i ;
	i = 0;
	while (x&=(x-1)) {
		i+=1;
	}
	return i+1;
}

int main()
{
	int a;
	a = bitcount(85);
	printf("%d", a);
}