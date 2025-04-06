#include <stdio.h>
#include <stdlib.h>

/* Să se scrie o funcție care primește două liste și returnează 1 dacă ele sunt egale, indiferent de ordinea și numărul 
elementelor, altfel returnează 0.
Exemple: listele {1, 7, 3, 1, 3} și {7, 1, 3, 7} sunt egale. Listele {1,2} și {2} nu sunt egale*/

typedef struct list 
{
    int info;
    struct list* next;
}node;


node* create_node()
{
    int val = 0;
    printf("Type value of node: ");
    scanf("%d", &val);
    node* new;
    new = malloc(sizeof(node));

    if (new == NULL)
    {
        perror("Error malloc");
        exit(-1);
    }

    new -> info = val;
    new -> next = NULL;

    return new;
}

node* add_start(node* start, node* new)
{
    if (start == NULL)
        return new;
    
    new -> next = start;
    start = new;
    return start;
}

void print_l(node* start)
{
    node* cursor;

    for (cursor = start; cursor != NULL; cursor = cursor -> next)
    {
        printf("%d ", cursor -> info);
    }
    printf("\n");
}


int compare_lists(node* start1, node* start2)
{
    node* cursor1;
    node* cursor2;


    for (cursor1 = start1; cursor1 != NULL; cursor1 = cursor1 -> next)
    {
        int found = 0;

        for (cursor2 = start2; cursor2 != NULL; cursor2 = cursor2 -> next)
        {
            if (cursor1 -> info == cursor2 -> info)
                found = 1;
        }

        if (found == 0)
            return 0;
    }

    return 1;
}

void free_list(node* start)
{
    node *node_next;

    while (start != NULL)
    {
        node_next = start -> next; 
        free(start); 
        start = node_next;
    }
}

node* delete_item(node *start)
{
    printf("Type value of node you want to delete: ");
    int val = 0;
    scanf("%d", &val);
    node *cursor, *behind;

    if (start == NULL)
    {
        printf("Empty list\n");
        return start;
    }

    if (start -> info == val)
    {
        node *aux = start;
        start = start -> next;
        free(aux);
        return start;
    }

    for (cursor = start -> next, behind = start; cursor != NULL; cursor = cursor -> next, behind = behind -> next)
    {
        if (cursor -> info == val)
        {
            behind -> next = cursor -> next;
            free(cursor);
            return start;
        }
    }
    
        printf("Value does not exist in list\n");
        return start;

}

node* add_item(node* start, node* new)
{
    printf("Type value of node after which you wish to insert the new node: ");
    int val = 0;
    scanf("%d", &val);

    node *cursor;

    if (start == NULL)
    {
        printf("Empty list\n");
        return start;        
    }

    for (cursor = start; cursor -> info != val && cursor != NULL; cursor = cursor -> next);

    if (cursor == NULL)
    {
        printf("Value does not exist in list\n");
        return start;
    }

    new -> next = cursor -> next;
    cursor -> next = new;
    return start;
}

int main()
{
    int opt = 0;
    node *new1, *start1 = NULL;
    node *new2, *start2 = NULL;

    for(;;)
    {
        printf("Choose option\n");
        printf("1. Add node to list 1\n");
        printf("2. Add node to list 2\n");
        printf("3. Print list 1\n");
        printf("4. Print list 2\n");
        printf("5. Compare lists\n");
        printf("6. Delete a node from list 1\n");
        printf("7. Insert new node in list 1\n");
        printf("8. End\n");

        printf("Option: ");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1:
                new1 = create_node();
                start1 = add_start(start1, new1);
                break;

            case 2:
                new2 = create_node();
                start2 = add_start(start2, new2);
                break;

            case 3:
                print_l(start1);
                break;
            case 4:
                print_l(start2);
                break;

            case 5:
                if (compare_lists(start1, start2) == 1)
                    printf("Lists are equal\n");
                else 
                    printf("Lists aren't equal\n");
                break;
            case 6:
                start1 = delete_item(start1);
                break;
            case 7:
                new1 = create_node();
                start1 = add_item(start1, new1);
                break;

            case 8:
                free_list(start1);
                free_list(start2);
                return 0;
                break;

        }

    }

    return 0;
}
