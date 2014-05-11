#include <stdio.h>


int htoi(char s[])
{
	int i,v;
	v = 0;
	for (i=0; s[i] != '\0'; i++) {
		if (s[i] == '0' && (s[i+1] == 'X' || s[i+1] =='x'))
			continue;
		if (s[i] == 'x' || s[i] == 'X')
			continue;
		if (s[i] >= '0' && s[i] <= '9')
			v = 16*v + (s[i] - '0');
		else if (s[i] >= 'A' && s[i] <= 'F')
			v = 16*v + (s[i] - 'A');
		else if (s[i] >= 'a' && s[i] <= 'f')
			v = 16*v + (s[i] - 'a');
		else 
			return -1;
	}
	return v;	
}

int main()
{
	char s[] = "0X22";	
	int v;
	v = htoi(s);
	printf("%d\n", v);
	return 0;
}
