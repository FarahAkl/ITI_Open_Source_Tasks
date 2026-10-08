#include <stdio.h>

void main(void)
{
    int size, value, index;
    printf("Enter the size :");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the array : ");

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the value :");
    scanf("%d", &value);

    for (int i = 0; i < size; i++)
    {
        if (value == arr[i])
        {
            index = i;
            break;
        }
        else
        {
            index = -1;
        }
    }

    printf("The position of the value = %d", index == -1 ? index : index + 1);
}