#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void f(double a, double b, int n, double (*math_f)(double))
{
    double adder = (b - a) / (double) n;

    for (double i = a; i < b; i = i + adder)
    {
        printf("%lg ", math_f(i));
    }
}

int main()
{
    double a, b;

    printf("Type a: ");
    scanf("%lg", &a);
    printf("Type b: ");
    scanf("%lg", &b);

    int n;

    printf("Type n: ");
    scanf("%d", &n);

    if (n == 0)
    {
        printf("n can't be 0\n");
        exit(-1);
    }

    double (*math_f)(double);
    math_f = cos;

    printf("Cos: \n");
    f(a, b, n, math_f);
    printf("\nFabs: \n");
    f(a, b, n, fabs);
    printf("\nSqrt: \n");
    f(a, b, n, sqrt);
    printf("\n");
    return 0;
}