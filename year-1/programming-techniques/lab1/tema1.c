

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int pb1()
{
    int n, **m, i, j;
    
    printf("Type n: ");
    scanf("%d", &n);

    if ((m = malloc(n * sizeof(int*))) == NULL)
    {
        perror("error memory malloc for lines");
        exit(-1);
    }

    for (i = 0; i < n; i++)
    {
        if ((m[i] = malloc(n * sizeof(int))) == NULL)
        {
            for (j = 0; j < i; j++)
            {
                free(m[j]);
            }
            free(m);
            perror("error memory malloc for cols");
            exit(-1);
        }
    }

    for (i = 0;i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Type m[%d][%d]: ", i, j);
            scanf("%d", &m[i][j]);
        }
    }

    int *sl, *sc;

            if ((sl = malloc(n * sizeof(int))) == NULL)
        {
            perror("error malloc sl");
            for (i = 0; i < n; i++)
                free(m[i]);
            free(m);
            exit(-1);
        }

            if ((sc = malloc(n * sizeof(int))) == NULL)
        {
            perror("error malloc sc");
            for (i = 0; i < n; i++)
                free(m[i]);
            free(m);
            free(sl);
            exit(-1);
        } 

    for (i = 0 ;i < n; i++)
    {
        int sum_lin = 0;
        int sum_col = 0;

        for (j = 0; j < n; j++)
        {
            sum_lin = sum_lin + m[i][j];
            sum_col = sum_col + m[j][i];
        }

        sl[i] = sum_lin;
        sc[i] = sum_col;
    }


    printf("Sum of each line: ");
    for (i = 0; i < n; i++)
        printf("%d ", sl[i]);

    printf("\n");

    printf("Sum of each col: ");
    for (i = 0; i < n; i++)
        printf("%d ", sc[i]);

    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
    free(sl);
    free(sc);

    return 0;
}

void read_matrix(char **m, int n)
{
    char c;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            {             
                do
                {
                    scanf("%c", &c);
                } while (isalpha(c) == 0);

                m[i][j] = c;
                
            }
    }
}

int lr_line(char **m, char *word, int n)
{
    int i, j, ok = 0;
    char new_word[n + 1];

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            new_word[j] = m[i][j];
        }
        new_word[j] = '\0';

        char *x;
        int poz = 0;

        while (strstr(new_word + poz, word) != NULL)
        {
            x = strstr(new_word + poz, word);
            int index = x - new_word;
            printf("De la linia %d coloana %d spre dreapta\n", i, index);
            ok = 1;
            poz = index + 1;
        }
    }
    return ok;
}

int rl_line(char **m, char *word, int n)
{
    int i, j, ok = 0, k = 0;
    char new_word[n + 1];

    for (i = 0; i < n; i++)
    {
        k = 0;
        for (j = n - 1; j >= 0; j--)
        {
            new_word[k] = m[i][j];
            k++;
        }
        new_word[k] = '\0';

        char *x;
        int poz = 0;

        while (strstr(new_word + poz, word) != NULL)
        {
            x = strstr(new_word + poz, word);
            int index = x - new_word;
            printf("De la linia %d coloana %d spre stanga\n", i, n - index - 1);
            ok = 1;
            poz = index + 1;
        }
    }
    return ok;
}

int ud_col(char **m, char *word, int n)
{
    int i, j, ok = 0;
    char new_word[n + 1];

    for (j = 0; j < n; j++)
    {
        for (i = 0; i < n; i++)
        {
            new_word[i] = m[i][j];
        }
        new_word[i] = '\0';
        char *x;

        int poz = 0;

        while (strstr(new_word + poz, word) != NULL)
        {
            x = strstr(new_word + poz, word);
            int index = x - new_word;
            printf("De la linia %d coloana %d in jos\n", index, j);
            ok = 1;
            poz = index + 1;
        }
    }

    return ok;
    
}

int du_col(char **m, char *word, int n)
{
    int i, j, ok = 0;
    char new_word[n + 1];

    for (j = 0; j < n; j++)
    {
        int k = 0;
        for (i = n - 1; i >= 0; i--)
        {
            new_word[k] = m[i][j];
            k++;
        }
        new_word[k] = '\0';
        char *x;
        int poz = 0;
        
        while (strstr(new_word + poz, word) != NULL)
        {
            x = strstr(new_word + poz, word);
            int index = x - new_word;
            printf("De la linia %d coloana %d in sus\n", n - index - 1, j);
            ok = 1;
            poz = index + 1;
        }        

    }
    return ok;
}

int pb2()
{

    int n, i, j;
    char **m;

    printf("Type n: ");
    scanf("%d", &n);
    getchar();

    if ((m = malloc(n * sizeof(char*))) == NULL)
    {
        perror("Error lines malloc");
        exit(-1);
    }

    for (i = 0; i < n; i++)
    {
        if ((m[i] = malloc(n * sizeof(char))) == NULL)
        {
            for (j = 0; j < i; j++)
                free(m[j]);
            free(m);
            perror("Error lines malloc");
            exit(-1);
        }
    }

    read_matrix(m, n);
    getchar();

    char *word;
    word = malloc((n + 1) * sizeof(char));

    fgets(word, n + 1, stdin);
    word[strcspn(word, "\n")] = '\0';

    int ok1 = 0, ok2 = 0, ok3 = 0, ok4 = 0;

    ok1 = lr_line(m, word, n);
    ok2 = rl_line(m, word, n);
    ok3 = ud_col(m, word, n);
    ok4 = du_col(m, word, n);

    if ((ok1 == 0) || (ok2 == 0) || (ok3 == 0) || (ok4 == 0))
        printf("Nu exista solutie\n");

    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
    free(word);

    return 0;
}

int main()
{

    //Se citește de la tastatură o matrice cu n<=20 linii și coloane. Să se memoreze într-un vector suma tuturor elementelor de 
    //pe fiecare linie și într-un alt vector, suma tuturor elementelor de pe fiecare coloană. Să se afișeze cei doi vectori. Se vor utiliza pointeri 
    //atât pentru vectori cât și pentru matrici.

    pb1();

    printf("\n");

    //Se citesc de la tastatură un număr n și o matrice pătratică de dimensiune n conținând litere din alfabet. 
    //Pe urmă se citește de la tastatură un cuvânt. Verificați dacă respectivul cuvânt se poate construi parcurgând 
    //literele matricii pe verticală în sus sau în jos sau pe orizontală spre stânga sau spre dreapta. Afișați toate pozițiile 
    //de unde trebuie începută parcurgerea, precum și sensul de parcurgere necesar pentru a construi cuvântul.
    
    pb2();

    return 0;
}