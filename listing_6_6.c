#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

struct nlist {
	struct nlist *prev;
	struct nlist *next;
	char *name;
	char *defn;
};

unsigned simple_hash(char *, int);

struct nlist *lookup(char *s)
{
	struct nlist *np;

	//question: for == do while or while, make a test
	for (np = hashtab[simple_hash(s, HASHSIZE)]; np->next != NULL; np = np->next) {
		if (strcmp(np->name, s) == 0) {
			return np;
		}
	}
	return NULL;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		//if c has exception handle, the conditional branch can cancel. but I like it, it's so simple..
		if (np == NULL || (np->name = strdup(name)) == NULL) {
			return NULL;
		}
		hashval = simple_hash(name, HASHSIZE);
		np->prev = NULL;
		np->next = hashtab[hashval]; //why,please think.
		if (hashtab[hashval] != NULL) {
			hashtab[hashval]->prev = np;
		}
		hashtab[hashval] = np;
	} else {
		free((void *) np->defn);
	}
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

int undef(char *name)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		return 0;
	} else {
		np->prev->next = np->next;
		free((void *) np->name);
		free((void *) np->defn);
		free((void *) np); //is the free recursion? or we need to free np->name,np->defn first?how can it distinguish between *next and *name
	}
	return 1;
}

int main()
{
	struct nlist *np;
	char word[MAXWORD];
	char c;
	char name[MAXWORD];
	char defn[MAXWORD];
	int name_ready, defn_ready;

	while ((c = getch()) != EOF) {
		if (c == '#') {
			ungetch(c);
			getword(word, MAXWORD);
			if (strcmp(word, "#define") == 0) {
				printf("%s", word);
				name_ready = 0;
				defn_ready = 0;
				while ((c = getch())) {
					if (isspace(c)) {
						printf("%c", c);
					} else {
						ungetch(c);
						if (!name_ready) {
							getword(name, MAXWORD);
							printf("%s", name);
						} else if (!defn_ready) {
							getword(defn, MAXWORD);
							printf("%s", defn);
							install(name, defn);
							break;
						}
					}
				}	
			} else {
				printf("%s", word);
			}
		} else if(isalpha(c) || c == '_') {
			ungetch(c);
			getword(word);
			if ((np = lookup(word)) != NULL) { 
				printf("%s", np->defn);
			} else {
				printf("%s", word);
			}
		} else {
			printf("%c", c);
		}
	}

}