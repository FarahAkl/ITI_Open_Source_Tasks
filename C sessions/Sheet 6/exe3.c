#include <stdio.h>

void main()
{
    int length = 0;
    char str[100] = "";
    char *p = str;
    printf("Enter your string : ");
    scanf("%s", p);

    while (*p != '\0')
    {
        length++;
        p++;
    }

    printf("The length of the string = %d", length);
}