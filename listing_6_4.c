#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct tnode *addtree(struct tnode *, char *);
void treeprint_sort(struct tnode *);
int getword(char *, int);

struct tnode *talloc(void);
char *strdupp(char *);

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};


int main()
{

	struct tnode *root;
	struct tnode *root_sort;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]))
			root = addtree(root, word);
	}
	treeprint_sort(root_sort, root);
	return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdupp(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->count++;
	} else if (cond < 0) {
		p->left = addtree(p->left, w);
	} else {
		p->right = addtree(p->right, w);
	}
	return p;
}

struct tnode *addtree_sort(struct tnode *p, struct tnode *s)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = s->word;
		p->count = s->count;
		p->left = p->right = NULL;
	} else if (s->count < p->count) { //<= or < Dijistra zhihu!
		p->left = addtree_sort(p->left, s);
	} else {
		p->right = addtree_sort(p->right, s);
	}
	return p;
}


struct tnode *sorttree(struct tnode *p, struct tnode *s)
{
	if (p != NULL) {
		sorttree(p, s->left);
		addtree_sort(p, s);
		sorttree(p, s->right);
	}
}

void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdupp(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL) {
		strcpy(p, s);
	}
	return p;
}

