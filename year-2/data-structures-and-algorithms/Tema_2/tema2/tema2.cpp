#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000001

void generate_array(long* arr, long n)
{
	for (long i = 0; i < n; i++)
	{
		arr[i] = n - i;
	}
}

void print_array(long* arr, long n)
{
	for (long i = 0; i < n; i++)
	{
		printf("%ld ", arr[i]);
	}
	printf("\n");
}

void insert_sort(long* arr, long n)
{
	long i = 0, j = 0, to_insert = 0;
	
	for (i = 1; i < n; i++)
	{
		if (arr[i - 1] > arr[i])
		{
			to_insert = arr[i];

			j = i;
	
			while (j > 0 && to_insert < arr[j - 1])
			{
				arr[j] = arr[j - 1];
				j--;
			}

			arr[j] = to_insert;
		}
	}
}

void free_array(long* arr, long n)
{
	free(arr);
}

void swap(long* e1, long* e2)
{
	if (*e1 > *e2)
	{
		long aux = *e1;
		*e1 = *e2;
		*e2 = aux;
	}

}

int get_min_index(long pos, long* arr, long n)
{
	long min = MAX, min_index = 0;
	for (long i = pos; i < n; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			min_index = i;
		}
	}
	
	return min_index;
}

void select_sort(long* arr, long n)
{
	int min_index = 0;
	for (int i = 0; i < n - 1; i++)
	{
		min_index = get_min_index(i + 1, arr, n);
		swap(&arr[i], &arr[min_index]);
	}
}

void bubble_sort(long* arr, long n)
{
	bool sorted = true;
	do
	{
		sorted = true;
		for (int i = 0; i < n - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(&arr[i], &arr[i + 1]);
				sorted = false;
			}
		}
	} while (sorted == false);
}

void shaker_sort(long* arr, long n)
{
	bool swapped = true;
	long end = n - 1, start = 0;

	while (swapped)
	{
		for (int i = start; i < end; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(&arr[i], &arr[i + 1]);
				swapped = true;
			}
		}

		if (!swapped)
			break;

		swapped = false;
		end--;

		for (int i = end; i >= start; i--)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(&arr[i], &arr[i + 1]);
				swapped = true;
			}
		}

		start++;
	}
}


int main()
{
	long n = 0;
	clock_t start, end;

	printf("Type n: ");
	scanf("%ld", &n);

	long* arr = (long*)malloc(sizeof(long) * n);

	if (arr == NULL)
	{
		perror("Malloc error");
		exit(-1);
	}

	generate_array(arr, n);
	//print_array(arr, n);

	start = clock();
	insert_sort(arr, n);
	end = clock();
	printf("Time taken insert: %.3f\n", (double)(end - start) / CLOCKS_PER_SEC);

	generate_array(arr, n);
	start = clock();
	select_sort(arr, n);
	end = clock();
	printf("Time taken select: %.3f\n", (double)(end - start) / CLOCKS_PER_SEC);

	generate_array(arr, n);
	start = clock();
	bubble_sort(arr, n);
	end = clock();
	printf("Time taken bubble: %.3f\n", (double)(end - start) / CLOCKS_PER_SEC);

	generate_array(arr, n);
	//print_array(arr, n);
	start = clock();
	shaker_sort(arr, n);
	end = clock();
	//print_array(arr, n);
	printf("Time taken shaker: %.3f\n", (double)(end - start) / CLOCKS_PER_SEC);


	free_array(arr, n);
	return 0;
}
