#include <stdio.h>

int size;
int top = -1;

void push(int arr[], int value);
void pop(int arr[]);
void main()
{
    printf("Enter the size of the array : ");
    scanf("%d", &size);

    int arr[size];
}

void push(int arr[], int value)
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

void pop(int arr[])
{
    if (top == -1)
    {
        printf("Stack is empty");
    }
    else
    {
        printf("Removed value = %d", arr[top]);
        top--;
    }
}