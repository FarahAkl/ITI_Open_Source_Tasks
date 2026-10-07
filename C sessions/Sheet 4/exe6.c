#include <stdio.h>

int factorial(int a);
void main(void)
{
    int a;
    int total = 1;
    printf("Enter the number :");
    scanf("%d", &a);

    for (int i = 1; i <= a; i++)
    {
        total *= i;
    }

    printf("%d\n", total);

    printf("%d", factorial(a));
}

int factorial(int a)
{
    int total = 1;
    if (a > 1)
    {
        total = a * factorial(a - 1);
        return total;
    }

    return 1;
}