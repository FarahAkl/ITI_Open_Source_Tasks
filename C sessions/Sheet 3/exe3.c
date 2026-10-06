#include <stdio.h>

void main(void)
{
    int size;
    float min, max;
    printf("Enter the size :");
    scanf("%d", &size);

    printf("Enter the numbers :");

    for (int i = 0; i < size; i++)
    {
        float num;
        scanf("%f", &num);
        if (i == 0)
        {
            min = num;
            max = num;
        }
        else if (num < min)
        {
            min = num;
        }
        else if (num > max)
        {
            max = num;
        }
    }

    printf("The range of the numbers = [%0.2f , %0.2f]", min, max);
}