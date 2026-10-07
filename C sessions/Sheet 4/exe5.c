#include <stdio.h>

int sumOfNaturals(int a);
void main(void)
{
    int a;
    int total = 0;
    printf("Enter the number :");
    scanf("%d", &a);

    for (int i = 1; i <= a; i++)
    {
        total += i;
    }

    printf("%d\n", total);

    printf("%d", sumOfNaturals(a));
}

int sumOfNaturals(int a)
{
    int total = 0;
    if (a > 0)
    {
        total = a + sumOfNaturals(a - 1);
        return total;
    }

    return 0;
}