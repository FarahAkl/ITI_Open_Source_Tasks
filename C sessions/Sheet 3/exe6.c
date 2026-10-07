#include <stdio.h>
#include <math.h>

void main(void)
{
    int base, num, power, divisor, digit;

    printf("Enter the base : ");
    scanf("%d", &base);

    printf("Enter the number : ");
    scanf("%d", &num);

    if (base >= 2 && base <= 9)
    {
        if (num == 0)
        {
            printf("0");
        }
        else
        {
            power = (int)(log(num) / log(base));
            divisor = (int)pow(base, power);

            while (divisor != 0)
            {
                digit = num / divisor;
                printf("%d", digit);

                num %= divisor;
                divisor /= base;
            }
        }
    }
    else
    {
        printf("The base must be between 2 and 9");
    }
}