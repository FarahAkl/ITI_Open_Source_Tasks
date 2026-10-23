
#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(int studentId, string studentName, string studentUsername, string studentPassword)
    : id(studentId),
      name(studentName),
      username(studentUsername),
      password(studentPassword) {}

int Student::getId() const
{
    return id;
}

string Student::getName() const
{
    return name;
}

string Student::getUsername() const
{
    return username;
}

bool Student::checkLogin(const string &enteredUsername, const string &enteredPassword) const
{
    return username == enteredUsername && password == enteredPassword;
}

void Student::display() const
{
    cout << "ID: " << id
         << " | Name: " << name
         << " | Username: " << username << '\n';
}
