#include <stdio.h>
#include <stdlib.h>

void main()
{
    FILE *file = fopen("students.txt", "w");

    if (file == NULL)
    {
        printf("Error with opening file");
        exit(10);
    }

    char names[5][100];

    for (int i = 0; i < 5; i++)
    {
        printf("Enter student %d name: ", i + 1);
        scanf("%99s", names[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        fprintf(file, "%s\n", names[i]);
    }

    fclose(file);

    printf("Student names saved successfully.\n");
}