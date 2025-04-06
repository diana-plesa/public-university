#include <stdio.h>

// Rescrieți funcția factorial astfel încât să nu fie recursivă

long fact(int n)
{
	long val = 1;

	for (int i = 1; i <= n; i++)
	{
		val = val * i;
	}

	return val;
}

int main()
{
	printf("%ld", fact(9));
}
