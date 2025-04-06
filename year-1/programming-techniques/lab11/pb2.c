#include <stdio.h>
#include <stdlib.h>

/*Se consideră o matrice cu m linii și n coloane, numere naturale. Folosind metoda Divide et Impera, 
determinați suma numerelor pare din matrice*/

int get_sum(int **array, int n_start, int n, int m_start, int m)
{
    int sum = 0;
    if (n_start == n)
    {
        if (m == m_start)
            {
                if (array[n][m] % 2 == 0)
                    return array[n][m];
                else    
                    return 0;
            }
        else 
        {
            sum = sum + get_sum(array, n, n, m_start, (m_start + m)/2);
            sum = sum + get_sum(array, n, n, (m_start + m)/2 + 1, m);
            return sum;
        }

        
    }




    sum = sum + get_sum(array, n_start, (n_start + n) / 2, m_start, (m + m_start)/2);
    sum = sum + get_sum(array, n_start, (n_start + n)/2, (m_start + m)/2 + 1, m);
    sum = sum + get_sum(array, (n_start + n)/2 + 1, n, m_start, (m_start + m)/2);
    sum = sum + get_sum(array, (n_start + n)/2 + 1, n, (m_start + m)/2 + 1, m);
    return sum;
}

int main()
{
    int n, m, i, j;
    printf("m = ");
    scanf("%d", &n);
    printf("n = ");
    scanf("%d", &m);

    int aux = n;
    n = m;
    m = aux;

    int **array;
    array = malloc(sizeof(int*) * n);

    if (array == NULL)
    {
        perror("Eroare malloc");
        exit(-1);
    }

    for (i = 0; i < n; i++)
    {
        array[i] = malloc(sizeof(int) * m);
        
        if (array[i] == NULL)
        {
            perror("Eroare malloc");
            for (j = 0; j < i; j++)
                free(array[i]);

            free(array);
            exit(-1);
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &array[i][j]);
        }
    }


    int sum = 0;
    sum = get_sum(array, 0, n - 1, 0, m - 1);
    printf("%d", sum);

    for (i = 0; i < n; i++)
    {
        free(array[i]);
    }
    free(array);

    return 0;
}