#pragma once

#include "Question.h"

class SingleChoiceQuestion : public Question
{
private:
    char correctAnswer;

public:
    SingleChoiceQuestion(string text, string choices[], char answer);
    char getCorrectAnswer() const;

    bool checkAnswer(const vector<char> &answers) const override;
};