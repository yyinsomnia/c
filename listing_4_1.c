#include <string.h>

int strrindex(char s[], char t[])
{
	int i, j, k;
	for (i = strlen(s)-1; i >= 0; i--) {
		for (k = strlen(t)-1,j = i; t[k] == s[j]; j--,k-- )
			;
		if (k == 0)
			return i-strlen(t)+1;
	}
}