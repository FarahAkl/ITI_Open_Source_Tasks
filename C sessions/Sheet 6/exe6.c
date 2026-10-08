#include <stdio.h>

void main()
{
    char str1[100], str2[100], str[200];
    char *p1 = str1;
    char *p2 = str2;
    int i = 0;

    printf("Enter the first string : ");
    scanf("%s", p1);

    printf("Enter the second string : ");
    scanf("%s", p2);

    while (*p1 != '\0')
    {
        str[i] = *(p1);
        i++;
        p1++;
    }
    while (*p2 != '\0')
    {
        str[i] = *(p2);
        i++;
        p2++;
    }

    printf("The concatenated string : ");
    for (int j = 0; j < i; j++)
    {
        printf("%c", str[j]);
    }
}