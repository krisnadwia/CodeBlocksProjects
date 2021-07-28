/* Pemakaian standard library untuk membangkitkan bilangan random */

#include<stdio.h>
#include<stdlib.h>

/************************/

int main()
{
    const int MIN = 1;
    const int MAX = 100;

    /* Program akan membangkitkan 5 bilangan random antar MIN sampai MAX */
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", rand()%MAX + MIN);
    }

    return 0;
}

