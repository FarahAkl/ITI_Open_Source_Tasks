#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Question.h"

using namespace std;

class Section
{
private:
    string sectionName;
    vector<unique_ptr<Question>> questions;

public:
    Section(string name);

    string getName() const;

    bool hasQuestions() const;

    int getQuestionCount() const;

    void addQuestion(unique_ptr<Question> question);

    void displayQuestions() const;

    const vector<unique_ptr<Question>> &getQuestions() const;
    const Question *getQuestion(int index) const;
};
