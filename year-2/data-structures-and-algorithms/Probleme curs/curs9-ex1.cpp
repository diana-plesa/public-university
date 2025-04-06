#include <stdio.h>

// Scrieți o funcție recursivă care numără nodurile dintr-o listă simplu înlănțuită


int count_nodes(node* cursor)
{
	if (cursor == NULL)
		return 0;
	else
		return 1 + count_nodes((cursor->next));
}
