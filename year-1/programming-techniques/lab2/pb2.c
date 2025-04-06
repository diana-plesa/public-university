#include <stdio.h>
#include <stdlib.h>

void read_array(int n, int *a)
{
    for (int i = 0; i < n; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
}

int check_value(int x)
{
    if (x < 0)
        return 1;
    return 0;
}


void modif_array(int *a, int (*function)(int), int *n)
{
    for (int i = 0; i < *n; i++)
    {
        if (function(a[i]) == 1)
        {
            for (int j = i; j < *n; j++)
            {
                a[j] = a[j + 1];
            }
            i--;
            (*n)--;
        }
    }
}

void print_array(int *a, int *n)
{
    for (int i = 0; i < *n; i++)
        printf("%d ", a[i]);
}

int main()
{
    int n;
    printf("Type n: ");
    scanf("%d", &n);

    int *a;
    a = malloc(n * sizeof(int));

    if (a == NULL)
    {
        perror("Error memory alloc");
        exit(-1);
    }

    read_array(n, a);

    int (*p)(int);
    p = &check_value; 

    modif_array(a, p, &n);
    print_array(a, &n);

    free(a);
    return 0;
}