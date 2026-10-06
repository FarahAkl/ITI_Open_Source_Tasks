#include <stdio.h>

void main(void)
{
    float num1, num2, area, r, sum;

    printf("Enter the base and the height : ");
    scanf("%f\n %f", &num1, &num2);

    area = 0.5 * num1 * num2;

    printf("The area of triangle = %.2f", area);
}