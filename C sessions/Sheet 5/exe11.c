#include <stdio.h>

void main(void)
{
    int size;
    printf("Enter the size :");
    scanf("%d", &size);

    int odd_size, even_size;

    if (size % 2 == 0)
    {
        odd_size = size / 2;
        even_size = size / 2;
    }
    else
    {
        odd_size = size / 2 + 1;
        even_size = size / 2;
    }

    int arr[size], even_arr[even_size], odd_arr[odd_size];

    printf("Enter the array : ");

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
        if (i % 2 != 0)
        {
            even_arr[i / 2] = arr[i];
        }
        else
        {
            odd_arr[i / 2] = arr[i];
        }
    }

    printf("The odd elements array : ");
    for (int i = 0; i < odd_size; i++)
    {
        printf("%d ", odd_arr[i]);
    }

    printf("\nThe even elements array : ");
    for (int i = 0; i < even_size; i++)
    {
        printf("%d ", even_arr[i]);
    }
}