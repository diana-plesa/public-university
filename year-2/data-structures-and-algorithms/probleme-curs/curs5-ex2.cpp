#include <stdio.h>
#include <stdlib.h>

//Modificați algoritmul pentru sortarea prin inserție astfel încât sortarea să se facă de la
//sfârșitul tabloului spre început.Ordinea va rămâne tot crescătoare

void generate_array(long* arr, long n)
{
	for (long i = 0; i < n; i++)
	{
		arr[i] = n - i;
	}
}

void free_array(long* arr, long n)
{
	free(arr);
}

void print_array(long* arr, long n)
{
	for (long i = 0; i < n; i++)
	{
		printf("%ld ", arr[i]);
	}
	printf("\n");
}



void insert_sort(long* arr, long n) //sortarea modificata
{
	long i = 0, j = 0, to_insert = 0;

	for (i = n - 2; i >= 0; i--)
	{
		to_insert = arr[i];

		j = i;

		while (j < n - 1 && to_insert > arr[j + 1])
		{
			arr[j] = arr[j + 1];
			j++;
		}

		arr[j] = to_insert;
	}
	
}

int main()
{
	long n;

	printf("Type n: ");
	scanf_s("%ld", &n);

	long* arr = (long*)malloc(sizeof(long) * n);

	if (arr == NULL)
	{
		perror("Malloc error");
		exit(-1);
	}

	generate_array(arr, n);
	print_array(arr, n);

	insert_sort(arr, n);
	print_array(arr, n);

	free_array(arr, n);
    return 0;
}


