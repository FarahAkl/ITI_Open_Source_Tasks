#include "Exam.h"
#include <iostream>

Exam::Exam(string name, string subject, int duration)
    : examName(name),
      subjectName(subject),
      durationMinutes(duration)
{
}

string Exam::getName() const
{
    return examName;
}

string Exam::getSubjectName() const
{
    return subjectName;
}

int Exam::getDuration() const
{
    return durationMinutes;
}

void Exam::display() const
{
    cout << "Exam: " << examName << endl;
    cout << "Subject: " << subjectName << endl;
    cout << "Duration: " << durationMinutes
         << " minutes" << endl;
}