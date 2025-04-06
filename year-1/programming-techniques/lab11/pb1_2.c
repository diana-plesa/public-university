#include <stdio.h>
#include <stdlib.h>

/* Se dă un vector cu n elemente numere naturale. Folosind metoda Divide et Impera să se verifice 
dacă are elementele ordonate strict crescător sau strict descrescător.*/

int check_ascend(int *array, int left, int right)
{
    if ( left + 1 >= right)
    {
        if (left == right)
            return 3;
        if (array[left] > array[right])
            return 0;
        else
            return 1;
    }
    
    int middle_index = (left + right) / 2;
    int check_left = check_ascend(array, left, middle_index);
    int check_right = check_ascend(array, middle_index + 1, right);
    
    if(check_left == 3) check_left = check_right;
    if(check_right == 3) check_right = check_left;
    
    if (check_left == check_right && check_left==1 && array[middle_index] < array[middle_index + 1])
        return 1;
        
    if (check_left == check_right && check_left==0 && array[middle_index] > array[middle_index + 1])
        return 0;
        
    return 2;
}


int main()
{
    int n = 0, check = 0;
    printf("Scrie n: ");
    scanf("%d",&n);

    int* array = malloc(n * sizeof(int));
    if (array == NULL)
    {
        printf("Eroare realloc\n");
        exit(-1);
    }

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    check = check_ascend(array, 0, n - 1);
    if (check == 0) printf("Descrescator\n");
    if (check == 1) printf("Crescator\n");
    if (check == 2) printf("Nesortat\n");
    if (check == 3) printf("Un singur element\n");

    free(array);

    return 0;
}