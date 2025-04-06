#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define CHUNK 4096

/*Să se scrie un program care primește o serie de n programe în linia de comandă și le concatenează pe primele n-1 într-un 
nou fișier având numele specificat pe ultima poziție din linia de comandă. Exemplu: ./concat 1.dat 2.dat 3.dat rez.dat       
-> concatenează conținutul fișierelor {1.dat, 2.dat, 3.dat} într-un nou fișier, denumit rez.dat*/

void concate(char* init_file, char* dest_file)
{
    FILE *f, *g;

    f = fopen(init_file, "rb");
    g = fopen(dest_file, "ab");

    if (f == NULL)
    {
        perror("Error opening initial file");
        exit(-1);
    }

    if (g == NULL)
    {
        perror("Error opening dest file");
        exit(-1);
    }

    uint8_t buffer[10];
    int n = 0;

    while ((n = fread(buffer, 1, 10, f)) != 0)
    {
        fwrite(buffer, 1, n, g);
    }

    if (fclose(f) != 0)
    {
        perror("Error closing initial file");
        exit(-1);
    }

    if (fclose(g) != 0)
    {
        perror("Error closing initial file");
        exit(-1);
    }
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc - 1; i++)
    {
        concate(argv[i], argv[argc - 1]);
    }
    return 0;
}