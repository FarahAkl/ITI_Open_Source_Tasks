#include "MultipleChoiceQuestion.h"
#include <cctype>

MultipleChoiceQuestion::MultipleChoiceQuestion(
    string text,
    string choices[],
    vector<char> answers)
    : Question(text, choices),
      correctAnswers(answers)
{
    for (char &answer : correctAnswers)
        answer = static_cast<char>(toupper(answer));
}

bool MultipleChoiceQuestion::checkAnswer(
    const vector<char> &answers) const
{
    if (answers.size() != correctAnswers.size())
        return false;

    vector<char> userAnswers;

    for (char answer : answers)
    {
        answer = static_cast<char>(toupper(answer));

        if (answer < 'A' || answer > 'D')
            return false;

        for (char previous : userAnswers)
        {
            if (answer == previous)
                return false;
        }

        userAnswers.push_back(answer);
    }

    for (char correct : correctAnswers)
    {
        bool found = false;

        for (char answer : userAnswers)
        {
            if (answer == correct)
            {
                found = true;
                break;
            }
        }

        if (!found)
            return false;
    }

    return true;
}