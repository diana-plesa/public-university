#include <stdio.h>
#include <stdlib.h>

/* Să se scrie o funcție care primește două liste și returnează 1 dacă ele sunt egale, indiferent de ordinea și numărul 
elementelor, altfel returnează 0.
Exemple: listele {1, 7, 3, 1, 3} și {7, 1, 3, 7} sunt egale. Listele {1,2} și {2} nu sunt egale*/

typedef struct list1 
{
    int info;
    struct list1* next;
}node1;

typedef struct list2 
{
    int info;
    struct list2* next;
}node2;

node1* create_node_l1()
{
    int val = 0;
    printf("Type value of node: ");
    scanf("%d", &val);
    node1* new;
    new = malloc(sizeof(node1));

    if (new == NULL)
    {
        perror("Error malloc");
        exit(-1);
    }

    new -> info = val;
    new -> next = NULL;

    return new;
}

node1* add_start1(node1* start, node1* new)
{
    if (start == NULL)
        return new;
    
    new -> next = start;
    start = new;
    return start;
}

node2* create_node_l2()
{
    int val = 0;
    printf("Type value of node: ");
    scanf("%d", &val);
    node2 *new = malloc(sizeof(node2));

    if (new == NULL)
    {
        perror("error malloc");
        exit(-1);
    }

    new -> info = val;
    new -> next = NULL;

    return new;
}

node2* add_start2(node2* start, node2* new)
{
    if (start == NULL)
        return new;
    
    new -> next = start;
    start = new;
    return start;
}

void print_l1(node1* start)
{
    node1* cursor;

    for (cursor = start; cursor != NULL; cursor = cursor -> next)
    {
        printf("%d ", cursor -> info);
    }
    printf("\n");
}

void print_l2(node2* start)
{
    node2* cursor;

    for(cursor = start; cursor != NULL; cursor = cursor -> next)
    {
        printf("%d ", cursor -> info);
    }
    printf("\n");
}

int compare_lists(node1* start1, node2* start2)
{
    node1* cursor1;
    node2* cursor2;
    int found = 0;

    for (cursor1 = start1; cursor1 != NULL; cursor1 = cursor1 -> next)
    {
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

int main()
{
    int opt = 0;
    node1 *new1, *start1 = NULL;
    node2 *new2, *start2 = NULL;

    for(;;)
    {
        printf("Choose option\n");
        printf("1. Add node to list 1\n");
        printf("2. Add node to list 2\n");
        printf("3. Print list 1\n");
        printf("4. Print list 2\n");
        printf("5. Compare lists\n");
        printf("6. End\n");

        printf("Option: ");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1:
                new1 = create_node_l1();
                start1 = add_start1(start1, new1);
                break;

            case 2:
                new2 = create_node_l2();
                start2 = add_start2(start2, new2);
                break;

            case 3:
                print_l1(start1);
                break;
            case 4:
                print_l2(start2);
                break;

            case 5:
                if (compare_lists(start1, start2) == 1)
                    printf("Lists are equal\n");
                else 
                    printf("Lists aren't equal\n");

            case 6:
                return 0;
                break;

        }

    }

    return 0;
}
