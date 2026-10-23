#pragma once

#include "Question.h"

class SingleChoiceQuestion : public Question
{
private:
    char correctAnswer;

public:
    SingleChoiceQuestion(string text, string choices[], char answer);

    bool checkAnswer(const vector<char> &answers) const override;
};