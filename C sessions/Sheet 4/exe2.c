#include <stdio.h>
#include <math.h>

void isPrime(int num, int i);
void main(void)
{
    int num, remain;
    printf("Enter the number :");
    scanf("%d", &num);

    //    Iterative Way

    if (num > 2)
    {
        for (int i = 2; i < num; i++)
        {
            remain = num % i;
            if (remain == 0)
            {
                printf("%d is not prime", num);
                break;
            }
            else if (i == num - 1)
            {
                printf("%d is prime", num);
            }
        }
    }
    else
    {
        printf("%d is prime", num);
    }

    isPrime(num, 2);
}

void isPrime(int num, int i)
{
    int remain;
    if (num < 2)
    {
        printf("\n%d is not prime", num);
    }
    else if (i < num)
    {
        remain = num % i;
        if (remain == 0)
        {
            printf("\n%d is not prime", num);
        }
        else
        {
            isPrime(num, i + 1);
        }
    }
    else
    {
        printf("\n%d is prime", num);
    }
}