
#include "Exam.h"
#include "ExamException.h"
#include <iostream>
#include <stdexcept>

Exam::Exam(string name, int duration)
    : examName(name),
      durationMinutes(duration)
{
    if (examName.empty() || durationMinutes <= 0)
        throw ExamException("Exam name and a positive duration are required.");
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
    for (const ExamDetail &existing : details)
        if (existing.getSubjectName() == detail.getSubjectName() &&
            existing.getSectionName() == detail.getSectionName())
            throw ExamException("An exam cannot contain the same section twice.");
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

ostream &operator<<(ostream &output, const Exam &exam)
{
    output << "Exam: " << exam.examName << '\n'
           << "Duration: " << exam.durationMinutes << " minutes\n"
           << "Total Questions: " << exam.getTotalQuestions() << '\n'
           << "Total Marks: " << exam.getTotalMarks() << '\n';
    for (const ExamDetail &detail : exam.details)
        output << detail.getSubjectName() << " / " << detail.getSectionName()
               << ": " << detail.getQuestionCount() << " questions, "
               << detail.getMarks() << " marks\n";
    return output;
}
