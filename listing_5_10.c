#include <stdio.h>

#define MAX 10



int main(int argc, char *argv[])
{
	double a;
	char s[MAX];
	while (--argc > 0) {
		s = *++argv;
		printf("%s", s, (argc > 1) ? " " : "");
	}

	return 0;
}