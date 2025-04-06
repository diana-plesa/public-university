#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Se cere un număr n și apoi un vector de n rezultate ale studenților la un examen. Fiecare rezultat
este definit prin (nume,nota). Se cere să se sorteze folosind qsort vectorul în ordinea notelor, notele cele mai mari
fiind primele. Dacă două note sunt identice, rezultatele respective se vor sorta în ordinea alfabetică a numelor.*/

typedef struct 
{
    char name[20];
    int grade;
}STUDENT;

void read_array(int n, STUDENT *a)
{
    for (int i = 0; i < n; i++)
    {
        printf("Name: ");
        scanf("%19s", a[i].name);
        printf("Grade: ");
        scanf("%d", &a[i].grade);

    }
}

int compare(const void *elem1, const void *elem2)
{
    const STUDENT *p1=(const STUDENT*)elem1;
    const STUDENT *p2=(const STUDENT*)elem2;

    if (p1->grade > p2->grade)
        return -1;
    if (p1->grade == p2->grade)
    {
        if (strcmp(p1->name, p2->name) == 0)
            return 0;
        else
        {
            if ((strcmp(p1->name, p2->name) < 0))
                return -1;
            
            else return 1;
            
        }
    }
    if (p1->grade < p2->grade)
        return 1;
    return 0;
}

void print_array(int n, STUDENT *a)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", a[i].name, a[i].grade);
    }
}

int main()
{
    int n;
    printf("Type n: ");
    scanf("%d", &n);

    STUDENT *a;
    a = malloc(n * sizeof(STUDENT));

    if (a == NULL)
    {
        perror("Error memory alloc");
        exit(-1);
    }

    read_array(n, a);

    qsort(a, n, sizeof(STUDENT), compare);

    print_array(n, a);

    free(a);

    return 0;
}