#include <stdio.h>

void main(void)
{
    int size, min;
    printf("Enter the size :");
    scanf("%d", &size);

    printf("Enter the numbers :");

    for (int i = 0; i < size; i++)
    {
        int num;
        scanf("%d", &num);
        if (i == 0)
        {
            min = num;
        }
        else if (num < min)
        {
            min = num;
        }
    }

    printf("The minimum number = %d", min);
}