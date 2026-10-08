#include <stdio.h>

void main()
{
    int size;
    printf("Enter the size of the array : ");
    scanf("%d", &size);

    int arr[size];
    int *p = arr;

    printf("Enter array's elements : ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", p + i);
    }

    printf("Array = ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *(p + i));
    }
}