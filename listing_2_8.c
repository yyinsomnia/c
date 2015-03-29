#include <stdio.h>
#include <math.h>

unsigned int getbits(unsigned int x, int p, int n)
{
	return x >> (p+1-n) & ~(~0 << n);
}

unsigned int getbitslen(unsigned int x)
{
	return log2(x) + 1;
}

unsigned rightonerot(x)
{
	unsigned int one, length;
	one = getbits(x, 0, 1);
	length = getbitslen(x);
	return (x >> 1) + (one << length);
}
/**
 * 1010110 = 2+4+16+64 = 86
 * 1010101 = 1+4+16+64 = 85
 */
unsigned rightrot(x, n)
{
	int i;
	for (i = 0; i < n; i++) {
		x = rightonerot(x);
	}
	return x;
}

int main()
{
	unsigned int r;
	r = rightrot(86, 2);
	printf("%u", r);
}