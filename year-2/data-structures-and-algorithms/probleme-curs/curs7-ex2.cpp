#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

//Scrieți un program care inserează structuri într-un tablou, le caută și le șterge folosind una 
//din metodele de hashing studiate în acest curs -> tehnica dispersiei deschise

typedef struct
{
    int val;

}INFO;

typedef struct list
{
    INFO item;
    list* next;
}element;

int get_key(int val)
{
    return val % SIZE;
}

element* init(element* start)
{
    if (start == NULL)
        return start;

    element* cursor = NULL;

    while (start != NULL)
    {
        cursor = start;
        start = start->next;
        free(cursor);
    }
    return start;
}

element* create_node(INFO info)
{
    element* new_node = (element*)malloc(sizeof(element));

    if (new_node == NULL)
    {
        printf("Error malloc new node\n");
        exit(-1);
    }

    new_node->item.val = info.val;
    new_node->next = NULL;

    return new_node;

}

element* add_node(element* start, INFO info)
{
    if (start == NULL)
    {
        start = create_node(info);
        return start;
    }

    element* cursor = start;

    while (cursor->next != NULL)
    {
        cursor = cursor->next;
    }

    element* new_node = create_node(info);
    new_node->next = cursor->next;
    cursor->next = new_node;

    return start;
}

element* add_to_h(INFO info, element** h)
{
    int index = get_key(info.val);

    h[index] = add_node(h[index], info);

    return h[index];

}

void print_list(element* start)
{
    if (start == NULL)
    {
        printf("Empty\n");
        return;
    }

    element* cursor = NULL;

    for (cursor = start; cursor != NULL; cursor = cursor->next)
    {
        printf("%d ", cursor->item.val);
    }
    printf("\n");
}


void print_h(element** h)
{
    for (int i = 0; i < SIZE; i++)
    {
        print_list(h[i]);
    }
    printf("\n");
}

void find_element(int val, element* start)
{
    if (start == NULL)
    {
        printf("item not found\n");
        return;
    }

    element* cursor = NULL;

    for (cursor = start; cursor != NULL; cursor = cursor->next)
    {
        if (cursor->item.val == val)
        {
            printf("item found\n");
            return;
        }
    }

    printf("item not found\n");
}

void find_in_h(int val, element** h)
{
    int index = get_key(val);
    find_element(val, h[index]);
}

element* remove_from_list(element* start, int val)
{
    if (start == NULL)
    {
        return NULL;
    }

    element* cursor = start->next;
    element* prev_cursor = start;
    element* aux = NULL;

    if (start->item.val == val)
    {
        aux = start;
        start = start->next;
        free(aux);
        return start;
    }

    while (cursor != NULL)
    {
        if (cursor->item.val == val)
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


void remove_from_h(int val, element** h)
{
    int index = get_key(val);
    h[index] = remove_from_list(h[index], val);

}

int main()
{
    element* h[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        h[i] = NULL;
    }

    INFO info1, info2, info3, info4, info5;
    info1.val = 321;
    info2.val = 11;
    info3.val = 34445;
    info4.val = 5;
    info5.val = 777;

    add_to_h(info1, h);
    add_to_h(info2, h);
    add_to_h(info3, h);
    add_to_h(info4, h);
    add_to_h(info5, h);
    print_h(h);

    //find_in_h(21, h);
    remove_from_h(321, h);
    remove_from_h(8, h);
    remove_from_h(11, h);
    remove_from_h(5, h);
    remove_from_h(34445, h);

    print_h(h);


    return 0;
}


