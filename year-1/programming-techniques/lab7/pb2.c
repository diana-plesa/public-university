#include <stdio.h>
#include <stdlib.h>

/*: Pentru implementarea listei care memorează ultimul element, să se scrie o funcție care primește două liste sortate 
și returnează lista sortată care conține toate elementele lor. Pentru lista rezultată se va folosi doar operația de 
adăugare la sfârșit de listă.
Exemplu: {1, 2, 7, 8} și {2, 9} -> {1, 2, 2, 7, 8, 9}*/

typedef struct list
{
    int info;
    struct list *next;
}node;

node* create_node(int val)
{
    node *new;
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

node* add_to_end(node *new, node *start)
{
    if (start == NULL)
        return new;
    
    node *cursor;

    for (cursor = start; cursor -> next != NULL; cursor = cursor -> next);

    cursor -> next = new;
    return start;

}

void print_list(node *start)
{
    node *cursor;

    for(cursor = start; cursor != NULL; cursor = cursor -> next)
    {
        printf("%d ", cursor -> info);
    }
    printf("\n");
}

node* compare_lists(node *start1, node *start2)
{
    node *cursor1, *cursor2, *new, *start3 = NULL;

    for (cursor1 = start1; cursor1 != NULL; cursor1 = cursor1 -> next)
    {
        for (cursor2 = start2; cursor2 != NULL; cursor2 = cursor2 -> next)
        {
            if (cursor1 -> info >= cursor2 -> info)
            {
                new = create_node(cursor2 -> info);
                start3 = add_to_end(new, start3);
                start2 = cursor2 -> next;
            }
        }
        new = create_node(cursor1 -> info);
        start3 = add_to_end(new, start3);
    }

    for (cursor2 = start2; cursor2 != NULL; cursor2 = cursor2 -> next)
    {
        new = create_node(cursor2 -> info);
        start3 = add_to_end(new, start3);
    }

    return start3;
}

void free_list(node *start)
{
    node *node_next, *cursor = start;

    while (cursor != NULL)
    {
        node_next = cursor -> next;
        free(cursor);
        cursor = node_next;
    }
}

int main()
{
    int opt = 0, val = 0;
    node *start1 = NULL, *start2 = NULL, *start3 = NULL, *new1, *new2;

    for(;;)
    {
        printf("1. Add element in list 1\n");
        printf("2. Add element in list 2\n");
        printf("3. Print list 1\n");
        printf("4. Print list 2\n");
        printf("5. Print final list\n");
        printf("6. End\n");

        printf("Type option: ");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1:
                printf("Type value of node: ");
                scanf("%d", &val);
                new1 = create_node(val);
                start1 = add_to_end(new1, start1);
                break;
            case 2:
                printf("Type value of node: ");
                scanf("%d", &val);
                new2 = create_node(val);
                start2 = add_to_end(new2, start2);
                break;
            case 3:
                print_list(start1);
                break;
            case 4:
                print_list(start2);
                break;
            case 5:
                start3 = compare_lists(start1, start2);
                print_list(start3);
                break;
            case 6:
                free_list(start1);
                free_list(start2);
                free_list(start3);
                return 0;
                break;
            
        }
    }

    return 0;
}