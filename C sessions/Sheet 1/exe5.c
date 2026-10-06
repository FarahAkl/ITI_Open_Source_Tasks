#include <stdio.h>

void main(void)
{
    float num1, num2, sum;

    printf("Enter the two numbers : ");
    scanf("%f\n %f", &num1, &num2);

    sum = num1 + num2;

    printf("The sum of two numbers = %.2f", sum);
}