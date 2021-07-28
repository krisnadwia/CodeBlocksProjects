#include<stdio.h>

int main()
{
    int t;

    printf("Masukkan suhu air (celsius) = ");
    scanf("%d", &t);
    printf("\n");

    if (t <= 10)
    {
        printf("Air beku \n");
    }
    else if ((t >= 11) && (t <= 100))
    {
        printf("Air padat \n");
    }
    else
    {
        printf("Air uap \n");
    }

    return 0;
}
