#include <stdio.h>
#include <stdlib.h>

int size;
int top = -1;

void push(int *arr, int value);
void pop(int *arr);
void main()
{
    printf("Enter the size of the array : ");
    scanf("%d", &size);

    int *arr = malloc(size * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed");
        exit(10);
    }
}

void push(int *arr, int value)
{
    if (top == size - 1)
    {
        printf("Stack overflow");
    }
    else
    {
        top++;
        arr[top] = value;
    }
}

void pop(int *arr)
{
    if (top == -1)
    {
        printf("Stack is empty");
    }
    else
    {
        printf("Removed value = %d\n", arr[top]);
        top--;
    }
}