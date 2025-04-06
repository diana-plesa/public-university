#include <stdio.h>

int main()
{
    int n, m, a[20][20], i ,j;

    scanf("%d%d", &n, &m);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    FILE *f;
    f = fopen("fisier.bin", "wb");

    fwrite(&n, sizeof(int), 1, f);
    fwrite(&m, sizeof(int), 1, f);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            fwrite(&a[i][j], sizeof(a[i][j]), 1, f);
        }
    }

    FILE *g;
    g = fopen("fisier.bin", "rb");

    int m2, n2;

    int b[20][20];

    fread(&n2, sizeof(n2), 1, g);
    fread(&m2, sizeof(m2), 1, g); 

    for (i = 0; i < n2; i++)
    {
        for (j = 0; j < m2; j++)
        {
            fread(&b[i][j], sizeof(b[i][j]), 1, g);
        }
    }

    printf("%d %d\n", n2, m2);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    fclose(g);
    fclose(f);

}