#include <stdio.h>

void main(void)
{
    int size, max;
    printf("Enter the size :");
    scanf("%d", &size);

    printf("Enter the numbers :");

    for (int i = 0; i < size; i++)
    {
        int num;
        scanf("%d", &num);
        if (i == 0)
        {
            max = num;
        }
        else if (num > max)
        {
            max = num;
        }
    }

    printf("The maximum number = %d", max);
}