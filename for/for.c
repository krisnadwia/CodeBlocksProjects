/* Deskripsi :
/* print “Saya senang” sebanyak 3 kali */

#include<stdio.h>

int main()
{ /* Kamus */
    int i;
    int j, max;
    int k = 5;

    /* Algoritma */
    for (i = 0; i < 3; i++)
    {
        printf("Saya senang belajar bahasa C Mantap \n");
    }

    for (i = 1; i <= 1000; i++)
    {
        printf("Saya senang belajar bahasa C OK \n");
    }

    for (i = 1; i < k; i++)
    {
        printf("Saya senang belajar bahasa C Mantul \n");
    }

    printf("Masukkan berapa yang akan di print: \n");
    scanf("%d", &max);
    for (j = 1; j <= max; j++)
    {
        printf("Saya senang belajar bahasa C Sip \n");
    }

    return 0;
}
