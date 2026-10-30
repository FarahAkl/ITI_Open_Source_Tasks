#pragma once

#include <string>
using namespace std;

class ExamDetail
{
private:
    string subjectName;
    string sectionName;
    int questionCount;
    int marks;

public:
    ExamDetail(string subject, string section, int count, int marks);

    string getSubjectName() const;
    string getSectionName() const;
    int getQuestionCount() const;
    int getMarks() const;

    void display() const;
};
