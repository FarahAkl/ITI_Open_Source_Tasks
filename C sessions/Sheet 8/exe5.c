
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
    struct Student students[5];

    FILE *file = fopen("students.dat", "wb");

    if (file == NULL)
    {
        printf("Error opening file");
        exit(10);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("Enter student %d ID: ", i + 1);
        scanf("%d", &students[i].id);

        printf("Enter student name: ");
        scanf(" %49[^\n]", students[i].name);

        printf("Enter student GPA: ");
        scanf("%f", &students[i].gpa);
    }

    fwrite(students, sizeof(struct Student), 5, file);
    fclose(file);

    file = fopen("students.dat", "rb");

    if (file == NULL)
    {
        printf("Error reading file");
        exit(10);
    }

    struct Student s;

    printf("\n%-10s %-25s %-10s\n", "ID", "Name", "GPA");
    printf("------------------------------------------------\n");

    while (fread(&s, sizeof(struct Student), 1, file) == 1)
    {
        printf("%-10d %-25s %-10.2f\n", s.id, s.name, s.gpa);
    }

    fclose(file);
}
