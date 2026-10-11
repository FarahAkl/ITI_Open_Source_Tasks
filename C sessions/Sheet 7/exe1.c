#include <stdio.h>

struct Student
{
    int code;
    char name[10];
    char gender;
    int age;
};

struct Student createStudent();
void printStudent(struct Student s);

void main()
{
    printf("===========First student=========== \n");
    struct Student s1 = createStudent();

    printf("===========Second student===========  : \n");
    struct Student s2 = createStudent();

    s1.age > s2.age
        ? printStudent(s1)
        : printStudent(s2);
}

struct Student createStudent()
{
    struct Student s;

    printf("Enter student code : ");
    scanf("%d", &s.code);
    printf("Enter student name : ");
    scanf("%9s", s.name);
    printf("Enter student gender : ");
    scanf(" %c", &s.gender);
    printf("Enter student age : ");
    scanf("%d", &s.age);

    return s;
}

void printStudent(struct Student s)
{

    printf("===========Student Data===========\n");

    char *gender = s.gender == 'f' || s.gender == 'F' ? "female" : s.gender == 'm' || s.gender == 'M' ? "male"
                                                                                                      : "Unknown gender";
    printf("Student Code = %d\n", s.code);
    printf("Student Name = %s\n", s.name);
    printf("Student age = %d\n", s.age);
    printf("Student gender = %s\n", gender);
}