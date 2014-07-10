#include <stdio.h>


void escape(char s[], char t[])
{
	int i = 0;
	int j = 0;
	char c;
	while (( c = t[j++]) != '\0') {
		switch (c) {
			case '\n':
				s[i++] = '\\';
				s[i++] = 'n';
				break;
			case '\t':
				s[i++] = '\\';
				s[i++] = 't';
				break;
			default:
				s[i++] = c;
		}
	}

	s[i] = '\0';
}

void unescape(char s[], char t[])
{
	int i = 0;
	int j = 0;
	char c;
	while (( c = t[j++]) != '\0') {
		if (c == '\\') {
			c = t[j++];
			switch (c) {
				case 'n':
					s[i++] = '\n';
					break;
				case 't':
					s[i++] = '\t';
					break;
				case '\0':
					s[i++] = '\0';
					return;
				default:
					s[i++] = c;
			}
		} else {
			s[i++] = c;
		}
	}
	s[i] = '\0';
}

int main()
{
	char s[100];
	char z[100];
	char t[] = "hello	world";
	escape(s, t);
	printf("%s\n", s);
	unescape(z, s);
	printf("%s\n", z);
	return 0;
}