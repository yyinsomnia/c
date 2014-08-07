#include <ctype.h>
#include <stdio.h>

#define SIZE 10

int getch(void);
void ungetch(int);

int getint(int *pn)
{
	int c, c_before, sign;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c_before = c;
		c = getch();
		if (!isdigit(c)) {
			if (c != EOF)
				ungetch(c);
			ungetch(c_before);
			return c_before; //not 0 because 0 => !isdigital(c) && c != EOF && c != '+' && c != '-'
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main()
{
	int i,n, array[SIZE], getint(int *);
	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
		;
	for (i = 0; i < n; i++)
		printf("%d \n", array[i]);
}