#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *next;
};

struct Node *top = NULL;

void push(int value);
void pop();
void main()
{
    push(5);
    push(10);
    push(4);

    pop();
}

void push(int value)
{
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->value = value;
    newNode->next = top;

    top = newNode;
}

void pop()
{
    if (top == NULL)
    {
        printf("Stack is empty");
        return;
    }

    struct Node *temp = top;
    top = top->next;

    printf("Removed value = %d", temp->value);
}