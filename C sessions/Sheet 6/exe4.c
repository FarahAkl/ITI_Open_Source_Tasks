#include <stdio.h>

void swap(int *p1, int *p2);

void main()
{
    int a, b;

    printf("Enter first number : ");
    scanf("%d", &a);

    printf("Enter second number : ");
    scanf("%d", &b);

    swap(&a, &b);
}

void swap(int *p1, int *p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;

    printf("Numbers after swaping : %d , %d", *p1, *p2);
}