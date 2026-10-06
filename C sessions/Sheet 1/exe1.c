#include <stdio.h>

void main(void)
{
    float num, area;
    printf("Enter the edge size : ");
    scanf("%f", &num);

    area = num * num;

    printf("The area of square = %.2f", area);
}