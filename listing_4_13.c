
void reverse(char s[])
{
	reverse(s, 0, strlen(s));
}

void reverse(char s[], int i, int length)
{
	int c, j;
	j = length - (i + 1);
	if (i < j) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		reverse(s, ++i, length);
	}
}