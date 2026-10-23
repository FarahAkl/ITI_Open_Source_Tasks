
#include <iostream>
#include <limits>
#include "Admin.h"

using namespace std;

int main()
{
    Admin admin;
    admin.loadData();
    int choice;

    do
    {
        cout << "\n===== Examination Management System =====\n";
        cout << "1. Add Department\n";
        cout << "2. Display Departments\n";
        cout << "3. Add Subject\n";
        cout << "4. Display Subjects\n";
        cout << "5. Assign Subject to Department\n";
        cout << "6. Add Question\n";
        cout << "7. Display Questions\n";
        cout << "8. Add Exam\n";
        cout << "9. Display Exams\n";
        cout << "10. Add Student\n";
        cout << "11. Display Students\n";
        cout << "12. Add Reservation\n";
        cout << "13. Display Reservations\n";
        cout << "14. Start Quiz\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            admin.addDepartment();
            break;
        case 2:
            admin.displayDepartments();
            break;
        case 3:
            admin.addSubject();
            break;
        case 4:
            admin.displaySubjects();
            break;
        case 5:
            admin.assignSubjectToDepartment();
            break;
        case 6:
            admin.addQuestion();
            break;
        case 7:
            admin.displayQuestions();
            break;
        case 8:
            admin.addExam();
            break;
        case 9:
            admin.displayExams();
            break;
        case 10:
            admin.addStudent();
            break;
        case 11:
            admin.displayStudents();
            break;
        case 12:
            admin.addReservation();
            break;
        case 13:
            admin.displayReservations();
            break;
        case 14:
            admin.startQuiz();
            break;
        case 0:
            admin.saveData();
            cout << "Exiting the system...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
