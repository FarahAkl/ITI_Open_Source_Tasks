#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Question.h"

using namespace std;

class Subject
{
private:
    string subjectName;
    vector<unique_ptr<Question>> questions;

public:
    Subject(string name);

    string getName() const;

    bool hasQuestions() const;

    bool startQuiz() const;

    void addQuestion(unique_ptr<Question> question);

    void displayQuestions() const;

    int getQuestionsCount() const;

    const vector<unique_ptr<Question>> &getQuestions() const;
};