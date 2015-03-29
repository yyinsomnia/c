#include <stdio.h>

void squeeze(char s1[], char s2[])
{
	int i,j,k,flag;
	for (i = j = 0; s1[i] != '\0'; i++) {
		flag = 0;
		for (k = 0; s2[k] != '\0'; k++) {
			if (s1[i] == s2[k]) {
				flag = 1;
				break;
			}
		}
		if (!flag)
			s1[j++] = s[i];
	}
	s1[j] = '\0';
}


