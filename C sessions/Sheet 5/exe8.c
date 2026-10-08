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

    printf("Array = ");
    for (int i = 0; i < size ; i++)
    {
        printf("%d ", arr[i]);
    }
}