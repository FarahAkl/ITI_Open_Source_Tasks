#pragma once

#include "Question.h"

class MultipleChoiceQuestion : public Question
{
private:
    vector<char> correctAnswers;

public:
    MultipleChoiceQuestion(
        string text,
        string choices[],
        vector<char> answers);

    bool checkAnswer(const vector<char> &answers) const override;
};