#include <stdio.h>

void main(void)
{
    int size, value;

    printf("Enter the size :");
    scanf("%d", &size);

    int index = size;
    int arr[size + 1];

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

    printf("Enter the new value : ");
    scanf("%d", &value);

    for (int i = 0; i < size; i++)
    {
        if (value <= arr[i])
        {
            index = i;
            break;
        }
    }

    for (int i = size; i >= index; i--)
    {
        arr[i] = arr[i - 1];
    }

    arr[index] = value;

    for (int i = 0; i < size + 1; i++)
    {
        printf("%d ", arr[i]);
    }
}