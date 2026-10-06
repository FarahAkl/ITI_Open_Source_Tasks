#include <stdio.h>

void main(void)
{
    int size, total;
    float average;
    printf("Enter the size :");
    scanf("%d", &size);

    printf("Enter the numbers :");

    for (int i = 0; i < size; i++)
    {
        int num;
        scanf("%d", &num);
        if (i == 0)
        {
            total = num;
        }else{
            total += num;
        }
    }

    average = (float)total / size;

    printf("The average of numbers = %0.2f", average);
}