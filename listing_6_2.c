#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXALIAS 6
#define MAXALIASWORDS 10

struct anode *addtree(struct anode *, char *);
void treeprint(struct anode *);
int getword(char *, int);
char *alias_hash(char *, const char *, int n);
struct anode *talloc(void);
char *strdupp(char *); //there is also strdupa() (in the GNU C library

/**
 * the same work will be showed n time , let it go..
 */
struct anode {
	char *alias;
	char *wordlist[MAXALIASWORDS];
	int wordcount;
	int count;
	struct anode *left;
	struct anode *right;
};

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
	printf("\n------------------\n");
	treeprint(root);
	return 0;
}

char *alias_hash(char *alias, const char *word, int n)
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

	alias_hash(alias, w, MAXALIAS);


	if (p == NULL) {
		p = talloc();
		p->alias = strdupp(alias);
		p->wordlist[0] = strdupp(w);
		p->wordcount = 1;
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(alias, p->alias)) == 0) {
		p->wordlist[p->wordcount++] = strdupp(w);
		p->count++;
	} else if (cond < 0) {
		p->left = addtree(p->left, w);
	} else {
		p->right = addtree(p->right, w);
	}
	return p;
}

void treeprint(struct anode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		int wordcount = p->wordcount;
		printf("%s: ", p->alias);
		while (wordcount--) {
			printf("%s ", p->wordlist[wordcount]);
		}
		printf("\n");
		treeprint(p->right);
	}

}

/**
 * it's ok, the work is start with a-zA-Z_ ,the number is filtered
 */
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

struct anode *talloc(void)
{
	return (struct anode *) malloc(sizeof(struct anode));
}

char *strdupp(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}