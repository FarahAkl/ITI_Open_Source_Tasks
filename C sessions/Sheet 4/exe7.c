#include <stdio.h>
#include <stdbool.h>

int factorial(int a);
float power(float a, int b);

void main(void)
{
    int a;
    float total = 0;
    bool flag = false;
    float rad;
    const float pi = 3.14;

    printf("Enter the degree :");
    scanf("%d", &a);

    rad = a * pi / 180;

    for (int i = 1; i <= 15; i += 2)
    {
        if (!flag)
        {
            total += power(rad, i) / factorial(i);
            flag = !flag;
        }
        else
        {
            total -= power(rad, i) / factorial(i);
            flag = !flag;
        }
    }

    printf("%0.2f\n", total);
}

int factorial(int a)
{
    int total = 1;
    if (a > 1)
    {
        total = a * factorial(a - 1);
        return total;
    }

    return a;
}

float power(float a, int b)
{
    float total = 1;
    if (b > 1)
    {
        total = a * power(a, b - 1);
        return total;
    }

    return a;
}