#include<stdio.h>

int main()
{
    float p, l;

    printf("Masukkan panjang persegi (m) = ");
    scanf("%f", &p);
    printf("Masukkan lebar persegi (m) = ");
    scanf("%f", &l);

    printf("Luas persegi adalah (m2) = %.2f \n", p * l);

    return 0;
}
