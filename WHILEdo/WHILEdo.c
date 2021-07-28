/* Deskripsi : */
/* print “Saya senang” sebanyak 3 kali */

#include<stdio.h>

int main()
{ /* Kamus */
    int i = 0;

    /* Algoritma */
    while (i < 3) /* program diulang selama nilai i < 3 */
    {
        printf("Saya senang belajar bahasa C \n");
        i++;
    }
    /* disini nilai i sudah berubah menjadi 3 karena while */
    for (i; i <= 5; i++)
    {
        printf("Saya senang belajar bahasa C Mantap \n");
    }
    return 0;
}
