#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXALIAS 6
#define MAXALIASWORDS 10

struct anode *addtree(struct anode *, char *);
void treeprint(struct anode *);
int getword(char *, int);
char *alias(char *, const char *, int n);

struct anode {
	char *alias;
	char *wordlist[MAXALIASWORDS];
	int count;
	struct anode *left;
	struct anode *right;
}

int main(int argc, char *argv[])
{
	struct anode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			root = addtree(root, word);
		}
	}
	treeprint(root, word);
	return 0;
}

char *alias(char *alias, const char *word, int n)
{

	while (*word != '\0' && n--) {
		*alias++ = *word++;
	}
	*alias = '\0';
	return alias;
}

struct anode *addtree(struct anode *p, char *w)
{
	int cond;
	char alias[MAXALIAS];

	alias(alias, w, MAXALIAS);


	if (p == NULL) {
		p = talloc();
		p->alias = strdup(alias);
		p->wordlist[] = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(alias, p->alias)) == 0) {
		p->wordlist[] = strdup(w);
		p->count++;
	} else if (cond < 0) {
		p->left = addtree(p->left, w);
	} else {
		p->right = addtree(p->right, w);
	}
	return p;
}

int getword(char *word, int lim)
{
	int c, d, former, later;
	int getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
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
