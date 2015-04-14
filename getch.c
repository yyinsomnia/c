#include <string.h>
#include <stdio.h>
#define BUFSIZE 4096

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else 
		buf[bufp++] = c;
}

void ungets(char s[])
{
	int len = strlen(s);
	void ungetch(int);
	while (len > 0) {
		ungetch(s[--len]);
	}
}