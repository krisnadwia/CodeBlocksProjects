/* Mencari nilai maksimum dari sebuah tabel yang berisi 10 nilai integer */

#include<stdio.h>

int main()
{ /* Kamus */
    int i;
    int Tab[10] = {1, 50, 6, 200, 3, 100, 30, 8, 99, 100};
    int max;
    int min;
    float rata, total;

    /* Algoritma */
    max = Tab[0];
    for (i = 1; i < 10; i++)
    {
        if (Tab[i] > max)
        {
            max = Tab[i];
        }
    }
    printf("Nilai Max = %d", max);

    printf("\n");

    min = Tab[0];
    for (i = 1; i > 10; i++)
    {
        if (Tab[i] < min)
        {
            min = Tab[i];
        }
    }
    printf("Nilai Min = %d", min);

    printf("\n");

    /* rata-rata */
    for(i = 0; i < 10; i++)
    {
        total = total + Tab[i];
    }

    printf("\n");

    rata = total / 10;
    printf("hasil nilai total adalah: %.2f \n", total);
    printf("hasil rata rata adalah: %.2f \n", rata);

    return 0;
}
