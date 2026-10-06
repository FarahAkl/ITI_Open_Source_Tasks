#include <stdio.h>

void main(void)
{
    int num1;

    printf("Enter the number : ");
    scanf("%f", &num1);

    printf(num1 % 2 == 0 ? "Even" : "Odd");
}