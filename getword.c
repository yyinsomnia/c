#include <stdio.h>
#include <ctype.h>

int getword(char *word, int lim)
{
	int c, d, former, later;
	int getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c == EOF) {
		return c;
	} else {
		*w++ = c;
	}
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0; w++) {
			if (!isalnum(*w = getch())) {
				ungetch(*w);
				break;
			}
		}
	} else if (c == '\'' || c == '"') {
		former = c;
		while ((later = getch()) != EOF) {
			if (later == c && former != '\'')
				break;
			former = later;
		}
	} else if (c == '/') {
		if ((d = getch()) == '*') {
			while ((c = getch()) != EOF) {
				if (c == '*') {
					if ((c = getch()) == '/')
						break;
					else 
						ungetch(c);
				}
			}
		} else if (d == '/') {
			while ((c = getch()) != '\n') //TODO
				;
		} else {
			ungetch(d);
		}
	}
	*w = '\0';
	return word[0];
}