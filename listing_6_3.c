#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

struct nlist {
	struct nlist *next;
	char *name;
	int lines[100]; //it's illegal, I use the sizeof(struct nlist)...use the pointer or ..int lines[200]?
	int linecount;
};

struct nlist *talloc();
char *strdupp(char *);

int main(int argc, char *argv[])
{
	char word[MAXWORD];

	if (argc != 2) {
		printf("please enter the file name!\n");
		return -1;
	}
	char *filename;
	strcpy(filename, argv[2]);
	FILE * fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("file is not exist!\n");
		return -1;
	}
	int linenow = 1;
	struct nlist *node;
	struct nlist *node_parent;
	while (getword(word, MAXWORD) != EOF) {
		if ((word[0] == '\n')) {
			linenow++;
		}

		int hash_key = simple_hash(word, HASHSIZE);
		node = hashtab[hash_key];
		int is_node_exist = 0;
		while (node != NULL) {
			if (strcmp(node->name, word) == 0) {
				is_node_exist = 1;
				node->lines[node->linecount++] = linenow;
				break;
			}
			node_parent = node;
			node = node->next;
		}
		if (!is_node_exist) {
			node = talloc();
			node->next = NULL;
			node->name = strdupp(word);
			node->linecount = 0;
			node->lines[node->linecount++] = linenow;
			//the implement is dirty, how can I keep the consistency?
			if (hashtab[hash_key] == NULL) {
				hashtab[hash_key] = node;
			} else {
				node_parent->next = node;
			}
		}
	}
	int i;
	for (i = 0; i < HASHSIZE; i++) {
		node = hashtab[i];
		while (node != NULL) {
			printf("%s:", node->name);
			int count = node->linecount;
			while (count--) {
				printf(" %d", node->lines[count]);
			}
		}
	}
	return 0;
}

struct nlist *talloc()
{
	return (struct nlist *) malloc(sizeof(struct nlist));
}

char *strdupp(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}
