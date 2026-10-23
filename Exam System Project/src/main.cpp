#include <iostream>
#include "Admin.h"

using namespace std;

int main()
{
    Admin admin;

    cout << "=== Examination Management System ===\n\n";

    admin.addDepartment();
    admin.addSubject();
    admin.assignSubjectToDepartment();

    admin.addQuestion();

    admin.addExam();
    admin.displayExams();
    admin.startExam();

    return 0;
}