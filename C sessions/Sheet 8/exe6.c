#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int id;
    char name[50];
    float gpa;
};

void main(void)
{
    FILE *file = fopen("students.dat", "r+b");

    if (file == NULL)
    {
        printf("Error opening file");
        exit(10);
    }

    int id, found = 0;
    float newGPA;
    struct Student s;

    printf("Enter student ID: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(struct Student), 1, file) == 1)
    {
        if (s.id == id)
        {
            printf("Student found: %s\n", s.name);
            printf("Current GPA: %.2f\n", s.gpa);

            printf("Enter new GPA: ");
            scanf("%f", &newGPA);

            s.gpa = newGPA;

            fseek(file, -(long)sizeof(struct Student), SEEK_CUR);

            if (fwrite(&s, sizeof(struct Student), 1, file) == 1)
            {
                printf("GPA updated successfully.\n");
            }
            else
            {
                printf("Error updating GPA.\n");
            }

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Student ID not found.\n");
    }

    fclose(file);
}
