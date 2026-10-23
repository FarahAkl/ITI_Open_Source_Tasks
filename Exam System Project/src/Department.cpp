#include "Department.h"
#include <iostream>

Department::Department(string name)
    : departmentName(name)
{
}

string Department::getName() const
{
    return departmentName;
}

void Department::addSubject(string subjectName)
{
    subjectNames.push_back(subjectName);
}

bool Department::hasSubject(const string &subjectName) const
{
    for (const string &subject : subjectNames)
    {
        if (subject == subjectName)
            return true;
    }

    return false;
}

void Department::displaySubjects() const
{
    cout << "\nDepartment: " << departmentName << endl;

    if (subjectNames.empty())
    {
        cout << "No subjects assigned.\n";
        return;
    }

    for (const string &subject : subjectNames)
        cout << "- " << subject << endl;
}

const vector<string> &Department::getSubjects() const
{
    return subjectNames;
}