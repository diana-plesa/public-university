#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/*Să se scrie o funcție int comune(int nVec,...) care primește un număr de vectori cu valori de tip int și
vectorii propriu-ziși. Fiecare vector se dă prin 2 argumente: un pointer la elementele sale și dimensiunea. Funcția
va returna numărul de elemente comune care se regăsesc în toți vectorii.
Exemplu: comune(3,v1,2,v2,3,v3,3) => returnează 2 pentru v1={5,8}, v2={8,3,5}, v3={5,0,8}*/

int exists_in_all(int x, int **vectors, int *lengths, int nVec)
{
    for (int i = 0; i < nVec; i++)
    {
        for (int j = 0; j < lengths[i]; j++)
        {
            if (vectors[i][j] == x)
            {
                printf("%d\n", x);
                return 1;
            }   
        }
    }
    return 0;
}

int common(int nVec, ...)
{
    va_list arg_list;
    va_start(arg_list, nVec);

    int *vectors[nVec];
    int lengths[nVec];
    int counter = 0, poz = 0;
    int min_length = 1000;

    for (int i = 0; i < nVec; i++)
    {
        vectors[i] = va_arg(arg_list, int *);
        lengths[i] = va_arg(arg_list, int);

        if (lengths[i] < min_length) 
            {
                min_length = lengths[i];
                poz = i;
            }

    }

    va_end(arg_list);


    for (int j = 0; j < min_length; j++)
    {
        counter = counter + exists_in_all(vectors[poz][j], vectors, lengths, nVec);
        //printf("%d ", vectors[poz][j]);
    }

    return counter;

}

int main()
{
    int v1[] = {1, 2}, v2[] = {2, 3, 5, 1}, v3[] = {1,2};

    printf("Common elements are %d\n", common(3, v1, 2, v2, 3, v3, 2));

    return 0;
}