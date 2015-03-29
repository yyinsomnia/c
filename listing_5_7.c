#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 //进行排序的最大文本行数
char *lineptr[MAXLINES];  //指向问本行的指针数组

int readlines(char *lineptr[], char *linestor, int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main()
{
	int nlines; //读取的输入行数目
	char *linestor;
	if ((nlines = readlines(lineptr, linestor, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000
#define MAXSTOR 8000

int getline_my(char *, int);
//Both getline() and getdelim() were originally GNU extensions. They were standardized in POSIX.1-2008.
//char *alloc(int);
//mac hasn't the alloc with llvm
int readlines(char *lineptr[], char *linestor,int maxlines)
{
	int len, nlines;
	char line[MAXLEN];
	char *p = linestor;
	char *linestop = linestor + MAXSTOR;
	nlines = 0;
	while ((len = getline_my(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || p + len > linestop) {
			return -1;
		} else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);
	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int getline_my(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
