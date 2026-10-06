#include <stdio.h>

void main(void)
{
    float num1;

    printf("Enter the number : ");
    scanf("%f", &num1);

    printf(num1 == 0 ? "Zero" : num1 > 0 ? "Positive"
                                         : "Negative");
}