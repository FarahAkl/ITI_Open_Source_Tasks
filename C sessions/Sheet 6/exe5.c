#include <stdio.h>
#include <stdlib.h>

void main()
{
    int size, max;

    printf("Enter the size: ");
    scanf("%d", &size);

    int *arr = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        scanf("%d", arr + i);

        if (i == 0)
        {
            max = *(arr + i);
        }
        else if (*(arr + i) > max)
        {
            max = *(arr + i);
        }
    }

    printf("Maximum value = %d", max);
    free(arr);
}