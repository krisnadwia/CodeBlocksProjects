/* Deskripsi : */
/* contoh membaca nilai numerik: bilangan bulat, bilangan riil */
/* kemudian menuliskan nilai yang dibaca */
#include<stdio.h>

int main()
{ /* Kamus */
    int a;
    float x;

    /* Program */
    printf("Contoh membaca dan menulis, ketik nilai integer: ");
    scanf("%d", &a); /* membaca nilai a yang bertype integer perhatikan bahwa nama variabel ditulis dg &a*/
    printf("Nilai yang dibaca : %d \n", a);

    printf("Ketik nilai sebuah bilangan riil: ");
    scanf("%f", &x); /* membaca nilai a yang bertype integer*/
    printf("Nilai yang dibaca : %f \n", x);

    /* Coba-coba */
    /* coba ketik : scanf ("%d", a);dan tuliskan nilainya. Apa akibatnya ?*/
    /* coba ketik : scanf ("%f", x);dan tuliskan nilainya. Apa akibatnya ?*/

    return 0;
}
