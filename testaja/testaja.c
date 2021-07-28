#include <stdio.h>
int main()
{
  int angka;
  printf("Masukan sebuah angka: ");
  scanf ("%d", &angka);
  if (angka >= 0)
  {
    printf ("Nilai angka positif");
  }
  else
  {
    printf ("Nilai angka negatif");
  }
  return 0;
}
