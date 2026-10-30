#include "Question.h"
#include <stdexcept>

Question::Question(string text, string choices[])
    : questionText(text)
{
    for (int i = 0; i < 4; i++)
        options[i] = choices[i];
}

void Question::display() const
{
    cout << questionText << "\n\n";

    for (int i = 0; i < 4; i++)
    {
        cout << static_cast<char>('A' + i)
             << " - " << options[i] << endl;
    }
}

string Question::getText() const
{
    return questionText;
}

string Question::getOption(int index) const
{
    if (index < 0 || index >= 4)
        throw out_of_range("Question option index must be between 0 and 3.");

    return options[index];
}

string Question::operator[](size_t index) const
{
    if (index >= 4)
        throw out_of_range("Question option index must be between 0 and 3.");
    return options[index];
}

bool Question::operator==(const Question &other) const
{
    if (questionText != other.questionText)
        return false;
    for (int i = 0; i < 4; ++i)
        if (options[i] != other.options[i]) return false;
    return true;
}
