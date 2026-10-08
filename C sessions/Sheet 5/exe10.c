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

    for (int i = 0; i < size / 2; i++)
    {
        int temp;
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }

    printf("The reversed array = ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}