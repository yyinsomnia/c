#include <stdio.h>

int main()
{
	int c,b;
	b = -2; //wheb b eq -2 means that b is not be used.
	while ((c = getchar()) != EOF) {
		if (b == -2)
			putchar(c);
		else {
			if (b == c && c == ' ')
				;
			else
				putchar(c);
		}
		b = c;
	}
	return 0;
}
