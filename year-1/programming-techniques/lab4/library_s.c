#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*: Să se realizeze o aplicaţie pentru gestionarea unei biblioteci folosind struct și union, iar dacă e
posibil și structuri cu câmpuri pe biți.
Se vor memora următoarele informaţii pentru fiecare înregistrare:
 Titlu
 Autor
 Număr de exemplare
 Preț (exprimat în lei, număr întreg, maxim 500 lei)
 Număr de pagini (maxim 1000 pagini)
 Greutate (exprimată în grame, maxim 5000 grame)
 Dacă e Carte sau Revistă
 Dacă e carte se va memora ISBN, sir de 13 caractere, exemplu: 9783161484100, iar dacă e revistă se va
memora anul în care a apărut primul număr

Folosind un meniu să se realizeze următoarele operaţii:
a) Introduceţi un produs.
b) Afişaţi toate publicaţiile aflate în stoc care sunt cărţi si au preţul peste 100.
c) Afişaţi toate înregistrările.
d) Salvaţi toate publicatiile - Toate produsele se vor salva într-un fişier binar (inventar.bin) folosind structura
creată anterior.
Datele de intrare se vor citi de la tastatură.*/

typedef union 
{
    unsigned int year: 11;
    char ISBN[14]; 
}TYPE;

typedef struct 
{
    unsigned int number: 6;
    unsigned int price: 9;
    unsigned int pages: 10;
    unsigned int weight: 13;
    unsigned int type: 2;
    char title[10];
    char author[30];
    TYPE appearance;

}PRODUCT;

void read_new_product(PRODUCT *x)
{
    printf("\nTitle: ");
    getchar();
    fgets(x->title, 10, stdin);
    x->title[strcspn(x->title, "\n")] = '\0';

    printf("\nAuthor: ");
    fgets(x->author, 30, stdin);
    x->author[strcspn(x->author, "\n")] = '\0';

    printf("\nNumber of exemplaries: ");
    unsigned int nb_aux;
    scanf("%u", &nb_aux);
    x->number = nb_aux;

    printf("\nPrice: ");
    unsigned int price_aux;
    scanf("%u", &price_aux);
    x->price = price_aux;

    printf("\nNumber of pages (max 1000): ");
    unsigned int pages_aux;
    scanf("%u", &pages_aux);
    x->pages = pages_aux;

    printf("\nWeight (max 5000): ");
    unsigned int weight_aux;
    scanf("%u", &weight_aux);
    x->weight = weight_aux;   

    printf("\nType (1 = book, 2 = magazine): ");
    unsigned int type_aux;
    scanf("%u", &type_aux);
    x->type = type_aux;  

    if (x->type == 1) //book
    {
        printf("\nType ISBN (13 characters): ");
        getchar();
        fgets(x->appearance.ISBN, 14, stdin);
        x->appearance.ISBN[strcspn(x->appearance.ISBN, "\n")] = '\0';
    }
    if (x->type == 2) //magazine
    {
        printf("\nType year of first model appearance (max 2024): ");
        unsigned int app_aux;
        scanf("%u", &app_aux);
        x->appearance.year = app_aux;
    }
}

void print_product(PRODUCT x)
{
    printf("\nTitle: %s", x.title);
    printf("\nAuthor: %s", x.author);
    printf("\nNumber of exemplaries: %u", x.number);
    printf("\nPrice: %u", x.price);
    printf("\nNumber of pages: %u", x.pages);
    printf("\nWeight: %u", x.weight);
    if (x.type == 1)
    {
        printf("\nType: book");
        printf("\nISBN: %s", x.appearance.ISBN);
    }
    else 
    {
        printf("\nType: magazine");
        printf("\nYear of first appearance: %u\n", x.appearance.year);        
    }

}

void print_specific_products(PRODUCT *p, int n)
{
    for (int i = 0; i < n; i++)
    {
            if (p[i].type == 1 && p[i].price > 100)
            print_product(p[i]); 
    }
    printf("\n");
}

void write_in_file(PRODUCT *p, int n)
{
    FILE *f;
    f = fopen("inventar.bin", "wb");
    if (f == NULL)
    {
        free(p);
        perror("Error opening file");
        exit(-1);
    }

    for (int i = 0; i < n; i++)
    {
        fwrite(&p[i], sizeof(PRODUCT), 1, f);
    }

    if (fclose(f) != 0)
    {
        free(p);
        perror("Error closing file");
        exit(-1);
    }
}

void print_all_products(PRODUCT *p, int n)
{
    for (int i = 0; i < n; i++)
        print_product(p[i]);
    printf("\n");
}

void read_file(PRODUCT *p, int n)
{
    FILE *f;
    f = fopen("inventar.bin", "rd");
    if (f == NULL)
    {
        perror("Error opening file at reading");
        exit(-1);
    }

    for (int i = 0; i < n; i++)
    {
        fread(&p[i], sizeof(PRODUCT), 1, f);
        print_product(p[i]);
    }

    if (fclose(f) != 0)
    {
        perror("Error closing file at reading");
        exit(-1);
    }
}

int main()
{
    int k = 0;
    PRODUCT *products = NULL;
    for (;;)
    {
        printf("Choose an option: ");
        printf("\n1. Add a new product");
        printf("\n2. Print all books with price > 100");
        printf("\n3. Print all products");
        printf("\n4. Save all products in a binary file");
        printf("\n5. End");

        printf("\nType your instruction: ");
        int n = 0;
        scanf("%d", &n);

        switch(n)
        {
            case 1:
                products = realloc(products, (k + 1) * sizeof(PRODUCT));

                if (products == NULL)
                {
                    perror("Error realloc");
                    exit(-1);
                }
                read_new_product(&products[k]);
                k++;
                break;
            case 2:
                print_specific_products(products, k);
                break;
            case 3:
                print_all_products(products, k);
                break;
            case 4:
                write_in_file(products, k);
                read_file(products, k);
                break;
            case 5:
                free(products);
                return 0;
        }
    }
    return 0;
}