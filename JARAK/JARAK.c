#include<stdio.h>

int main()
{
    float v, t;

    printf("Masukkan kecepatan (km/j) = ");
    scanf("%f", &v);
    printf("\n");
    printf("Masukkan waktu tempuh (jam) = ");
    scanf("%f", &t);

    printf("Jaraknya adalah = %.2f km \n", v * t);

    return 0;
}
