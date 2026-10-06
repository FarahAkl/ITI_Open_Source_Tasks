#include <stdio.h>

void main(void)
{
    float num1, num2, area;

    printf("Enter the two edges size : ");
    scanf("%f\n %f", &num1, &num2);

    area = num1 * num2;

    printf("The area of rectangle = %.2f", area);
}