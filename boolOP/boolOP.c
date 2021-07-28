/* Deskripsi : */
/* Contoh perhitungan aljabar boolen, perhatikan cara penulisan
   AND dan OR serta NOT */

#include<stdio.h>

int main()
{ /* Kamus */
    int TRUE = 1;
    int FALSE = 0;

    /* Algoritma */
    printf("Ini nilai TRUE AND TRUE : %d \n", TRUE && TRUE);
    printf("Ini nilai TRUE OR TRUE : %d \n", TRUE || TRUE);
    printf("Ini nilai FALSE AND TRUE : %d \n", FALSE && TRUE);
    printf("Ini nilai FALSE OR TRUE : %d \n", FALSE || TRUE);
    printf("Ini nilai NOT TRUE : %d \n", !TRUE);
    printf("Ini nilai NOT FALSE : %d \n", !FALSE);

    return 0;
}
