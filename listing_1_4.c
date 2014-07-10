#include <stdio.h>

int main()
{
	float fahr, celsius;
	int lower, upper, step;

	lower = -20;
	upper = 100;
	step = 10;

	celsius = lower;
	printf("C to F table\n");
	while (celsius <= upper) {
		fahr = celsius*(9.0/5.0) + 32.0;
		printf("%6.1f %3.0f\n", celsius, fahr);
		celsius = celsius+step;
	}
}

