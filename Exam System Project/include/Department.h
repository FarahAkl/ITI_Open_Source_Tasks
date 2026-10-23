#pragma once

#include <string>
#include <vector>

using namespace std;

class Department
{
private:
    string departmentName;
    vector<string> subjectNames;

public:
    Department(string name);

    string getName() const;

    const vector<string> &getSubjects() const;

    void addSubject(string subjectName);

    bool hasSubject(const string &subjectName) const;

    void displaySubjects() const;
};