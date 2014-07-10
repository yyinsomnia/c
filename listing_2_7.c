#include <stdlib.h>
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

unsigned int invert(unsigned int x, int p, int n)
{
	unsigned int high, mid, low, length, mid_r;
	char s1[64];
	char s2[32];
	length = log2(x) + 1;
	high   = getbits(x, length - 1, length - 1 - p);
	mid    = getbits(x, p, n);
	low    = getbits(x, p - n, p + 1 - n);
	mid_r  = ~mid & ~(~0 << n);
	return (high << (p + 1)) + (mid_r << (p + 1 -n)) + low;
}

/**
 * 1+8+32+64 = 105
 * 1101001 4 3  
 * 1110101
 * 1+4+16+32+64 = 117
 */
int main()
{
	unsigned int r;
	r = invert(105, 4, 3);
	printf("%u", r);
}