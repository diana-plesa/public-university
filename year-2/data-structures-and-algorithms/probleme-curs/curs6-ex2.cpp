#include <stdio.h>
#include <stdlib.h>

/* Pornind de la implementarea algoritmului Quicksort din acest curs, dezvoltați o serie de
implementări care să fie cât mai eficiente din punct de vedere alt timpului de rulare și a
memoriei utilizate considerănd :
◦ Diferite variante de alegere a pivotului
◦ Ineficiența pentru un număr mic de elemente : în apelul recursiv, nu apelați tot quicksort() pe
un tablou cu mai puțin de L elemente(unde valoarea lui L o alegeți dvs.), ci apelați sortarea
prin inserție sub această limită(în rest se va apela quicksort în mod obișnuit)
◦ Ineficiența pentru cazul în care numărul de elemente egale este semnificativ : implementați o
variantă care împarte tabloul în trei partiții în loc de două(prima conține elementele mai mici
    decât pivotul, a doua elementele egale cu pivotul și a treia, elementele mai mari)*/

void swap(int* e1, int* e2)
{
    int aux = *e1;
    *e1 = *e2;
    *e2 = aux;
}

int partition(int arr[], int left, int right) 
{ 
    //int pivot = arr[right]; //pivotul e ultimul; ineficient cand array-ul este deja sortat
    int pivot = arr[rand() % (right - left + 1) + left]; //pivotul e ales aleator 
    //int pivot = arr[left + (right - left) / 2]; //pivotul e elementul de la mijloc

    int i = left - 1;
    int j = right + 1;

    while (true)
    {
        do
        {
            i++;
        } while (arr[i] < pivot);

        do
        {
            j--;
        } while (arr[j] > pivot);

        if (i > j)
            return j;

        swap(&arr[i], &arr[j]);

    }
}

void partition_in_3(int arr[], int left, int right, int *m1, int *m2) 
{
    //partitionarea in 3 segmente, separate de m1 si m2, care delimiteaza al doilea segment ce contine elementele
    //egale cu pivotul; de la left la m1-1 sunt elementele mai mici decat pivot, si de la m2+1 la right sunt
    //elementele mai mari decat pivotul

    int pivot = arr[right];
    int i = left;
    *m1 = left, *m2 = right;

    while (i < right)
    {
        if (arr[i] < pivot)
        {
            swap(&arr[*m1], &arr[i]);
            (*m1)++;
        }

        else if (arr[i] > pivot)
        {
            swap(&arr[*m2], &arr[i]);
            (*m2)--;
        }

        else i++;
    }
}

void quicksort(int arr[], int left, int right)
{
    if (left < right)
    {
        int pivot = partition(arr, left, right);

        quicksort(arr, left, pivot);
        quicksort(arr, pivot + 1, right);
    }

}

void first_quicksort(int arr[], int left, int right, int *m1, int *m2)
{
    partition_in_3(arr, left, right, m1, m2);

    quicksort(arr, left, *m1 - 1);
    quicksort(arr, *m2 + 1, right);

}



void print_arr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

void insert_sort(int* arr, int start, int end)
{
    int i = start, j = start, to_insert = 0;

    for (i = start + 1; i < end; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            to_insert = arr[i];

            j = i;

            while (j > start && to_insert < arr[j - 1])
            {
                arr[j] = arr[j - 1];
                j--;
            }

            arr[j] = to_insert;
        }
    }
}

void quicksort_min(int arr[], int left, int right, int min_nb) 
{
    //quicksort cu implementare de insert sort cand avem un nr de elemente mai mic decat min_nb dat ca parametru

    if (left < right) {
        int pivot = partition(arr, left, right);

        if (pivot - left < min_nb)
            insert_sort(arr, left, pivot + 1);
        else
            quicksort_min(arr, left, pivot, min_nb);

        if (right - pivot - 1 < min_nb)
            quicksort_min(arr, pivot + 1, right, min_nb);
        else
            insert_sort(arr, pivot + 1, right + 1);
    }
}

int main()
{
    int arr[9];
    int m1 = 0;
    int m2 = 8;

    arr[0] = 5;
    arr[1] = 4;
    arr[2] = 1;
    arr[3] = 3;
    arr[4] = 2;
    arr[5] = 4;
    arr[6] = 10;
    arr[7] = 0;
    arr[8] = 4;
   
    //first_quicksort(arr, 0, 8, &m1, &m2);
    quicksort_min(arr, 0, 8, 4);
    print_arr(arr, 9);


	return 0;
}
