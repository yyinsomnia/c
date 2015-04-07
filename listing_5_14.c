#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right, int reverse, int (*comp)(void *, void *));
int numcmp(char *, char *);

int main(int argc, char *argv[])
{
	int (*cmp)(char *, char *);
	int nlines;
	int numeric = 0;
	int reverse = 0;
	int i = argc;
	while (--i) {
		if (strcmp(argv[i], "-n") == 0)
			numeric = 1;
		else if (strcmp(argv[i], "-r") == 0)
			reverse = 1;
		else
			;
	}
	if (numeric)
		cmp = numcmp;
	else
		cmp = strcmp;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort((void **) lineptr, 0, nlines - 1, reverse, (int (*)(void *, void *))cmp); //int strcmp(const char *str1, const char *str2), so need transform to void *
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input is too large to sort\n");
		return -1;
	}
}

void qsort(void *v[], int left, int right, int is_r,int (*comp)(void *, void *))
{
	int i, last, res;
	void swap(void *v[], int , int);
	if (left >= right)
		return ;
	last = left;
	for (i = left; i < right; i++) {
		res = (*comp)(v[i], v[right]);
		if (is_r)
			res = -res;
		if (res < 0)
			swap(v, i, last++);
	}
	swap(v, right, last);
	qsort(v, left, last - 1, is_r, comp);
	qsort(v, last + 1, right, is_r, comp);
}

void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int numcmp(char *s1, char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else 
		return 0;
}

int mstrcasecmp(char *s1, char *s2)
{
	for ( ; tolower(*s1) == tolower(*s2); s1++, s2++) {
		if (*s1 == '\0')
			return 0;
	}
	return tolower(*s1) - tolower(*s2);
}
