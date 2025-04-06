#include <stdio.h>
#include <stdlib.h>

/*Într-o sală de spectacole, într-o zi, trebuie planificate n spectacole. Pentru fiecare 
spectacol se cunoaşte intervalul în care se desfăşoară. Se cere să se planifice un număr maxim 
de spectacole astfel încât să nu se suprapună.*/

typedef struct 
{
    int start;
    int end;
}SHOW;

int compar(const void *e1, const void *e2)
{
    const SHOW *el1 = (const SHOW *)e1;
    const SHOW *el2 = (const SHOW *)e2;
    int length1 = el1 -> end - el1 -> start;
    int length2 = el1 -> end - el1 -> start;

    if ((el1 -> start) != (el2 -> start))
    {
        return el1 -> start - el2 -> start;
    }
    else
    {
        return length1 - length2;
    }

    return 0;

}

void read_show(SHOW *elem)
{
    printf("Start: ");
    scanf("%d", &(elem -> start));
    printf("Final: ");
    scanf("%d", &(elem -> end));
}

void read(SHOW *shows, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Spectacol %d:\n", i + 1);
        read_show(&shows[i]);
    }
}

void print(SHOW *shows, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Spectacol %d:\n", i + 1);
        printf("Start: %d\n Final: %d\n", shows[i].start, shows[i].end);
    }
}

void print_result(SHOW *shows, int n)
{
    int last_end = 0;

    for (int i = 0; i < n; i++)
    {
        if (shows[i].start >= last_end)
        {
            printf("Spectacol %d - Start: %d End: %d\n", i + 1, shows[i].start, shows[i].end);
            last_end = shows[i].end;
        }
    }
}

int main()
{
    int n = 0;
    printf("Scrie numarul de spectacole = ");
    scanf("%d", &n);
    SHOW *shows;

    shows = malloc(n * sizeof(SHOW));

    if (shows == NULL)
    {
        perror("Eroare malloc\n");
        exit(-1);
    }

    read(shows, n);
    qsort(shows, n, sizeof(SHOW), compar);
    print_result(shows, n);


    //print(shows, n);
    
    return 0;
}