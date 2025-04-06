#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct set
{
	int info;
	struct set* next;
}elem;

void free_set(elem* start)
{
	elem *cursor = start, *cursor_next = NULL;

	while (cursor != NULL)
	{
		cursor_next = cursor->next;
		free(cursor);
		cursor = cursor_next;
	}

	return;
}

elem* init(elem* start)
{
	free_set(start);
	return NULL;
}

elem* add_elem(elem* start, int val)
{
	elem* cursor = NULL;

	if (start != NULL)
	{
		cursor = start;
		while (cursor != NULL)
		{
			if (val == cursor->info)
			{
				return start;
			}
			cursor = cursor->next;
		}
	}

	elem* new_elem = malloc(sizeof(elem));

	if (new_elem == NULL)
	{
		perror("Malloc error");
		exit(-1);
	}

	new_elem->info = val;
	new_elem->next = NULL;

	if (start == NULL)
	{
		start = new_elem;
	}
	else
	{
		cursor = start;
		while (cursor->next != NULL)
		{
			cursor = cursor->next;
		}

		cursor->next = new_elem;
	}
		
	return start;
	
}

elem* create_item(elem* start)
{
	int val = 0;
	printf("Type value of new element: ");
	scanf("%d", &val);

	return add_elem(start, val);
}

elem* delete_item(elem* start)
{
	if (start == NULL)
	{
		printf("Can't delete element from empty list\n");
		return start;
	}

	int val = 0;
	printf("Type value of element you want to delete: ");
	scanf("%d", &val);
	elem *aux = NULL;

	if (start->info == val)
	{
		aux = start -> next;
		free(start);
		start = aux;
		return start;
	}

	elem *cursor = start -> next, *prev = start;

	while (cursor != NULL)
	{
		if (cursor->info == val)
		{
			prev->next = cursor->next;
			free(cursor);
			
			return start;
		}
		cursor = cursor->next;
		prev = prev->next;
	}
	
	printf("Given value does not exist in set\n");
	return start;

}

void print_set(elem* start)
{
	if (start == NULL)
	{
		printf("Set is empty\n");
		return;
	}

	elem* cursor = start;

	while (cursor != NULL)
	{
		printf("%d ", cursor->info);
		cursor = cursor->next;
	}
	printf("\n");

	return;
}

elem* reunion(elem* start1, elem* start2, elem* reunion_start)
{
	elem* cursor = NULL;
	if (start1 == NULL)
	{
		reunion_start = NULL;
	}
	else
	{
		cursor = start1;

		while (cursor != NULL)
		{
			reunion_start = add_elem(reunion_start, cursor->info);
			cursor = cursor->next;
		}
	
	}

	if (start2 == NULL && start1 == NULL)
	{
		reunion_start = NULL;
	}
	else
	{
		cursor = start2;

		while (cursor != NULL)
		{
			reunion_start = add_elem(reunion_start, cursor->info);
			cursor = cursor->next;
		}
	
	}

	return reunion_start;

}

elem* intersection(elem* start1, elem* start2, elem* inters_start)
{
	elem *cursor1 = start1, *cursor2 = start2;

	if (start1 == NULL || start2 == NULL)
	{
		return NULL;
	}


	for (cursor1 = start1; cursor1 != NULL; cursor1 = cursor1->next)
	{
		for (cursor2 = start2; cursor2 != NULL; cursor2 = cursor2->next)
		{
			if (cursor1 -> info == cursor2 -> info)
				inters_start = add_elem(inters_start, cursor1->info);
		}
	}

	return inters_start;

}

bool belongs(elem* start, int val)
{
	elem* cursor = start;

	while (cursor != NULL)
	{
		if (cursor->info == val)
			return true;
		cursor = cursor->next;
	}

	return false;
}


int main()
{
	elem *start1 = NULL, *start2 = NULL;
	elem* reunion_start = NULL, *inters_start = NULL;
	bool val_in_set = 0;


	start1 = init(start1);
	start2 = init(start2);

	//start1 = create_item(start1);
	//start1 = create_item(start1);
	//start1 = create_item(start1);
	//print_set(start1);

	//start2 = create_item(start2);
	//start2 = create_item(start2);
	start2 = create_item(start2);
	start2 = create_item(start2);
	print_set(start2);

	//val_in_set = belongs(start1, 2);
	//printf("%d\n", val_in_set);
	//val_in_set = belongs(start2, 123);
	//printf("%d\n", val_in_set);
	//val_in_set = belongs(inters_start, 5);
	//printf("%d\n", val_in_set);

	//reunion_start = reunion(start1, start2, reunion_start);
	//print_set(reunion_start);
	//reunion_start = delete_item(reunion_start);
	//print_set(reunion_start);

	//inters_start = intersection(start1, start2, inters_start);
	//print_set(inters_start);
	//inters_start = delete_item(inters_start);
	//print_set(inters_start);

	//start1 = init(start1);
	//print_set(start1);

	reunion_start = reunion(start1, start2, reunion_start);
	print_set(reunion_start);
	free_set(start1);
	free_set(start2);
	//free_set(reunion_start);
	//free_set(inters_start);


	return 0;
}