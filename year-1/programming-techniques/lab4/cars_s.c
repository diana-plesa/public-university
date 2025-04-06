#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Să se implementeze un program care gestionează un parc de automobile. Informaţiile relative la un
automobil sunt: codul mașinii (număr între 1 si 9000), numărul de locuri (între 1 și 9), puterea (în cai putere între 1
și 500), marca, culoarea, anul fabricaţiei maşinii (între 1800 și 2017). Parcul conține n automobile, datele sunt citite
de la tastatură. Să se scrie următoarele funcții de gestiune a mașinilor:
a) Introducerea unui automobil nou;
b) Ștergerea unui anumit automobil, al cărui cod e citit de la tastatură;
c) Afișarea întregii liste de automobile;
d) Afișarea pe ecran doar a automobilelor cu un anumit număr de locuri, citit de la tastatură;
e) Ordonarea listei în funcție de anul fabricației, folosind qsort.*/


typedef struct 
{
    unsigned int code: 14;
    unsigned int seats: 4;
    unsigned int horse_pow: 9;
    unsigned int color: 32;
    unsigned int year: 11;
    char *brand;

}VEHICLE;

void delete_vehicle(unsigned int x, int n, VEHICLE *v)
{
    for (int i = 0; i < n; i++)
    {
        if (v[i].code == x)
        {
            free(v[i].brand);
            for (int j = i; j < n - 1; j++)
            {
                memcpy(&v[j], &v[j + 1], sizeof(VEHICLE));
            }
            i--;
            n--;
        }
    }
}

int compare(const void *e1, const void *e2)
{
    return (((VEHICLE *)e1)->year - ((VEHICLE *)e2)->year);
}

void print_vehicle(VEHICLE v)
{
    printf("Code: %u\n", v.code);
    printf("Seats: %u\n", v.seats);
    printf("Horse power: %u\n", v.horse_pow);
    printf("Color: %x\n", v.color);
    printf("Fabrication year: %u\n", v.year);
    printf("Brand: %s\n", v.brand);
    printf("\n");
}

void sort_vehicles(int n, VEHICLE *v)
{
    qsort(v, n, sizeof(VEHICLE), compare);
}

void print_all_vehicles(VEHICLE *v, int n)
{
    for (int i = 0; i < n; i++)
    {
        print_vehicle(v[i]);

    }
}

void print_specific_vehicles(unsigned int x, int n, VEHICLE *v)
{
    for (int i = 0; i < n; i++)
    {
        if (v[i].seats == x)
        {
            print_vehicle(v[i]);
        }
    }
}

int main()
{
    VEHICLE *vehicles = NULL;
    int k = 0;

    for (;;)
    {
        printf("Choose an option:\n");
        printf("1. Add a new vehicle\n");
        printf("2. Delete a vehicle\n");
        printf("3. Print all vehicles\n");
        printf("4. Print all vehicles with a given number of seats\n");
        printf("5. Sort the vehicles by fabrication year\n");
        printf("6. End\n");

        printf("Type command: ");

        int n;
        scanf("%d", &n);

        switch (n)
        {
            case 1:
                vehicles = realloc(vehicles, (k + 1) * sizeof(VEHICLE));

                if (vehicles == NULL)
                {
                    free(vehicles);
                    perror("Error realloc");
                    exit(-1);
                }

                VEHICLE new_vehicle;
                unsigned int code_aux;
                unsigned int seats_aux;
                unsigned int horse_pow_aux;
                unsigned int color_aux;
                unsigned int year_aux;
                char brand_aux[12];

                printf("\nNew vehicle code (1, 9000) : ");
                scanf("%u", &code_aux);
                new_vehicle.code = code_aux;

                printf("\nNew vehicle seats (1, 9) : ");
                scanf("%u", &seats_aux);
                new_vehicle.seats = seats_aux;

                printf("\nNew vehicle horse power (1, 500) : ");
                scanf("%u", &horse_pow_aux);
                new_vehicle.horse_pow = horse_pow_aux;

                printf("\nNew vehicle color (hexazecimal): ");
                scanf("%x", &color_aux);
                new_vehicle.color = color_aux;

                printf("\nNew vehicle fabrication year (1800, 2017) : ");
                scanf("%u", &year_aux);
                new_vehicle.year = year_aux;

                printf("\nNew vehicle brand: ");
                getchar();
                
                fgets(brand_aux, 12, stdin);
                brand_aux[strcspn(brand_aux, "\n")] = '\0';

                new_vehicle.brand = malloc(sizeof(char) * (strlen(brand_aux) + 1));

                if (new_vehicle.brand == NULL)
                {
                    perror("Error malloc");
                    exit(-1);
                }

                strcpy(new_vehicle.brand, brand_aux);

                memcpy(&vehicles[k], &new_vehicle, sizeof(VEHICLE));
                k++;
                break;
            case 2:
                printf("Type the code of the vehicle you want to delete: ");
                unsigned int del_code = 0;
                scanf("%u", &del_code);
                delete_vehicle(del_code, k, vehicles);
                k--;
                break;
            case 3:
                print_all_vehicles(vehicles, k);
                break;
            case 4:
                unsigned int nb_seats = 0;
                printf("Type number of seats: ");
                scanf("%u", &nb_seats);
                print_specific_vehicles(nb_seats, k, vehicles);
                break;
            case 5:
                sort_vehicles(k, vehicles);
                break;
            case 6:
                for (int i = 0; i < k; i++)
                    free(vehicles[i].brand); 
                free(vehicles);
                return 0;

        }
    }

    return 0;
}