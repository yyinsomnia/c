#include <stdio.h>

int main()
{
	char s[100];
	int i = 0;
	while((s[i++] = getchar()) != EOF)
		;
	s[i] = '\0';
	printf("--------\n%s\n", s); //why there is a '?' at the end?
	return 0;
}