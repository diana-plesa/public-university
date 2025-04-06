
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list
{
	char name[20];
	int age;
	float grade;
	list* next;
}node;

node* create_node(const char* new_name, int new_age, float new_grade)
{
	node* new_node = (node*)malloc(sizeof(node));

	if (new_node == NULL)
	{
		printf("Error malloc new node\n");
		exit(-1);
	}

	strcpy_s(new_node->name, new_name);
	new_node->age = new_age;
	new_node->grade = new_grade;
	new_node->next = NULL;

	return new_node;

}

node* add_node(node* start, const char* new_name, int new_age, float new_grade)
{
	if (start == NULL)
	{
		start = create_node(new_name, new_age, new_grade);
		return start;
	}

	node* cursor = start;

	if (strcmp(start->name, new_name) > 0)
	{
		node* new_node = create_node(new_name, new_age, new_grade);
		new_node->next = start;
		return new_node;
	}

	while (cursor->next != NULL && strcmp(cursor->next->name, new_name) < 0)
	{
		cursor = cursor->next;
	}

	node* new_node = create_node(new_name, new_age, new_grade);
	new_node->next = cursor->next;
	cursor->next = new_node;

	return start;
}

node* init(node* start)
{
	if (start == NULL)
		return start;

	node* cursor = NULL;

	while (start != NULL)
	{
		cursor = start;
		start = start->next;
		free(cursor);
	}
	return start;
}

void print_list(node* start)
{
	if (start == NULL)
	{
		printf("Empty list\n");
		return;
	}

	node* cursor = NULL;

	for (cursor = start; cursor != NULL; cursor = cursor->next)
	{
		printf("%s ", cursor->name);
	}
	printf("\n");
}

node* remove(node* start, const char* new_name)
{
	if (start == NULL)
	{
		return NULL;
	}


	node* cursor = start->next;
	node* prev_cursor = start;
	node* aux = NULL;

	if (strcmp(start->name, new_name) == 0)
	{
		aux = start;
		start = start->next;
		free(aux);
		return start;


	}

	while (cursor != NULL)
	{
		if (strcmp(cursor->name, new_name) == 0)
		{
			prev_cursor->next = cursor->next;
			free(cursor);
			return start;
		}
		prev_cursor = cursor;
		cursor = cursor->next;
	}

	return start;
}


int main()
{
	node* start = NULL;
	start = init(start);
	start = add_node(start, "Diana", 20, 9.70);
	start = add_node(start, "Andreea", 19, 10);
	print_list(start);
	start = remove(start, "Diana");
	start = add_node(start, "Matei", 20, 7);
	start = add_node(start, "Diana", 20, 9.70);
	print_list(start);
	start = init(start);
}

