#include "Subject.h"
#include <iostream>
#include <cctype>
#include <utility>

Subject::Subject(string name)
    : subjectName(name)
{
}

string Subject::getName() const
{
    return subjectName;
}

bool Subject::hasQuestions() const
{
    return !questions.empty();
}

bool Subject::startQuiz() const
{
    if (questions.empty())
    {
        cout << "No questions available in this subject.\n";
        return false;
    }

    int score = 0;

    for (const auto &question : questions)
    {
        question->display();

        vector<char> answers;
        string input;

        cout << "Enter your answer(s): ";
        cin >> input;

        for (char answer : input)
        {
            answers.push_back(
                static_cast<char>(toupper(static_cast<unsigned char>(answer))));
        }

        if (question->checkAnswer(answers))
        {
            cout << "Correct!\n";
            score++;
        }
        else
        {
            cout << "Incorrect!\n";
        }
    }

    cout << "Your score: " << score
         << " / " << questions.size() << endl;

    return true;
}

void Subject::addQuestion(unique_ptr<Question> question)
{
    questions.push_back(move(question));
}

void Subject::displayQuestions() const
{
    cout << "\nSubject: " << subjectName << endl;

    if (questions.empty())
    {
        cout << "No questions available.\n";
        return;
    }

    for (const auto &question : questions)
        question->display();
}

int Subject::getQuestionsCount() const
{
    return static_cast<int>(questions.size());
}

const vector<unique_ptr<Question>> &Subject::getQuestions() const
{
    return questions;
}