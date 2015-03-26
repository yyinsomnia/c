#include <stdlib.h>
#include <stdio.h>

void allocateArray(int *arr, int size, int value) 
{
	int i;
	arr = (int*) malloc(size * sizeof(int));
	if (arr != NULL) {
		for (i = 0; i < size; i++) {
			arr[i] = value;
		}
	}
}

int main()
{
	int *vector = NULL;
	allocateArray(vector, 5, 45);
	printf("%p\n", vector);
	return 0;
}