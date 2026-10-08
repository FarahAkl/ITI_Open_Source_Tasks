#include <stdio.h>

int total(int arr[], int size, int index);
void main(void)
{
    int size;
    int sum = 0;
    printf("Enter the size :");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the array : ");

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }

    printf("Total = %d\n", sum);

    int func_total = total(arr, size, 0);

    printf("Total = %d", func_total);
}

int total(int arr[], int size, int index)
{
    if (size != index)
    {
        return arr[index] + total(arr, size, index + 1);
    }

    return 0;
}