#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
				//because i lose the stdlib.h
				//but how can it run without the .h?
				/**
				 * http://stackoverflow.com/questions/4800102/not-including-stdlib-h-does-not-produce-any-compiler-error
				 * For historical reasons -- specifically, compatibility with very old C programs (pre-C89) -- using a function without having declared it first only provokes a warning from GCC, not an error. But the return type of such a function is assumed to be int, not double, which is why the program executes incorrectly.
				 * If you use -Wall on the command line, you get a diagnostic:
				 * $ gcc -Wall test.c
				 * test.c: In function ‘main’:
				 * test.c:5: warning: implicit declaration of function ‘atoi’
				 * test.c:6: warning: implicit declaration of function ‘atof’
				 * You should use -Wall basically always. Other very useful warning options for new code are -Wextra, -Wstrict-prototypes, -Wmissing-prototypes, -pedantic, and -Wwrite-strings, but compared to -Wall they have much higher false positive rates.
				 * Tangentially: never use atoi nor atof, they hide input errors. Use strtol and strtod instead.
				 */
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