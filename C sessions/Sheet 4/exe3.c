#include <stdio.h>

void swapNumbers(int a, int b);
void main(void)
{
    int a, b;
    printf("Enter the number :");
    scanf("%d %d", &a, &b);

    swapNumbers(a, b);
}

void swapNumbers(int a, int b)
{
    int temp = b;
    b = a;
    a = temp;

    printf("The swapped number : %d %d", a, b);
}