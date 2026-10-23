#include "SingleChoiceQuestion.h"
#include <cctype>

SingleChoiceQuestion::SingleChoiceQuestion(
    string text,
    string choices[],
    char answer)
    : Question(text, choices),
      correctAnswer(static_cast<char>(toupper(answer)))
{
}

bool SingleChoiceQuestion::checkAnswer(
    const vector<char> &answers) const
{
    return answers.size() == 1 &&
           toupper(answers[0]) == correctAnswer;
}