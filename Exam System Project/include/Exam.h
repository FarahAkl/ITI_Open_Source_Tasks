#pragma once

#include <string>

using namespace std;

class Exam
{
private:
    string examName;
    string subjectName;
    int durationMinutes;

public:
    Exam(string name, string subject, int duration);

    string getName() const;

    string getSubjectName() const;

    int getDuration() const;

    void display() const;
};