#include "Subject.h"
#include <iostream>
#include <cctype>
#include <utility>
#include <chrono>
#include <conio.h>
#include <thread>
#include <string>
#include <vector>

using namespace std;

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

int Subject::startQuiz(int durationMinutes) const
{
    if (questions.empty())
    {
        cout << "No questions available in this subject.\n";
        return -1;
    }

    if (durationMinutes <= 0)
    {
        cout << "Invalid exam duration.\n";
        return -1;
    }

    vector<vector<char>> answers(questions.size());
    int currentQuestion = 0;
    bool finished = false;
    bool timeExpired = false;

    using Clock = chrono::steady_clock;

    const auto deadline =
        Clock::now() + chrono::minutes(durationMinutes);

    while (!finished)
    {
        if (Clock::now() >= deadline)
        {
            timeExpired = true;
            break;
        }

        cout << "\nQuestion " << currentQuestion + 1
             << " of " << questions.size() << '\n';

        questions[currentQuestion]->display();

        if (!answers[currentQuestion].empty())
        {
            cout << "Current answer: ";

            for (char answer : answers[currentQuestion])
            {
                cout << answer;
            }

            cout << '\n';
        }

        cout << "Enter answer(s), N (next), P (previous), "
             << "or F (finish):\n";

        string input;
        auto lastDisplay = Clock::time_point{};

        while (true)
        {
            auto now = Clock::now();

            if (now >= deadline)
            {
                timeExpired = true;
                finished = true;
                break;
            }

            if (now - lastDisplay >= chrono::seconds(1))
            {
                auto remaining =
                    chrono::duration_cast<chrono::seconds>(
                        deadline - now)
                        .count();

                int minutes = static_cast<int>(remaining / 60);
                int seconds = static_cast<int>(remaining % 60);

                cout << '\r'
                     << "Time remaining: "
                     << minutes << ':'
                     << (seconds < 10 ? "0" : "")
                     << seconds
                     << " | Input: " << input
                     << "                    "
                     << flush;

                lastDisplay = now;
            }

            if (_kbhit())
            {
                int key = _getch();

                if (key == '\r')
                {
                    cout << '\n';
                    break;
                }

                if (key == '\b')
                {
                    if (!input.empty())
                    {
                        input.pop_back();
                    }
                }
                else if (key >= 32 && key <= 126)
                {
                    input += static_cast<char>(key);
                }
            }
            else
            {
                this_thread::sleep_for(
                    chrono::milliseconds(50));
            }
        }

        if (finished)
        {
            break;
        }

        for (char &ch : input)
        {
            ch = static_cast<char>(
                toupper(static_cast<unsigned char>(ch)));
        }

        if (input == "F")
        {
            finished = true;
            continue;
        }

        if (input == "N")
        {
            if (currentQuestion + 1 <
                static_cast<int>(questions.size()))
            {
                currentQuestion++;
            }
            else
            {
                cout << "You are at the last question.\n";
            }

            continue;
        }

        if (input == "P")
        {
            if (currentQuestion > 0)
            {
                currentQuestion--;
            }
            else
            {
                cout << "You are at the first question.\n";
            }

            continue;
        }

        answers[currentQuestion].clear();

        for (char answer : input)
        {
            answers[currentQuestion].push_back(answer);
        }

        if (currentQuestion + 1 <
            static_cast<int>(questions.size()))
        {
            currentQuestion++;
        }
        else
        {
            cout << "You have reached the last question.\n";
        }
    }

    if (timeExpired)
    {
        cout << "\nTime is up! Your exam has ended.\n";
    }

    int score = 0;

    for (size_t i = 0; i < questions.size(); i++)
    {
        if (questions[i]->checkAnswer(answers[i]))
        {
            score++;
        }
    }

    cout << "\n========== Exam Result ==========\n";
    cout << "Your score: " << score
         << " / " << questions.size() << '\n';

    return score;
}

int Subject::getQuestionCount() const
{
    return static_cast<int>(questions.size());
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