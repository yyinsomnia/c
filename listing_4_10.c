#include <ctype.h>

#define MAXLINE 100

int getline(char line[], int limit);
int li = 0;
char line[MAXLINE];

int getop(char s[])
{
	int i, c;

	if (line[li] == '\0') { //line end!
		if (getline(line, MAXLINE) == 0)
			return EOF;
		else
			li = 0;
	}

	while ((s[0] = c = line[li++]) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = line[li++]))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = line[li++]))
			;
	s[i] = '\0';
	li--;
	return NUMBER;
}