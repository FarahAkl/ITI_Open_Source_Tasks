#include <stdio.h>

void main()
{
    char str1[100], str2[100], str[200];
    char *p1 = str1;
    char *p2 = str2;
    int match = 1;
    int i = 0;

    printf("Enter the first string : ");
    scanf("%s", p1);

    printf("Enter the second string : ");
    scanf("%s", p2);

    while (*p1 != '\0' && *p2 != '\0')
    {
        if (*p1 != *p2)
        {
            match = 0;
            break;
        }

        p1++;
        p2++;
    }

    if (*p1 != '\0' || *p2 != '\0')
    {
        match = 0;
    }

    if (match)
    {
        printf("The two strings match");
    }
    else
    {
        printf("The two strings do not match");
    }
}
