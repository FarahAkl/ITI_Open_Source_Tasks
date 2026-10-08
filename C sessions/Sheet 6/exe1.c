#include <stdio.h>

void main()
{
    int a, b;
    int *p1 = &a;
    int *p2 = &b;

    printf("Enter first number : ");
    scanf("%d", p1);

    printf("Enter second number : ");
    scanf("%d", p2);

    printf("The sum = %d", *p1 + *p2);
}