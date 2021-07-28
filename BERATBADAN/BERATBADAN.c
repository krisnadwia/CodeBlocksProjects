#include<stdio.h>

int main()
{
    int b;

    printf("Masukkan berat badan = ");
    scanf("%d", &b);
    printf("\n");

    if (b <= 49)
    {
        printf("Kurus \n");
    }
    else if ((b >= 50) && (b <= 60))
    {
        printf("Ideal \n");
    }
    else if ((b >= 61) && (b <= 75))
    {
        printf("Gemuk \n");
    }
    else
    {
        printf("Kegemukan \n");
    }

    return 0;
}
