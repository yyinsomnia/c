#include <stdio.h>

int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n-1;
	mid = (low+high) / 2;
	while (low <= high && x != v[mid]) {
		if (x < v[mid])
			high = mid - 1;
		else 
			low = mid + 1;
		mid = (low + high) / 2;
	}

	if (x == v[mid])
		return mid;
	else
		return -1;

}

int main()
{
	int n = 7;
	int v[7] = {1,2,3,4,5,6,7};
	int x = 4;
	int bin;
	bin = binsearch(x, v, n);
	printf("%d\n", bin);
	return 0;
}
