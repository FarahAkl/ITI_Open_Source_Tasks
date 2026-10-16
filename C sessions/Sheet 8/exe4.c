#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    FILE *file1 = fopen("file1.txt", "r");
    FILE *file2 = fopen("file2.txt", "r");
    FILE *merged = fopen("merged.txt", "w");

    if (file1 == NULL || file2 == NULL || merged == NULL)
    {
        printf("Error opening files");
        if (file1 != NULL)
            fclose(file1);
        if (file2 != NULL)
            fclose(file2);
        if (merged != NULL)
            fclose(merged);
        exit(10);
    }

    int num1, num2;
    int has1 = fscanf(file1, "%d", &num1) == 1;
    int has2 = fscanf(file2, "%d", &num2) == 1;

    while (has1 && has2)
    {
        if (num1 <= num2)
        {
            fprintf(merged, "%d ", num1);
            has1 = fscanf(file1, "%d", &num1) == 1;
        }
        else
        {
            fprintf(merged, "%d ", num2);
            has2 = fscanf(file2, "%d", &num2) == 1;
        }
    }

    while (has1)
    {
        fprintf(merged, "%d ", num1);
        has1 = fscanf(file1, "%d", &num1) == 1;
    }

    while (has2)
    {
        fprintf(merged, "%d ", num2);
        has2 = fscanf(file2, "%d", &num2) == 1;
    }

    fclose(file1);
    fclose(file2);
    fclose(merged);

    printf("Files merged successfully.\n");

}
