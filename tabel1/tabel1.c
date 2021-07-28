/* Deskripsi : */
/* Mendefinisikan array dan mengisi nilainya */

#include<stdio.h>

int main()
{ /* Kamus */
    int Tab[5] = {1, 2, 3, 4, 5}; /* Tab[0]=1; Tab[1]=2; . .. Tab[4]=5 */
    float TabX[3] = {1.5, 3.5E2, 9.99};
    char TabChar[4] = {'1', '2', '@', 'Z'};

    int i; /* untuk iterasi indeks tabel */

    /* menuliskan isi Tab berderet ke kanan */
    for (i = 0; i < 5; i++)
    {
        printf("Tab[%d] = %d ;", i, Tab[i]);
        printf ("\n");
    }
    printf ("\n");

    /* Latihan: tuliskan nilai TabX dan TabChar */
    for (i = 0; i < 3; i++)
    {
        printf("TabX[%.2f] = %.2f ;", i, TabX[i]);
        printf("\n");
    }
    printf("\n");

    for (i = 0; i < 4; i++)
    {
        printf("TabChar[%c] = %c ;", i, TabChar[i]);
        printf("\n");
    }
    printf("\n");

    return 0;
}
