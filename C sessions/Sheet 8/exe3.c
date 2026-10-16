#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    FILE *file = fopen("employees.txt", "a");

    if (file == NULL)
    {
        printf("Error opening file");
        exit(10);
    }

    char name[100];

    while (1)
    {
        printf("Enter employee name (END to stop): ");
        scanf(" %99[^\n]", name);

        if (strcmp(name, "END") == 0)
            break;

        fprintf(file, "%s\n", name);
    }

    fclose(file);

    file = fopen("employees.txt", "r");

    if (file == NULL)
    {
        printf("Error reading file");
        exit(10);
    }

    printf("\nEmployees file contents:\n");

    while (fgets(name, sizeof(name), file) != NULL)
    {
        printf("%s", name);
    }

    fclose(file);
}