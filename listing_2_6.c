#include <stdio.h>
#include <limits.h>

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	unsigned max, top;
	max = UINT_MAX;
	top = max - ~(~0 << (p+1));
	//printf("%u", top);
	return (x & (~(~(~0 << n) << (p+1-n)) | top)) | ((y & ~(~0 << n)) << (p+1-n)); //为什么有 |top 和没有 |top结果一样？
}

int main()
{
	int r;
	r = setbits(90, 4, 4, 20);
	printf("%d", r);
}