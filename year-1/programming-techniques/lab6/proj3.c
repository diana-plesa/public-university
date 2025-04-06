#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void write_in_file(char *text, int size, FILE *g)
{
    fwrite(text, size, 1, g);
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

    FILE *g;
    g = fopen("new_image.bmp", "wb");

    if (g == NULL)
    {
        perror("Error opening new file");
        exit(-1);
    }
    
    unsigned int width = 0;
    unsigned int height = 0;
    uint16_t num_colors = 0;
    unsigned long long img_size = 0;

    fseek(f, 18, SEEK_SET);

    fread(&width, sizeof(width), 1, f);
    printf("width %d\n", width);
    fread(&height, sizeof(height), 1, f);
    printf("height %d\n", height);

    fseek(f, 28, SEEK_SET);

    fread(&num_colors, sizeof(num_colors), 1, f);
    printf("num colors: %d\n", num_colors);

    fseek(f, 0x22, SEEK_SET);
    fread(&img_size, 4, 1, f);
    printf("image size %lld\n", img_size);

    char header_info[54];

    fseek(f, 0, SEEK_SET);

    fread(header_info, 54, 1, f); 
    write_in_file(header_info, 54, g);

    uint8_t pixel_data[3], blue, green, red;

    //for (int i = 0; i < width * height; i++)
    while (!feof(f))
    {
        fread(pixel_data, 1, 3, f);
        blue = pixel_data[0] * 0.114;
        green = pixel_data[1] * 0.587;
        red = pixel_data[2] * 0.299;

        pixel_data[0] = red + green + blue;
        pixel_data[1] = red + green + blue;
        pixel_data[2] = red + green + blue;

        fwrite(pixel_data, 1, 3, g);

    }


    if (fclose(f) != 0)
    {
        perror("Error closing file f");
        exit(-1);
    }

    if (fclose(g) != 0)
    {
        perror("Error closing file g");
        exit(-1);
    }
}

int main()
{
    adjust_file();
    return 0;
}