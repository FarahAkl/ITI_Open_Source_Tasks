#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <cctype>

using namespace std;

class Question
{
protected:
    string questionText;
    string options[4];

public:
    Question(string text, string choices[])
    {
        questionText = text;
        for (int i = 0; i < 4; i++)
            options[i] = choices[i];
    }

    void display() const
    {
        cout << questionText << "\n"
             << endl;

        for (int i = 0; i < 4; i++)
            cout << static_cast<char>('A' + i) << " - " << options[i] << endl;
    }

    virtual bool checkAnswer(const vector<char> &answers) const = 0;
    virtual ~Question() = default;
};

class SingleChoiceQuestion : public Question
{
private:
    char correctAnswer;

public:
    SingleChoiceQuestion(string text, string choices[], char answer)
        : Question(text, choices)
    {
        correctAnswer = answer;
    }

    bool checkAnswer(const vector<char> &answers) const override
    {
        return answers.size() == 1 &&
               toupper(answers[0]) == toupper(correctAnswer);
    }
};

class MultipleChoiceQuestion : public Question
{
private:
    vector<char> correctAnswers;

public:
    MultipleChoiceQuestion(
        string text,
        string choices[],
        vector<char> answers) : Question(text, choices), correctAnswers(answers)
    {
    }

    bool checkAnswer(const vector<char> &answers) const override
    {
        if (answers.size() != correctAnswers.size())
            return false;

        for (char answer : answers)
        {
            bool found = false;

            for (char correct : correctAnswers)
            {
                if (toupper(answer) == toupper(correct))
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
};

class Subject
{
private:
    string subjectName;
    vector<unique_ptr<Question>> questions;

public:
    Subject(string name)
    {
        subjectName = name;
    }

    string getName() const
    {
        return subjectName;
    }

    bool hasQuestions() const
    {
        return !questions.empty();
    }

    void startQuiz()
    {
        if (questions.empty())
        {
            cout << "No questions available in this subject.\n";
            return;
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
                answers.push_back(toupper(answer));
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

        cout << "Your score: " << score << " / "
             << questions.size() << endl;
    }

    void addQuestion(unique_ptr<Question> question)
    {
        questions.push_back(move(question));
    }

    void displayQuestions() const
    {
        cout << "\nSubject: " << subjectName << endl;

        for (const auto &question : questions)
        {
            question->display();
        }
    }

    int getQuestionsCount() const
    {
        return questions.size();
    }
};

class Admin
{
private:
    vector<Subject> subjects;

public:
    void addSubject()
    {
        string name;

        cout << "Enter subject name: ";
        getline(cin, name);

        subjects.emplace_back(name);

        cout << "Subject added successfully!\n";
    }

    void displaySubjects() const
    {
        if (subjects.empty())
        {
            cout << "No subjects available.\n";
            return;
        }

        for (int i = 0; i < subjects.size(); i++)
        {
            cout << i + 1 << ". " << subjects[i].getName() << endl;
        }
    }

    void displayQuestions() const
    {
        if (subjects.empty())
        {
            cout << "No subjects available.\n";
            return;
        }

        displaySubjects();

        int subjectIndex;
        cout << "Choose subject number: ";
        cin >> subjectIndex;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (subjectIndex < 1 ||
            subjectIndex > static_cast<int>(subjects.size()))
        {
            cout << "Invalid subject number.\n";
            return;
        }

        subjects[subjectIndex - 1].displayQuestions();
    }

    void startQuiz()
    {
        if (subjects.empty())
        {
            cout << "No subjects available.\n";
            return;
        }

        displaySubjects();

        int subjectIndex;
        cout << "Choose subject number for the quiz: ";
        cin >> subjectIndex;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (subjectIndex < 1 ||
            subjectIndex > static_cast<int>(subjects.size()))
        {
            cout << "Invalid subject number.\n";
            return;
        }

        subjects[subjectIndex - 1].startQuiz();
    }

    void addQuestion()
    {
        string question;
        string choices[4];
        int type;

        if (subjects.empty())
        {
            cout << "Add a subject first.\n";
            return;
        }

        displaySubjects();

        int subjectIndex;
        cout << "Choose subject number: ";
        cin >> subjectIndex;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (subjectIndex < 1 || subjectIndex > subjects.size())
        {
            cout << "Invalid subject number.\n";
            return;
        }

        cout << "Choose question type:\n";
        cout << "1. Single Choice\n";
        cout << "2. Multiple Choice\n";
        cin >> type;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter the questions :" << endl;
        getline(cin, question);
        for (int i = 0; i < 4; i++)
        {
            cout << "Enter " << i + 1 << " choice : " << endl;
            getline(cin, choices[i]);
        }

        if (type == 1)
        {
            char answer;
            cout << "Enter the correct answer (A, B, C, or D): " << endl;
            cin >> answer;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            subjects[subjectIndex - 1].addQuestion(
                make_unique<SingleChoiceQuestion>(question, choices, answer));
        }

        if (type == 2)
        {
            int count;
            vector<char> answers;

            cout << "How many correct answers? ";
            cin >> count;

            for (int i = 0; i < count; i++)
            {
                char answer;
                cout << "Enter correct answer " << i + 1 << ": ";
                cin >> answer;
                answers.push_back(toupper(answer));
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            subjects[subjectIndex - 1].addQuestion(
                make_unique<MultipleChoiceQuestion>(question, choices, answers));
        }
    }
};

int main()
{
    Admin admin;

    admin.addSubject();
    admin.addSubject();

    admin.addQuestion();
    admin.addQuestion();

    admin.displayQuestions();
    admin.startQuiz();

    return 0;
}
