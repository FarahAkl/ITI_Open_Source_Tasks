#include <stdio.h>

void main(void)
{
    float area, r;

    const float pi = 3.14;

    printf("Enter the radius : ");
    scanf("%f", &r);

    area = 2 * pi * r * r;

    printf("\nThe area of circle = %.2f", area);
}