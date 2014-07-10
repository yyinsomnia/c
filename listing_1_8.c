#include <stdio.h>

int main()
{
	int c, sn, tn, nn;
	sn = tn = nn = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++sn;
		else if (c == '\t')
			++tn;
		else if (c == '\n')
			++nn;
	}
	printf(" %d\t%d\t%d", tn, sn, nn);
	printf("\n");
	return 0;
}
