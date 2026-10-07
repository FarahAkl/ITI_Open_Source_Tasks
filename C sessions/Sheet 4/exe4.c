#include <stdio.h>

int power(int a, int b);
void main(void)
{
    int a, b;
    int total = 1;
    printf("Enter the number :");
    scanf("%d", &a);

    printf("Enter the power :");
    scanf("%d", &b);

    for (int i = 1; i <= b; i++)
    {
        total *= a;
    }

    printf("%d\n", total);

    printf("%d", power(a, b));
}

int power(int a, int b)
{
    int total = 1;
    if (b > 1)
    {
        total = a * power(a, b - 1);
        return total;
    }

    return a;
}