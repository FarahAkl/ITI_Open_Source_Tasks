#include <stdio.h>

void main(void)
{
    int size;
    printf("Enter the size :");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the array : ");

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("The sorted array = ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}