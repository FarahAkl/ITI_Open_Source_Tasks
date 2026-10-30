#include "ExamDetail.h"
#include "ExamException.h"
#include <iostream>
#include <stdexcept>

ExamDetail::ExamDetail(string subject, string section, int count, int marks)
    : subjectName(subject),
      sectionName(section),
      questionCount(count),
      marks(marks)
{
    if (subjectName.empty() || sectionName.empty() || questionCount <= 0 || marks <= 0)
        throw ExamException("An exam section requires names, questions, and positive marks.");
}

string ExamDetail::getSubjectName() const
{
    return subjectName;
}

string ExamDetail::getSectionName() const
{
    return sectionName;
}

int ExamDetail::getQuestionCount() const
{
    return questionCount;
}

int ExamDetail::getMarks() const
{
    return marks;
}

void ExamDetail::display() const
{
    cout << "Subject: " << subjectName << '\n';
    cout << "Section: " << sectionName << '\n';
    cout << "Number of Questions: " << questionCount << '\n';
    cout << "Marks: " << marks << '\n';
}
