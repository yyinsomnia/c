#define abs(x)    ((x) < 0 ? -(x) : (x))

void itob(int n, char s[], int b)
{
	int i, sign, c;
	void reverse(char s[]);
	i = 0;
	do {
		c = abs(n % b);
		s[i++] = (c <= 9) ? (c + '0') : (c - 10 + 'a');
	} while (( n /= b ) != 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}