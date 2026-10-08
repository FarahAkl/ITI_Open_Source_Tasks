#include <stdio.h>

int binary_search(int arr[], int l, int h, int value);
void main(void)
{
    int size, value;
    printf("Enter the size :");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the array : ");

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the value : ");
    scanf("%d", &value);

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

    int position = binary_search(arr, 0, size - 1, value);

    printf("The position of %d : %d", value, position == -1 ? position : position + 1);
}

int binary_search(int arr[], int l, int h, int value)
{
    if (l > h)
    {
        return -1;
    }

    int mid = (l + h + 1) / 2;

    if (value == arr[l])
    {
        return l;
    }
    else if (value == arr[h])
    {
        return h;
    }
    else if (value == arr[mid])
    {
        return mid;
    }
    else if (value > arr[mid])
    {
        return binary_search(arr, mid + 1, h, value);
    }
    else if (value < arr[mid])
    {
        return binary_search(arr, l, mid - 1, value);
    }
    else
    {
        return -1;
    }
}