#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void write_pixel(uint8_t pixel)
{
    FILE *g;
    g = fopen("new_image.bmp", "ab");

    if (g == NULL)
    {
        perror("Error opening new file");
        exit(-1);
    }

    pixel = pixel * 0.5;
    fwrite(&pixel, sizeof(pixel), 1, g);

    if (fclose(g) != 0)
    {
        perror("Error closing file");
        exit(-1);
    } 
}

void write_header(char *text)
{
    printf("text: %ld\n", sizeof(text));
    FILE *g;
    g = fopen("new_image.bmp", "ab");

    if (g == NULL)
    {
        perror("Error opening new file");
        exit(-1);
    }

    fwrite(text, 54, 1, g);

    if (fclose(g) != 0)
    {
        perror("Error closing file");
        exit(-1);
    }    
}

void adjust_file()
{
    FILE *f;
    f = fopen("im.bmp", "rb");
    
    if (f == NULL)
    {
        perror("Error opening file");
        exit(-1);
    }
    
    unsigned int width;
    unsigned int height;

    fseek(f, 18, SEEK_SET);

    fread(&width, sizeof(width), 1, f);
    fread(&height, sizeof(height), 1, f);
    printf("width: %u\n", width);
    printf("height: %u\n", height);

    char header_info[54];

    fseek(f, 0, SEEK_SET);

    fread(header_info, sizeof(header_info), 1, f);
    
    write_header(header_info);
    uint8_t pixel_byte = 0;


    while (!feof(f))
    //for (int i = 0; i < width * height; i++)
    {
        fread(&pixel_byte, sizeof(pixel_byte), 1, f);

        write_pixel(pixel_byte);
    }



    if (fclose(f) != 0)
    {
        perror("Error closing file");
        exit(-1);
    }
}

int main()
{
    adjust_file();
    return 0;
}