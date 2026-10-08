#include <stdio.h>

void main()
{
    char temp;
    char str[100];
    char *p1 = str;
    char *p2 = str;
    int size = 0;

    printf("Enter the string : ");
    scanf("%s", p1);

    while (*p1 != '\0')
    {
        size++;
        p1++;
    }
    p1 = str;

    for (int i = 0; i < size / 2; i++)
    {
        temp = *(p1 + i);
        *(p1 + i) = *(p2 + size - 1 - i);
        *(p2 + size - 1 - i) = temp;
    }

    printf("The reversed word : ");
    for (int i = 0; i < size; i++)
    {
        printf("%c", *(p1 + i));
    }
}