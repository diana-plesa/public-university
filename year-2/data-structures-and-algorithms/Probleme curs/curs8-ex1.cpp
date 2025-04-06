//Să se implementeze o funcție de ștergere a unui nod cu o cheie dată dintr-o listă simplu înlănțuită. 
//Funcția trebuie să ia în considerare toate cazurile de ștergere

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