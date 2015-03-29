#include <ctype.h>

double atof(char s[])
{
	double val, power;
	int i, j, sign, e, sign_e;

	for (i=0; isspace(s[i]); i++)
		;
	sign = s[i] == '-' ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i]-'0');
		power *= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E')
		i++;
	sign_e = s[i] == '-' ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (e = 0; isdigit(s[i]); i++) {
		e = 10 * e + (s[i] - '0');
	}
	for (j = 1; j<= e; j++) {
		if (sign_e == 1)
			power /= 10.0;
		else
			power *= 10.0;
	}

	return sign * val / power;

}