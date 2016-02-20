#include <stdio.h>
#include <ctype.h>
#define MAXLINECHARS 100
#define OCTLEN 6

int main()
{
	int c, pos;
	int inc(int pos, int n);

	pos= 0;
	while ((c = getchar()) != EOF) {
		if (iscntrl(c) || c == '') {
			pos = inc(pos, OCTLEN);
			printf(" \\%03o ", c);
			if (c == '\n') {
				pos = 0;
				putchar('\n');
			}
		} else {
			pos = inc(pos, 1);
			putchar(c); //the func inc return n is correct because of this line!
		}
	} 
	return 0;
}

int inc(int pos, int n)
{
	if (pos + n < MAXLINECHARS) {
		return pos + n;
	} else {
		putchar('\n');
		return n;
	}
}