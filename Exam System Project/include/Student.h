
#pragma once
#include <string>
using namespace std;

class Student
{
private:
    int id;
    string name;
    string username;
    string password;

public:
    Student(int studentId, string studentName, string studentUsername, string studentPassword);

    int getId() const;
    string getName() const;
    string getUsername() const;
    string getPassword() const;
    
    bool checkLogin(const string &enteredUsername, const string &enteredPassword) const;
    void display() const;
};
