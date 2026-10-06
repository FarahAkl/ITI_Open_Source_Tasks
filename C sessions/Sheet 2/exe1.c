#include <stdio.h>

void main(void)
{
    float num1;

    printf("Enter the number : ");
    scanf("%f", &num1);

    if (num1 > 0)
    {
        printf("Positive");
    }
    else if (num1 < 0)
    {
        printf("Negative");
    }
    else
    {
        printf("Zero");
    }
}