#include <stdio.h>
#include <stdlib.h>

/* Se dă un vector cu n elemente numere naturale. Folosind metoda Divide et Impera să se verifice 
dacă are elementele ordonate strict crescător sau strict descrescător.*/

int check_ascend(int *array, int left, int right)
{
    //printf("left: %d right: %d", left, right);
    if (left >= right)
    {
        return 0;
    }
    else 
        return 1;
    
    int middle_index = (left + right) / 2;
    int check_left = check_ascend(array, left, middle_index);
    int check_right = check_ascend(array, middle_index + 1, right);
    if (check_left == 0 || check_right == 0)
        return 0;
    else 
        return 1;
    
}


int main()
{
    int n = 0, *array = NULL, check = 0;
    printf("Scrie n: ");
    scanf("%d",&n);

    array = malloc(sizeof(int) * n);

    if (array == NULL)
        {
            printf("Eroare malloc\n");
            exit(-1);
        }


    for(int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    check = check_ascend(array, 0, n - 1);
    if (check == 1) printf("Crescator\n");
    else printf("Descrescator\n");

    free(array);

    return 0;
}