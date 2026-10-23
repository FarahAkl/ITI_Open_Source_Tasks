#include "Admin.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <memory>
#include <utility>

using namespace std;

void Admin::addExam()
{
    if (subjects.empty())
    {
        cout << "Add subjects first.\n";
        return;
    }

    string name;
    int duration;

    cout << "Enter exam name: ";
    getline(cin >> ws, name);
    if (name.empty())
    {
        cout << "Exam name cannot be empty.\n";
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

void Admin::displayExams() const
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

void Admin::assignSubjectToDepartment()
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

void Admin::addDepartment()
{
    string name;

    cout << "Enter department name: ";
    getline(cin >> ws, name);
    if (name.empty())
    {
        cout << "Department name cannot be empty.\n";
        return;
    }

    departments.emplace_back(name);

    cout << "Department added successfully!\n";
}

void Admin::displayDepartments() const
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

void Admin::displayDepartmentSubjects() const
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

void Admin::addSubject()
{
    string name;

    cout << "Enter subject name: ";
    getline(cin >> ws, name);
    if (name.empty())
    {
        cout << "Subject name cannot be empty.\n";
        return;
    }

    subjects.emplace_back(name);

    cout << "Subject added successfully!\n";
}

void Admin::displaySubjects() const
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

void Admin::displayQuestions() const
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

void Admin::startQuiz() const
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

void Admin::addQuestion()
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
    else
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

void Admin::startExam()
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

void Admin::addStudent()
{
    int id = static_cast<int>(students.size()) + 1;
    string name;
    string username;
    string password;

    cout << "Enter student name: ";
    getline(cin >> ws, name);

    cout << "Enter username: ";
    getline(cin, username);

    for (const Student &student : students)
    {
        if (student.getUsername() == username)
        {
            cout << "Username already exists.\n";
            return;
        }
    }

    cout << "Enter password: ";
    getline(cin, password);

    students.emplace_back(id, name, username, password);

    cout << "Student added successfully. ID: " << id << '\n';
}

void Admin::displayStudents() const
{
    if (students.empty())
    {
        cout << "No students available.\n";
        return;
    }

    for (const Student &student : students)
    {
        student.display();
    }
}

void Admin::addReservation()
{
    if (students.empty())
    {
        cout << "Add students before creating reservations.\n";
        return;
    }

    if (exams.empty())
    {
        cout << "Add exams before creating reservations.\n";
        return;
    }

    displayStudents();

    int studentId;
    cout << "Enter student ID: ";
    if (!(cin >> studentId))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid student ID.\n";
        return;
    }

    bool studentExists = false;

    for (const Student &student : students)
    {
        if (student.getId() == studentId)
        {
            studentExists = true;
            break;
        }
    }

    if (!studentExists)
    {
        cout << "Student not found.\n";
        return;
    }

    displayExams();

    int examNumber;
    cout << "Enter exam number: ";
    if (!(cin >> examNumber))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid exam number.\n";
        return;
    }

    if (examNumber < 1 || examNumber > static_cast<int>(exams.size()))
    {
        cout << "Exam not found.\n";
        return;
    }

    for (const Reservation &reservation : reservations)
    {
        if (reservation.getStudentId() == studentId &&
            reservation.getExamNumber() == examNumber)
        {
            cout << "This student already has a reservation for this exam.\n";
            return;
        }
    }

    int reservationId = static_cast<int>(reservations.size()) + 1;

    reservations.emplace_back(reservationId, studentId, examNumber);

    cout << "Reservation created successfully.\n";
}

void Admin::displayReservations() const
{
    if (reservations.empty())
    {
        cout << "No reservations available.\n";
        return;
    }

    for (const Reservation &reservation : reservations)
    {
        reservation.display();
    }
}
