/* Menentukan posisi di mana elemen tabel bernilai X */

#include<stdio.h>

int main()
{ /* Kamus */
    int i;
    int j;
    int Tab[10] = {1, 50, 6, 200, 3, 100, 30, 8, 99, 100};
    int X = 8; /* indeks dimana Tab[max] bernilai maksimum */

    /* Algoritma sequential search paling sederhana */
    /* program berhenti pada indeks I dimana nilai diketemukan */
    i = 0;
    while ( (Tab[i] != X) && (i < 9) )
    {
        i++;
    } /* Tab[i] == X atau i == 9 */
    if (Tab[i] == X)
    {
        printf("indeks bernilai X = %d", i); /* indeks ke berapa? 8 adalah indeks ke 7 */
    }
    else
    {
        printf("nilai tidak diketemukan");
    }

    printf("\n");
    printf("\n");

    /* menggunakan scanf */
    printf("Ketikkan angka yang akan dicari dan termasuk ke indeks berapa \n");
    scanf("%d", &j);

    i = 0;
    while ( (Tab[i] != j) && (i < 9) )
    {
        i++;
    } /* Tab[i] == j atau i == 9 */
    if (Tab[i] == j)
    {
        printf("indeks bernilai j = %d", i); /* indeks ke berapa? 8 adalah indeks ke 7 */
    }
    else
    {
        printf("nilai tidak diketemukan");
    }

    return 0;
}
