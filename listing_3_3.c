# include <stdio.h>

void expand(char s1[], char s2[])
{
	char c;
	int i, j;
	while ((c = s1[i++]) != '\0') {
		if (s1[i] == '-' && s1[i+1] >= c) {
			i++;
			while (c < s1[i])
				s2[j++] = c++;
		} else {
			s2[j++] = c;
		}
	}

	s2[j] = '\0';
}

void expand_x(char s1[], char s2[])
{
	char c;
	int i, j;
	while ((c = s1[i++]) != '\0') {
		if (s1[i] == '-' && s1[i+1] >= c) {
			i++;
			while (c < s1[i])
				s2[j++] = c++;
			if (s1[i+1] == '-')
				s2[j++] = s1[i];
		} else {
			s2[j++] = c;
		}
	}

	s2[j] = '\0';
}

int main()
{
	char c[100] = "a-b-c-d";
	char s[100];
	expand_x(c, s);
	printf("%s\n", s); 
	return 0;
}