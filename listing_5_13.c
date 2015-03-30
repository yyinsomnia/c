#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define FILE_MAX_LINE 10000
#define DAFAULT_N 10
#define NUMBER '0'

int getop(char []);

int main(int argc, char *argv[])
{
	int n;
	char s[9];
	ungets(" ");
	ungets(argv[2]);
	char op;
	op = getop(s);
	if (argc != 4 || strcmp(argv[1], "-n") || op != NUMBER) {
		n = DAFAULT_N;
	} else {
		n = atoi(s);
	}

	FILE *fp;
	fp = fopen(argv[3], "r");
	if (fp == NULL) {
		printf("file is not exist!\n");
		return 0;
	}

	int start_line_number;
	char *str_lines[FILE_MAX_LINE];
	char buffer[1024];
	int line = 0;
	while (!feof(fp)) {
		fgets(buffer, 1024, fp);
		str_lines[++line] = (char*)malloc(strlen(buffer)+1); //Segmentation fault (core dumped)?this is the problem key
		strcpy(str_lines[line], buffer);

	}
	fclose(fp);


	start_line_number = line - n + 1;
	int now_line_number = start_line_number;
	while (now_line_number++ <= line) {
		printf("%d: %s\n", now_line_number, str_lines[now_line_number]);
	}

	return 0;
}