#include <stdio.h>

void main(void)
{
    int size;
    int max = 0;
    printf("Enter the size :");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the array : ");

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    printf("Max value = %d", max);
}