#include <stdio.h>
#include <stdbool.h>

#define MAX 100

void init(int *count)
{
	*count = 0;
}

bool belongs(int *set, int val, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (val == set[i])
			return true;
	}

	return false;
}

void add_element(int *set, int val, int* count)
{
	set[*count] = val;
	(*count)++;
}

void add_item(int *set, int* count)
{
	int val = 0;

	printf("Type value of new item: ");
	scanf("%d", &val);

	if (belongs(set, val, *count))
		return;
	else
		add_element(set, val, count);
}

void print_set(int *set, int count)
{
	if (count == 0)
	{
		printf("Set is empty\n");
		return;
	}

	for (int i = 0; i < count; i++)
	{
		printf("%d ", set[i]);
	}
	printf("\n");
}

void delete_element(int* set, int val, int* count)
{
	if (*count == 0)
	{
		printf("Set is empty\n");
		return;
	}

	int i = 0;

	while (i < *count)
	{
		if (set[i] == val)
		{
			(*count)--;
			while (i < *count)
			{
				set[i] = set[i + 1];
				i++;
			}
			return;
		}
		i++;
	}

	printf("Given item does not exist in set\n");
}

void delete_item(int* set, int* count)
{
	if (*count == 0)
	{
		printf("Can't delete from empty list\n");
		return;
	}

	int val = 0;
	printf("Type value of item you want to delete: ");
	scanf("%d", &val);

	delete_element(set, val, count);
}

int* copy_set(int *set1, int *count1, int *set2, int count2)
{
	for (int i = 0; i < count2; i++)
	{
		if (!belongs(set1, set2[i], *count1))
		{
			add_element(set1, set2[i], count1);
		}
	}

	return set1;
}

void reunion(int count1, int count2, int* re_count, int *set1, int *set2, int* re_set)
{
	re_set = copy_set(re_set, re_count, set1, count1);
	re_set = copy_set(re_set, re_count, set2, count2);
}

void intersection(int count1, int count2, int* inters_count, int* set1, int* set2, int* inters_set)
{
	if (count1 == 0 || count2 == 0)
	{
		init(inters_count);
		return;
	}

	for (int i = 0; i < count1; i++)
	{
		for (int j = 0; j < count2; j++)
		{
			if (set1[i] == set2[j])
			{
				add_element(inters_set, set2[j], inters_count);
			}
		}
	}
}

int main()
{
	int set1[MAX], set2[MAX], re_set[2 * MAX], inters_set[MAX];
	int count1 = 0, count2 = 0, re_count = 0, inters_count = 0;

	//init(&count1);
	//add_item(set1, &count1);
	//add_item(set1, &count1);
	//add_item(set1, &count1);
	//print_set(set1, count1);

	delete_item(set1, &count1);
	print_set(set1, count1);

	add_item(set2, &count2);
	add_item(set2, &count2);
	add_item(set2, &count2);
	add_item(set2, &count2);
	print_set(set2, count2);

	init(&count2);

	//delete_item(set2, &count2);
	print_set(set2, count2);

	//reunion(count1, count2, &re_count, set1, set2, re_set);
	//print_set(re_set, re_count);

	//intersection(count1, count2, &inters_count, set1, set2, inters_set);
	//print_set(inters_set, inters_count);

	return 0;
}
