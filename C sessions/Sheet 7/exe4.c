#include <stdio.h>

struct Student
{
    int roll_num;
    char name[10];
    int age;
};
int size;

void addStud(struct Student *newStudent);
void filterByAge(struct Student studArr[], int age);
void searchByRollNum(struct Student studArr[], int roll_num);
void main()
{
    printf("Enter the number of students : ");
    scanf("%d", &size);

    struct Student studArr[size];

    for (int i = 0; i < size; i++)
        addStud(&studArr[i]);

    filterByAge(studArr, 20);
    searchByRollNum(studArr, 4);
}

void addStud(struct Student *newStudent)
{
    printf("Enter the roll n. : ");
    scanf("%d", &newStudent->roll_num);

    printf("Enter the student name : ");
    scanf("%9s", newStudent->name);

    printf("Enter the age : ");
    scanf("%d", &newStudent->age);

    printf("=======================================\n");
}

void filterByAge(struct Student studArr[], int age)
{
    for (int i = 0; i < size; i++)
    {
        if (studArr[i].age < age)
            printf("%s\n", studArr[i].name);
    }
}

void searchByRollNum(struct Student s[], int roll_num)
{
    struct Student *temp = NULL;

    for (int i = 0; i < size; i++)
    {
        if (s[i].roll_num == roll_num)
            temp = &s[i];
    }

    if (temp != NULL)
    {
        printf("%-12d %-12s %-5d\n", temp->roll_num, temp->name, temp->age);
    }
    else
    {
        printf("There is no student with this roll number");
    }
}