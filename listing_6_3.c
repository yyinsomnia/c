#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

int main(int argc, char *argv[])
{
	
	if (argc != 2) {
		printf("please enter the file name!\n");
		return -1;
	}
	char *filename;
	strcpy(filename, argv[2]);
	if (fp = fopen(filenam, "r") == NULL) {
		printf("file is not exist!\n");
		return -1;
	}
	int linenum = 1;
	while (getword(word, MAXWORD) != EOF) {
		if ((word[0] == '\n')) {
			linenum++;
		}
	}

	
}
