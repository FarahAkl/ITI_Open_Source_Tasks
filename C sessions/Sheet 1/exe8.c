#include <stdio.h>

void main(void)
{
    int num;
    printf("Enter the number : ");
    scanf("%d", &num);

    int amount = (num / 50);
    printf("\nAmount of 50 = %d\n", amount);
    num = num % 50;
    amount += num / 25;
    printf("Amount of 25 = %d\n", num / 25);

    num = num % 25;
    amount += num / 10;
    printf("Amount of 10 = %d\n", num / 10);

    num = num % 10;
    amount += num / 5;
    printf("Amount of 5 = %d\n", num / 5);

    num = num % 5;
    amount += num;
    printf("Amount of 1 = %d\n", num);

    printf("Total Amount = %d", amount);
}