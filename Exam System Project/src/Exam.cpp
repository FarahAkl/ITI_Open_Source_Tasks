
#include "Exam.h"
#include <iostream>

Exam::Exam(string name, int duration)
    : examName(name),
      durationMinutes(duration)
{
}

string Exam::getName() const
{
    return examName;
}

int Exam::getDuration() const
{
    return durationMinutes;
}

void Exam::addDetail(const ExamDetail &detail)
{
    details.push_back(detail);
}

const vector<ExamDetail> &Exam::getDetails() const
{
    return details;
}

int Exam::getTotalQuestions() const
{
    int total = 0;

    for (const ExamDetail &detail : details)
    {
        total += detail.getQuestionCount();
    }

    return total;
}

int Exam::getTotalMarks() const
{
    int total = 0;

    for (const ExamDetail &detail : details)
    {
        total += detail.getMarks();
    }

    return total;
}

void Exam::display() const
{
    cout << "\nExam: " << examName << '\n';
    cout << "Duration: " << durationMinutes << " minutes\n";
    cout << "Total Questions: " << getTotalQuestions() << '\n';
    cout << "Total Marks: " << getTotalMarks() << '\n';

    cout << "\nExam Details:\n";

    for (const ExamDetail &detail : details)
    {
        detail.display();
        cout << "--------------------\n";
    }
}

Exam &Exam::operator+=(const ExamDetail &detail)
{
    addDetail(detail);
    return *this;
}
