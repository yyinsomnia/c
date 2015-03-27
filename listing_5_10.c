#include <stdio.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void ungets(char []);
void push(double);
double pop(void);

int main(int argc, char *argv[])
{
	char s[MAXOP];
	double op2;
	while (--argc > 0) {
		ungets(" ");
		ungets(*++argv);
		switch (getop(s)) {
			case NUMBER:
				//why atoi is right but atof is zero?
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				op2 = pop();
				if (op2 == 0.0)
					printf("error: zero divisor\n");
				else 
					push(pop() / op2);
				break;
			default:
				printf("error: unknow command %s\n", s);
				argc = 1;
				break;
		}
	}
	printf("\t%.8g\n", pop());
	return 0;
}