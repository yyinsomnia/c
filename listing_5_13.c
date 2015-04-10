#include <stdio.h>
#include <string.h>
#define DAFAULT_N 10
#define NUMBER '0'

int getop(char []);

int main(int argc, char *argv[])
{
	int n;
	char s[9];
	ungets(" ");
	ungets(argv[2]);
	if (argc != 4 || !strcmp(argv[1], "-n") || getop(s) != NUMBER) {
		n = NUMBER;
	} else {
		n = atoi(s);
	}

	char *filename;
	strcpy(filename, argv[3]);
	FILE * fp;
	if (fp = fopen(filename, "r") == NULL) {
		printf("file is not exist!\n");
		return -1;
	}

	int start_line_number;
	char *str_lines[];

	int line = 0;
	while (!feof(fp)) {
		fgets(str_lines[++line], 1024, fp);
	}
	fclose(fp);
	start_line_number = line - n + 1;
	int now_line_number = start_line_number;
	while (now_line_number++ <= line) {
		printf("%d: %s\n", now_line_number, str_lines[now_line_number]);
	}

	return 0;
}