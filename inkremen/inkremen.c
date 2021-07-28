/* Deskripsi : */
/* Efek dari operator ++ */

#include<stdio.h>

int main()
{ /* Kamus */
    int i;

    /* Program */
    i = 3;
    printf("Nilai i : %d \n", i);
    printf("%d \n", i, i++);
    i = 3;
    printf("%d \n", ++i); /* sebelum dicetak, nilai i ditambah 1 */
    printf("%d \n", i, i++);

    /* "++i" = "i, i++" */


    /* dekremen */
    i = 4;
    printf("Nilai i : %d \n", i);
    printf("%d \n", i, i--);
    printf("%d \n", --i);

    return 0;
}
