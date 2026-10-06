#include <stdio.h>

void main(void)
{
    float num1;

    printf("Enter the number : ");
    scanf("%f", &num1);

    if (num1 >= 90)
    {
        printf("Excellent");
    }
    else if (num1 >= 80)
    {
        printf("Very good");
    }
    else if (num1 >= 65)
    {
        printf("good");
    }
    else if (num1 >= 50)
    {
        printf("pass");
    }
    else
    {
        printf("fail");
    }
}