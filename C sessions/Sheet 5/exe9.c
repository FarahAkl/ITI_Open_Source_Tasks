#include <stdio.h>

void main(void)
{
    int size1, size2;

    printf("Enter the first array's size :");
    scanf("%d", &size1);

    int arr1[size1];

    printf("Enter the first array : ");

    for (int i = 0; i < size1; i++)
    {
        scanf("%d", &arr1[i]);
    }

    printf("Enter the second array's size :");
    scanf("%d", &size2);
    int arr2[size2];

    for (int i = 0; i < size2; i++)
    {
        scanf("%d", &arr2[i]);
    }

    int arr3[size1 + size2];

    for (int i = 0; i < size1; i++)
    {
        arr3[i] = arr1[i];
    }

    for (int i = 0; i < size2; i++)
    {
        arr3[i + size1] = arr2[i];
    }

    printf("Merged Array = ");
    for (int i = 0; i < size1 + size2; i++)
    {
        printf("%d ", arr3[i]);
    }
}