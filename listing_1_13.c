#include <stdio.h>
#define IN 1
#define OUT 0
#define W_MAX_LEN 20
int main()
{
	int c, i,state, length, wnum[W_MAX_LEN];
	for (i = 1; i <= W_MAX_LEN; i++)
		wnum[i] = 0;
	state = OUT;
	length = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n')
			state = OUT;
		else if (state == OUT)
			state = IN;
		if (state == IN)
			++length;
		else {
			++wnum[length];
			length = 0;
		}
	}
	for (i = 1; i <= W_MAX_LEN; ++i)
		printf(" %2d : %d \n", i, wnum[i]);	

}
	
	
