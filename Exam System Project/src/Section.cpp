#include "Section.h"
#include <iostream>
#include <utility>

Section::Section(string name)
    : sectionName(name)
{
}

string Section::getName() const
{
    return sectionName;
}

bool Section::hasQuestions() const
{
    return !questions.empty();
}

int Section::getQuestionCount() const
{
    return static_cast<int>(questions.size());
}

void Section::addQuestion(unique_ptr<Question> question)
{
    questions.push_back(move(question));
}

void Section::displayQuestions() const
{
    cout << "\nSection: " << sectionName << '\n';

    if (questions.empty())
    {
        cout << "No questions available.\n";
        return;
    }

    for (const auto &question : questions)
    {
        question->display();
    }
}

const vector<unique_ptr<Question>> &Section::getQuestions() const
{
    return questions;
}
