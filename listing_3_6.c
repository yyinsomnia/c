#define abs(x)	((x) < 0 ? -(x) : (x))

void itoa(int n, char s[], int w)
{
	int i, sign;
	void reverse(char s[]);

	sign = n;
	i = 0;
	do {
		s[i++] = abs(n % 10) + '0'; //注意数组s的元素类型是char而abs(n % 10) 是int
	} while ((n / 10) != 0);

	if (sign < 0)
		s[i++] = '-';
	while (i < w) {
		s[i++] = ' ';
	}
	s[i] = '\0';
	reverse(s);
}