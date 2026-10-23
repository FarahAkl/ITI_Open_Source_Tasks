
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <cctype>
#include <utility>

using namespace std;

class Question
{
protected:
    string questionText;
    string options[4];

public:
    Question(string text, string choices[])
        : questionText(text)
    {
        for (int i = 0; i < 4; i++)
            options[i] = choices[i];
    }

    void display() const
    {
        cout << questionText << "\n\n";

        for (int i = 0; i < 4; i++)
            cout << static_cast<char>('A' + i)
                 << " - " << options[i] << endl;
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
        : Question(text, choices),
          correctAnswer(static_cast<char>(toupper(answer)))
    {
    }

    bool checkAnswer(const vector<char> &answers) const override
    {
        return answers.size() == 1 &&
               toupper(answers[0]) == correctAnswer;
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
        vector<char> answers)
        : Question(text, choices),
          correctAnswers(answers)
    {
        for (char &answer : correctAnswers)
            answer = static_cast<char>(toupper(answer));
    }

    bool checkAnswer(const vector<char> &answers) const override
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
};

class Subject
{
private:
    string subjectName;
    vector<unique_ptr<Question>> questions;

public:
    Subject(string name)
        : subjectName(name)
    {
    }

    string getName() const
    {
        return subjectName;
    }

    bool hasQuestions() const
    {
        return !questions.empty();
    }

    void startQuiz() const
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
                answers.push_back(static_cast<char>(toupper(answer)));

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

        if (questions.empty())
        {
            cout << "No questions available.\n";
            return;
        }

        for (const auto &question : questions)
            question->display();
    }

    int getQuestionsCount() const
    {
        return static_cast<int>(questions.size());
    }
};

class Department
{
private:
    string departmentName;
    vector<string> subjectNames;

public:
    Department(string name)
        : departmentName(name)
    {
    }

    string getName() const
    {
        return departmentName;
    }

    void addSubject(string subjectName)
    {
        subjectNames.push_back(subjectName);
    }

    bool hasSubject(const string &subjectName) const
    {
        for (const string &subject : subjectNames)
        {
            if (subject == subjectName)
                return true;
        }

        return false;
    }

    void displaySubjects() const
    {
        cout << "\nDepartment: " << departmentName << endl;

        if (subjectNames.empty())
        {
            cout << "No subjects assigned.\n";
            return;
        }

        for (const string &subject : subjectNames)
            cout << "- " << subject << endl;
    }
};

class Exam
{
private:
    string examName;
    string subjectName;
    int durationMinutes;

public:
    Exam(string name, string subject, int duration)
        : examName(name),
          subjectName(subject),
          durationMinutes(duration)
    {
    }

    string getName() const
    {
        return examName;
    }

    string getSubjectName() const
    {
        return subjectName;
    }

    int getDuration() const
    {
        return durationMinutes;
    }

    void display() const
    {
        cout << "Exam: " << examName << endl;
        cout << "Subject: " << subjectName << endl;
        cout << "Duration: " << durationMinutes
             << " minutes" << endl;
    }
};

class Admin
{
private:
    vector<Subject> subjects;
    vector<Department> departments;
    vector<Exam> exams;

public:
    void addExam()
    {
        if (subjects.empty())
        {
            cout << "Add subjects first.\n";
            return;
        }

        string name;
        int duration;

        cout << "Enter exam name: ";
        getline(cin, name);

        displaySubjects();

        int subjectIndex;
        cout << "Choose subject number: ";

        if (!(cin >> subjectIndex))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (subjectIndex < 1 ||
            subjectIndex > static_cast<int>(subjects.size()))
        {
            cout << "Invalid subject number.\n";
            return;
        }

        if (!subjects[subjectIndex - 1].hasQuestions())
        {
            cout << "Add questions to this subject first.\n";
            return;
        }

        cout << "Enter exam duration in minutes: ";

        if (!(cin >> duration) || duration <= 0)
        {
            cout << "Invalid duration.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        exams.emplace_back(
            name,
            subjects[subjectIndex - 1].getName(),
            duration);

        cout << "Exam added successfully!\n";
    }

    void displayExams() const
    {
        if (exams.empty())
        {
            cout << "No exams available.\n";
            return;
        }

        for (int i = 0; i < static_cast<int>(exams.size()); i++)
        {
            cout << "\nExam number: " << i + 1 << endl;
            exams[i].display();
        }
    }

    void assignSubjectToDepartment()
    {
        if (departments.empty() || subjects.empty())
        {
            cout << "Add departments and subjects first.\n";
            return;
        }

        displayDepartments();

        int departmentIndex;
        cout << "Choose department number: ";

        if (!(cin >> departmentIndex))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (departmentIndex < 1 ||
            departmentIndex > static_cast<int>(departments.size()))
        {
            cout << "Invalid department number.\n";
            return;
        }

        displaySubjects();

        int subjectIndex;
        cout << "Choose subject number: ";

        if (!(cin >> subjectIndex))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (subjectIndex < 1 ||
            subjectIndex > static_cast<int>(subjects.size()))
        {
            cout << "Invalid subject number.\n";
            return;
        }

        string subjectName = subjects[subjectIndex - 1].getName();

        if (departments[departmentIndex - 1].hasSubject(subjectName))
        {
            cout << "Subject already assigned to this department.\n";
            return;
        }

        departments[departmentIndex - 1].addSubject(subjectName);

        cout << "Subject assigned successfully!\n";
    }

    void addDepartment()
    {
        string name;

        cout << "Enter department name: ";
        getline(cin, name);

        if (name.empty())
        {
            cout << "Department name cannot be empty.\n";
            return;
        }

        departments.emplace_back(name);

        cout << "Department added successfully!\n";
    }

    void displayDepartments() const
    {
        if (departments.empty())
        {
            cout << "No departments available.\n";
            return;
        }

        for (int i = 0; i < static_cast<int>(departments.size()); i++)
        {
            cout << i + 1 << ". "
                 << departments[i].getName() << endl;
        }
    }

    void displayDepartmentSubjects() const
    {
        if (departments.empty())
        {
            cout << "No departments available.\n";
            return;
        }

        displayDepartments();

        int departmentIndex;
        cout << "Choose department number: ";

        if (!(cin >> departmentIndex))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (departmentIndex < 1 ||
            departmentIndex > static_cast<int>(departments.size()))
        {
            cout << "Invalid department number.\n";
            return;
        }

        departments[departmentIndex - 1].displaySubjects();
    }

    void addSubject()
    {
        string name;

        cout << "Enter subject name: ";
        getline(cin, name);

        if (name.empty())
        {
            cout << "Subject name cannot be empty.\n";
            return;
        }

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

        for (int i = 0; i < static_cast<int>(subjects.size()); i++)
        {
            cout << i + 1 << ". "
                 << subjects[i].getName() << endl;
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

        if (!(cin >> subjectIndex))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (subjectIndex < 1 ||
            subjectIndex > static_cast<int>(subjects.size()))
        {
            cout << "Invalid subject number.\n";
            return;
        }

        subjects[subjectIndex - 1].displayQuestions();
    }

    void startQuiz() const
    {
        if (subjects.empty())
        {
            cout << "No subjects available.\n";
            return;
        }

        displaySubjects();

        int subjectIndex;
        cout << "Choose subject number for the quiz: ";

        if (!(cin >> subjectIndex))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

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

        if (!(cin >> subjectIndex))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (subjectIndex < 1 ||
            subjectIndex > static_cast<int>(subjects.size()))
        {
            cout << "Invalid subject number.\n";
            return;
        }

        cout << "Choose question type:\n";
        cout << "1. Single Choice\n";
        cout << "2. Multiple Choice\n";

        if (!(cin >> type))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (type != 1 && type != 2)
        {
            cout << "Invalid question type.\n";
            return;
        }

        cout << "Enter the question: ";
        getline(cin, question);

        if (question.empty())
        {
            cout << "Question cannot be empty.\n";
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            cout << "Enter choice " << i + 1 << ": ";
            getline(cin, choices[i]);

            if (choices[i].empty())
            {
                cout << "Choice cannot be empty.\n";
                return;
            }
        }

        if (type == 1)
        {
            char answer;

            cout << "Enter the correct answer (A, B, C, or D): ";

            if (!(cin >> answer))
            {
                cout << "Invalid input.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }

            answer = static_cast<char>(toupper(answer));
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (answer < 'A' || answer > 'D')
            {
                cout << "Invalid answer. Choose A, B, C, or D.\n";
                return;
            }

            subjects[subjectIndex - 1].addQuestion(
                make_unique<SingleChoiceQuestion>(
                    question, choices, answer));
        }
        else if (type == 2)
        {
            int count;
            vector<char> answers;

            cout << "How many correct answers? ";

            if (!(cin >> count) || count < 1 || count > 4)
            {
                cout << "Invalid number of answers.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }

            for (int i = 0; i < count; i++)
            {
                char answer;

                cout << "Enter correct answer " << i + 1 << ": ";

                if (!(cin >> answer))
                {
                    cout << "Invalid input.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return;
                }

                answer = static_cast<char>(toupper(answer));

                if (answer < 'A' || answer > 'D')
                {
                    cout << "Invalid answer. Choose A, B, C, or D.\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return;
                }

                for (char previous : answers)
                {
                    if (previous == answer)
                    {
                        cout << "You cannot enter the same answer twice.\n";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        return;
                    }
                }

                answers.push_back(answer);
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            subjects[subjectIndex - 1].addQuestion(
                make_unique<MultipleChoiceQuestion>(
                    question, choices, answers));
        }

        cout << "Question added successfully!\n";
    }

    void startExam()
    {
        if (exams.empty())
        {
            cout << "No exams available.\n";
            return;
        }

        displayExams();

        int examIndex;
        cout << "\nChoose exam number: ";

        if (!(cin >> examIndex))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (examIndex < 1 ||
            examIndex > static_cast<int>(exams.size()))
        {
            cout << "Invalid exam number.\n";
            return;
        }

        string subjectName = exams[examIndex - 1].getSubjectName();

        for (const auto &subject : subjects)
        {
            if (subject.getName() == subjectName)
            {
                cout << "\nStarting exam: "
                     << exams[examIndex - 1].getName() << endl;

                cout << "Duration: "
                     << exams[examIndex - 1].getDuration()
                     << " minutes\n\n";

                subject.startQuiz();
                return;
            }
        }

        cout << "Subject not found.\n";
    }
};

int main()
{
    Admin admin;

    admin.addDepartment();
    admin.addSubject();
    admin.assignSubjectToDepartment();

    admin.addQuestion();

    admin.addExam();
    admin.displayExams();
    admin.startExam();

    return 0;
}
