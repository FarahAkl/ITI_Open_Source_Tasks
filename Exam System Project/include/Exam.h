#pragma once

#include <string>
#include <vector>
#include "ExamDetail.h"

using namespace std;

class Exam
{
private:
    string examName;
    int durationMinutes;
    vector<ExamDetail> details;

public:
    Exam(string name, int duration);

    string getName() const;
    int getDuration() const;

    void addDetail(const ExamDetail &detail);

    const vector<ExamDetail> &getDetails() const;

    int getTotalQuestions() const;
    int getTotalMarks() const;

    void display() const;

    Exam &operator+=(const ExamDetail &detail);
};
