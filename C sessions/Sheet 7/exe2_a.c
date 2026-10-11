#include <stdio.h>
#include <string.h>

struct student
{
    char id_num[5];
    char name[10];
    char gender;
    int age;
};

struct student createStudent();
void printStudent(struct student s);

void main()
{
    struct student stds[100];
    int num_of_stds;

    printf("Number of students <100 : ");
    scanf("%d", &num_of_stds);

    if (num_of_stds < 1 || num_of_stds > 100)
    {
        printf("Invalid number of students");
        return;
    }

    for (int i = 0; i < num_of_stds; i++)
    {
        stds[i] = createStudent();
        printf("------------------------------------------------\n");
    }

    for (int i = 0; i < num_of_stds - 1; i++)
    {
        for (int j = 0; j < num_of_stds - 1 - i; j++)
        {
            if (strcmp(stds[j].name, stds[j + 1].name) > 0)
            {
                struct student temp = stds[j];
                stds[j] = stds[j + 1];
                stds[j + 1] = temp;
            }
        }
    }

    printf("\n%-10s %-12s %-10s %-8s\n",
           "ID", "Name", "Gender", "Age");

    printf("------------------------------------------------\n");
    for (int i = 0; i < num_of_stds; i++)
    {
        printStudent(stds[i]);
    }
}

struct student createStudent()
{
    struct student s;
    static int counter = 0;

    printf("Enter student id : ");
    scanf("%5s", s.id_num);
    printf("Enter student name : ");
    scanf("%9s", s.name);
    printf("Enter student gender : ");
    scanf(" %c", &s.gender);
    printf("Enter student age : ");
    scanf("%d", &s.age);

    printf("======================================");
    counter++;

    return s;
}

void printStudent(struct student s)
{
    char *gender = s.gender == 'f' || s.gender == 'F' ? "Female" : s.gender == 'm' || s.gender == 'M' ? "Male"
                                                                                                      : "Unknown";

    printf("%-10s %-12s %-10s %-8d\n",
           s.id_num, s.name, gender, s.age);
}