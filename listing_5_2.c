#include <ctype.h>
#include <stdio.h>
#include <math.h>
//程序中用到 math.c，使用 gcc 编译，需要加上 -lm 选项。
//-l表示使用库，m为数学库。
#define SIZE 10

int getch(void);
void ungetch(int);

float getfloat(float *pn)
{
	int c, c_before, sign, f_num;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c_before = c;
		if (!isdigit(c = getch())) {
			if (c != EOF)
				ungetch(c);
			ungetch(c_before);
			return c_before; //not 0 because 0 => !isdigital(c) && c != EOF && c != '+' && c != '-'
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	f_num = 0;
	if (c == '.') {
		c_before = c;
		if (!isdigit(c = getch())) {
			if (c != EOF)
				ungetch(c);
			ungetch(c_before);
			return c_before;
		}
		for ( ; isdigit(c); c = getch()) {
			*pn = 10 * *pn + (c - '0');
			f_num += 1;
		}
		*pn /= pow(10, f_num);
	}
	if (c != EOF)
		ungetch(c);
	return c;
}

int main()
{
	int i,n;
	float array[SIZE], getfloat(float *);
	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
		;
	for (i = 0; i < n; i++)
		printf("%f \n", array[i]);
}