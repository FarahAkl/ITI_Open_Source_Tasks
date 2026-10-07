#include <stdio.h>
#include <math.h>

void decToBin(int num);
void main(void)
{
    int num, power, divisor, digit;
    printf("Enter the number :");
    scanf("%d", &num);

    //    Iterative Way

    if (num == 0)
    {
        printf("0");
    }
    else
    {
        power = (int)(log(num) / log(2));
        divisor = (int)pow(2, power);

        while (divisor != 0)
        {
            digit = num / divisor;
            printf("%d", digit);

            num %= divisor;
            divisor /= 2;
        }
    }

    decToBin(num);
}

void decToBin(int num)
{
    if (num > 1)
    {
        decToBin(num / 2);
    }

    printf("%d", num % 2);
}