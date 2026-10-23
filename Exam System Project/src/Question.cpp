#include "Question.h"

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