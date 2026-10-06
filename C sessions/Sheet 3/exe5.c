#include <stdio.h>

void main(void)
{
    int size, min, max, temp_min, temp_max;
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
            max = num;
            temp_min = num;
            temp_max = num;
        }
        else if (num < min)
        {
            temp_min = min;
            min = num;
        }
        else if (num < temp_min || temp_min == min)
        {
            temp_min = num;
        }
        if (num > max)
        {
            temp_max = max;
            max = num;
        }
        else if (num > temp_max || temp_max == max)
        {
            temp_max = num;
        }
    }

    printf("The range of the numbers without the extremes = [%d , %d]", temp_min, temp_max);
}