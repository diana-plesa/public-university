#include <stdio.h>
#include <stdlib.h>

void read_array(float *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("a[%d] = ", i);
        scanf("%g", &a[i]);
    }
}

int compare(const void *elem1, const void *elem2)
{
    const float *p1 = (const float*) elem1;
    const float *p2 = (const float*) elem2;

    if (*p1 > *p2)
        return 1;
    if (*p1 == *p2)
        return 0;
    if (*p1 < *p2)
        return -1;
    return 0;
}

void print_array(float *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%g ", a[i]);
}

int cmpfct(const void *elem1, const void *elem2)
{
    const float* p1 = (const float*) elem1;
    const float* p2 = (const float*) elem2;
    return (*p1 - *p2);
}


int main()
{
    int n;

    printf("Type n: ");
    scanf("%d", &n);

    float a[10];
    
    read_array(a, n);
    qsort(a, n, sizeof(float), compare);
    //print_array(a, n);

    float x;
    printf("Type x: ");
    scanf("%g", &x);

    float *item;

    item = (float*)bsearch(&x, a, n, sizeof(float), cmpfct);

    if (item != NULL)
    {
        printf("Item exists\n");
    }
    else
    {
        printf("Item does not exist\n");
    }


    return 0;
}