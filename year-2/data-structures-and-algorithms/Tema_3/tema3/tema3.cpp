#include <stdio.h>
#include <string.h>

#define SIZE 10

void add_to_h(int val, int h[SIZE][SIZE])
{
    int i = 0;
    for (i = 0; i < SIZE; i++)
    {
        if (h[val % SIZE][i] == -1)
        {
            h[val % SIZE][i] = val;
            
            break;
        }
        
    }

    if (i == SIZE)
    {
        printf("Table doesn't have space for given element\n");
    }
}

void print_h(int h[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%d ", h[i][j]);
        }
        printf("\n");
    }
}

void search(int val, int h[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        if (h[val % 10][i] == val)
        {
            printf("Found element in table\n");
            return;
        }
    }

    printf("Element doesn't exist\n");
    
}

void remove_in_h(int val, int h[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        if (h[val % 10][i] == val)
        {
            h[val % 10][i] = -1;
            return;
        }
    }

    printf("Element doesn't exist\n");
}

int main()
{
    int h[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            h[i][j] = -1;
    }

    add_to_h(321, h);
    add_to_h(1256, h);
    add_to_h(321, h);
    add_to_h(1, h);
    add_to_h(25, h);
    add_to_h(17, h);

    search(25, h);
    print_h(h);
    remove_in_h(25, h);
    print_h(h);   
}


