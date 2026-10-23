#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Question
{
protected:
    string questionText;
    string options[4];

public:
    Question(string text, string choices[]);
    string getText() const;
    string getOption(int index) const;

    void display() const;

    virtual bool checkAnswer(const vector<char> &answers) const = 0;

    virtual ~Question() = default;
};