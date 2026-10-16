#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void main()
{
    FILE *file = fopen("article.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file");
        exit(10);
    }

    int ch;
    int characters = 0;
    int words = 0;
    int lines = 0;
    int inWord = 0;
    int hasContent = 0;
    int lastChar = '\0';

    while ((ch = fgetc(file)) != EOF)
    {
        characters++;
        hasContent = 1;
        lastChar = ch;

        if (ch == '\n')
            lines++;

        if (isspace((unsigned char)ch))
        {
            inWord = 0;
        }
        else if (!inWord)
        {
            words++;
            inWord = 1;
        }
    }

    if (hasContent && lastChar != '\n')
        lines++;

    fclose(file);

    printf("Total characters = %d\n", characters);
    printf("Total words = %d\n", words);
    printf("Total lines = %d\n", lines);
}