#pragma once

#include <vector>
#include "Subject.h"
#include "Department.h"
#include "Exam.h"
#include "Student.h"
#include "Reservation.h"

using namespace std;

class Admin
{
private:
    vector<Subject> subjects;
    vector<Department> departments;
    vector<Exam> exams;
    vector<Student> students;
    vector<Reservation> reservations;

public:
    void addExam();
    void displayExams() const;

    void assignSubjectToDepartment();
    void addDepartment();
    void displayDepartments() const;
    void displayDepartmentSubjects() const;

    void addSubject();
    void displaySubjects() const;

    void displayQuestions() const;
    void startQuiz() const;
    void addQuestion();
    void startExam();

    void addStudent();
    void displayStudents() const;

    void addReservation();
    void displayReservations() const;
};
