/* Operasi aritmatika bilangan integer dan bilangan riil :
   Menuliskan jumlah, hasil perkalian, pembagian, modulo
 dua buah variabel integer*/

 #include<stdio.h>

 int main()
 { /* Kamus */

     int x = 5;
     int y = 8;

     /* Program */
     printf("Ini nilai x + y : %d \n", x + y);
     printf("Ini nilai x - y : %d \n", x - y);
     printf("Ini nilai x * y : %d \n", x * y);
     printf("Ini nilai x / y : %d \n", x / y);
     printf("Ini nilai y / x : %d \n", y / x);
     printf("Ini nilai x mod y : %d \n", x % y);
     printf("Ini nilai x + x + x : %d \n", x + x + x);
     printf("Ini nilai x * x + x : %d \n", x * x + x);

     /* bandingkan dengan operasi pembagian bilangan riil */
     float a = 5, b = 8;
     printf("Ini nilai a / b : %5.2f \n", a / b);
     printf("Ini nilai b / a : %5.2f \n", b / a);
     printf("ini nilai a / b * a + b - a : %.2f \n", a / b * a + b - a);
     printf("Ini nilai (((a+b)/(a*b)*a)-b)+a : %.2f \n", (((a+b)/(a*b)*a)-b)+a);


     int p, q, r;
     p = 5;
     q = 10;
     r = p * q;

     printf("%d \n", r);

     return 0;
 }
