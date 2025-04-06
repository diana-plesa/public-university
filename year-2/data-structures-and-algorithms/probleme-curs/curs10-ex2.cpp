#include <stdio.h>

//Fie un tablou de întregi cu valori unice A[0…n-1]. Să se verifice dacă există un index i astfel 
//încât A[i] = i, folosind un algoritm de tip divide et impera care are o complexitate O(log n).

int find_index(int a[], int left, int right)
{
	if (left > right)
	{
		return 0;
	}

	int middle = left + (right - left) / 2;

	if (a[middle] == middle) return 1;
	int ret = find_index(a, left, middle - 1);
	if (ret == 0)
		ret = find_index(a, middle + 1, right);

	return ret;
}

int main()
{
	int a[10] = { 6,22,3,4,5,5,7,8,9,8 };

	printf("%d", find_index(a, 0, 9));

	return 0;
}