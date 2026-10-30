#include "Admin.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <memory>
#include <utility>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <chrono>

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
    for (const Exam &existing : exams)
        if (existing.getName() == name)
        {
            cout << "An exam with that name already exists.\n";
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

    Exam exam(name, duration);

    while (true)
    {
        cout << "\nAvailable Subjects:\n";
        displaySubjects();

        int subjectIndex;

        cout << "\nChoose subject number (0 to finish): ";

        if (!(cin >> subjectIndex))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (subjectIndex == 0)
        {
            break;
        }

        if (subjectIndex < 1 ||
            subjectIndex > static_cast<int>(subjects.size()))
        {
            cout << "Invalid subject number.\n";
            continue;
        }

        Subject &subject = subjects[subjectIndex - 1];

        if (!subject.hasSections())
        {
            cout << "This subject has no sections.\n";
            continue;
        }

        subject.displaySections();

        int sectionIndex;

        cout << "Choose section number: ";

        if (!(cin >> sectionIndex))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        Section *section = subject.getSection(sectionIndex - 1);

        if (section == nullptr)
        {
            cout << "Invalid section number.\n";
            continue;
        }

        if (!section->hasQuestions())
        {
            cout << "This section has no questions.\n";
            continue;
        }

        cout << "Available questions: "
             << section->getQuestionCount() << '\n';

        int questionCount;

        cout << "Enter number of questions: ";

        if (!(cin >> questionCount) ||
            questionCount <= 0 ||
            questionCount > section->getQuestionCount())
        {
            cout << "Invalid question count.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        int marks;

        cout << "Enter marks for this section: ";

        if (!(cin >> marks) || marks <= 0)
        {
            cout << "Invalid marks.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        ExamDetail detail(
            subject.getName(),
            section->getName(),
            questionCount,
            marks);

        bool duplicateSection = false;
        for (const ExamDetail &existing : exam.getDetails())
            if (existing.getSubjectName() == detail.getSubjectName() &&
                existing.getSectionName() == detail.getSectionName())
                duplicateSection = true;
        if (duplicateSection)
        {
            cout << "That section is already included in this exam.\n";
            continue;
        }

        exam += detail;

        cout << "Section added to exam successfully!\n";
    }

    if (exam.getDetails().empty())
    {
        cout << "No sections were added. Exam was not created.\n";
        return;
    }

    exams.push_back(exam);

    cout << "\nExam created successfully!\n";
    exam.display();
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

void Admin::addSection()
{
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
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid subject number.\n";
        return;
    }
    if (subjectIndex < 1 || subjectIndex > static_cast<int>(subjects.size()))
    {
        cout << "Invalid subject number.\n";
        return;
    }

    string name;
    cout << "Enter section name: ";
    getline(cin >> ws, name);
    if (name.empty() || name.find('|') != string::npos)
    {
        cout << "Section name cannot be empty or contain '|'.\n";
        return;
    }
    Subject &subject = subjects[static_cast<size_t>(subjectIndex - 1)];
    for (const Section &section : subject.getSections())
    {
        if (section.getName() == name)
        {
            cout << "Section already exists in this subject.\n";
            return;
        }
    }
    subject.addSection(name);
    saveData();
    cout << "Section added successfully.\n";
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

    if (subjectIndex < 1 ||
        subjectIndex > static_cast<int>(subjects.size()))
    {
        cout << "Invalid subject number.\n";
        return;
    }

    const Subject &subject = subjects[subjectIndex - 1];

    if (!subject.hasSections())
    {
        cout << "This subject has no sections.\n";
        return;
    }

    subject.displaySections();

    int sectionIndex;
    cout << "Choose section number: ";

    if (!(cin >> sectionIndex))
    {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    const Section *section = subject.getSection(sectionIndex - 1);

    if (section == nullptr)
    {
        cout << "Invalid section number.\n";
        return;
    }

    section->displayQuestions();
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

    const Subject &subject = subjects[static_cast<size_t>(subjectIndex - 1)];
    vector<const Question *> questions;
    for (const Section &section : subject.getSections())
        for (const auto &question : section.getQuestions())
            questions.push_back(question.get());
    if (questions.empty())
    {
        cout << "This subject has no questions.\n";
        return;
    }
    int score = 0;
    for (size_t i = 0; i < questions.size(); ++i)
    {
        cout << "\nQuestion " << i + 1 << " of " << questions.size() << ":\n";
        questions[i]->display();
        cout << "Answer (A-D; multiple answers separated by spaces): ";
        string answerLine;
        getline(cin >> ws, answerLine);
        vector<char> answers;
        for (unsigned char ch : answerLine)
            if (isalpha(ch)) answers.push_back(static_cast<char>(toupper(ch)));
        if (questions[i]->checkAnswer(answers)) ++score;
    }
    cout << "Quiz score: " << score << " / " << questions.size() << '\n';
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

    Subject &subject = subjects[subjectIndex - 1];

    if (!subject.hasSections())
    {
        cout << "This subject has no sections. Add a section first.\n";
        return;
    }

    subject.displaySections();

    int sectionIndex;
    cout << "Choose section number: ";

    if (!(cin >> sectionIndex))
    {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Section *section = subject.getSection(sectionIndex - 1);

    if (section == nullptr)
    {
        cout << "Invalid section number.\n";
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

        answer = static_cast<char>(
            toupper(static_cast<unsigned char>(answer)));

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (answer < 'A' || answer > 'D')
        {
            cout << "Invalid answer.\n";
            return;
        }

        section->addQuestion(
            make_unique<SingleChoiceQuestion>(
                question, choices, answer));
    }
    else
    {
        int count;
        vector<char> answers;

        cout << "How many correct answers? ";

        if (!(cin >> count) || count < 2 || count > 4)
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

            answer = static_cast<char>(
                toupper(static_cast<unsigned char>(answer)));

            if (answer < 'A' || answer > 'D')
            {
                cout << "Invalid answer.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }

            for (char previous : answers)
            {
                if (previous == answer)
                {
                    cout << "Duplicate answer.\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return;
                }
            }

            answers.push_back(answer);
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        section->addQuestion(
            make_unique<MultipleChoiceQuestion>(
                question, choices, answers));
    }

    cout << "Question added successfully!\n";
}

void Admin::startExam()
{
    if (students.empty())
    {
        cout << "No students available.\n";
        return;
    }

    if (exams.empty())
    {
        cout << "No exams available.\n";
        return;
    }

    string username, password;
    cout << "Student username: ";
    getline(cin >> ws, username);
    cout << "Password: ";
    getline(cin, password);
    const Student *authenticatedStudent = nullptr;
    for (const Student &student : students)
        if (student.checkLogin(username, password))
        {
            authenticatedStudent = &student;
            break;
        }
    if (!authenticatedStudent)
    {
        cout << "Login failed. Check the username and password.\n";
        return;
    }
    const int studentId = authenticatedStudent->getId();

    displayExams();

    int examNumber;
    cout << "Choose exam number: ";

    if (!(cin >> examNumber))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid exam number.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (examNumber < 1 ||
        examNumber > static_cast<int>(exams.size()))
    {
        cout << "Invalid exam number.\n";
        return;
    }

    Reservation *studentReservation = nullptr;

    for (Reservation &reservation : reservations)
    {
        if (reservation.getStudentId() == studentId &&
            reservation.getExamNumber() == examNumber)
        {
            studentReservation = &reservation;
            break;
        }
    }

    if (studentReservation == nullptr)
    {
        cout << "You must reserve this exam before starting it.\n";
        return;
    }

    if (studentReservation->isCompleted())
    {
        cout << "This exam has already been completed.\n";
        return;
    }

    const Exam &exam = exams[static_cast<size_t>(examNumber - 1)];
    struct ExamQuestion { const Question *question; int detailIndex; int questionIndex; };
    vector<ExamQuestion> selected;
    mt19937 randomEngine(random_device{}());
    const auto makeQuestion = [&](int detailIndex, int questionIndex) -> ExamQuestion {
        const ExamDetail &detail = exam.getDetails()[static_cast<size_t>(detailIndex)];
        for (const Subject &subject : subjects)
            if (subject.getName() == detail.getSubjectName())
                for (int sectionIndex = 0; sectionIndex < subject.getSectionsCount(); ++sectionIndex)
                {
                    const Section *section = subject.getSection(sectionIndex);
                    if (section->getName() == detail.getSectionName())
                        return {section->getQuestion(questionIndex), detailIndex, questionIndex};
                }
        return {nullptr, detailIndex, questionIndex};
    };
    if (studentReservation->isInProgress() && !studentReservation->getRunningQuestions().empty())
    {
        for (const auto &key : studentReservation->getRunningQuestions())
        {
            ExamQuestion item = makeQuestion(key.first, key.second);
            if (!item.question) { selected.clear(); break; }
            selected.push_back(item);
        }
    }
    vector<pair<int, int>> questionKeys;
    if (selected.empty()) for (size_t detailIndex = 0; detailIndex < exam.getDetails().size(); ++detailIndex)
    {
        const ExamDetail &detail = exam.getDetails()[detailIndex];
        const Subject *subject = nullptr;
        for (const Subject &candidate : subjects)
            if (candidate.getName() == detail.getSubjectName()) { subject = &candidate; break; }
        const Section *section = nullptr;
        if (subject)
            for (int i = 0; i < subject->getSectionsCount(); ++i)
                if (subject->getSection(i)->getName() == detail.getSectionName()) { section = subject->getSection(i); break; }
        if (!section || section->getQuestionCount() < detail.getQuestionCount())
        {
            cout << "The exam cannot start: a section has too few questions.\n";
            return;
        }
        vector<int> indices(static_cast<size_t>(section->getQuestionCount()));
        for (size_t i = 0; i < indices.size(); ++i) indices[i] = static_cast<int>(i);
        shuffle(indices.begin(), indices.end(), randomEngine);
        for (int i = 0; i < detail.getQuestionCount(); ++i)
            selected.push_back({section->getQuestion(indices[static_cast<size_t>(i)]), static_cast<int>(detailIndex), indices[static_cast<size_t>(i)]});
    }
    if (selected.empty()) { cout << "The exam has no questions.\n"; return; }
    for (const ExamQuestion &item : selected) questionKeys.push_back({item.detailIndex, item.questionIndex});

    cout << (studentReservation->isInProgress() ? "\nResuming exam: " : "\nStarting exam: ")
         << exam.getName() << " (" << exam.getDuration() << " minutes)\n";
    if (!studentReservation->isInProgress())
        studentReservation->setAttempt(questionKeys, 0, exam.getDuration() * 60);
    vector<vector<char>> responses = studentReservation->getSelectedAnswers();
    responses.resize(selected.size());
    size_t current = static_cast<size_t>(max(0, min(studentReservation->getCurrentQuestion(), static_cast<int>(selected.size() - 1))));
    int remainingSeconds = studentReservation->getRemainingSeconds() > 0 ? studentReservation->getRemainingSeconds() : exam.getDuration() * 60;
    auto lastSavedAt = chrono::steady_clock::now();
    while (current < selected.size())
    {
        cout << "\nQuestion " << current + 1 << " of " << selected.size() << "\n";
        selected[current].question->display();
        if (!responses[current].empty())
        {
            cout << "Saved answer: ";
            for (char a : responses[current]) cout << a << ' ';
            cout << '\n';
        }
        cout << "Enter answer(s), N next, P previous, S submit: ";
        string input;
        getline(cin >> ws, input);
        const auto now = chrono::steady_clock::now();
        const int elapsed = static_cast<int>(chrono::duration_cast<chrono::seconds>(now - lastSavedAt).count());
        remainingSeconds = max(0, remainingSeconds - elapsed);
        lastSavedAt = now;
        if (remainingSeconds == 0) { cout << "Time expired. Submitting exam.\n"; break; }
        if (input == "Q" || input == "q")
        {
            studentReservation->setAttempt(questionKeys, static_cast<int>(current), remainingSeconds);
            for (size_t i = 0; i < responses.size(); ++i) studentReservation->setSelectedAnswer(i, responses[i]);
            saveData();
            cout << "Attempt saved. Choose Start Exam again to resume.\n";
            return;
        }
        if (input == "N" || input == "n") { if (current + 1 < selected.size()) ++current; else cout << "Already at the last question.\n"; }
        else if (input == "P" || input == "p") { if (current > 0) --current; else cout << "Already at the first question.\n"; }
        else if (input == "S" || input == "s") break;
        else
        {
        vector<char> answers;
        for (unsigned char ch : input)
            if (isalpha(ch)) answers.push_back(static_cast<char>(toupper(ch)));
        bool valid = !answers.empty();
        for (char a : answers) if (a < 'A' || a > 'D') valid = false;
        if (!valid || (dynamic_cast<const SingleChoiceQuestion *>(selected[current].question) && answers.size() != 1))
        {
            cout << "Invalid answer selection. Try again.\n";
            continue;
        }
        responses[current] = answers;
        if (current + 1 < selected.size()) ++current;
        }
        studentReservation->setAttempt(questionKeys, static_cast<int>(current), remainingSeconds);
        for (size_t i = 0; i < responses.size(); ++i) studentReservation->setSelectedAnswer(i, responses[i]);
        saveData();
    }

    int earned = 0;
    int totalMarks = 0;
    for (size_t d = 0; d < exam.getDetails().size(); ++d)
    {
        const ExamDetail &detail = exam.getDetails()[d];
        int sectionCorrect = 0;
        int sectionCount = 0;
        for (size_t i = 0; i < selected.size(); ++i)
            if (selected[i].detailIndex == static_cast<int>(d))
            {
                ++sectionCount;
                if (selected[i].question->checkAnswer(responses[i])) ++sectionCorrect;
            }
        int sectionScore = sectionCount ? detail.getMarks() * sectionCorrect / sectionCount : 0;
        earned += sectionScore;
        totalMarks += detail.getMarks();
        cout << detail.getSubjectName() << " / " << detail.getSectionName() << ": "
             << sectionScore << " / " << detail.getMarks() << '\n';
    }
    const double percent = totalMarks ? 100.0 * earned / totalMarks : 0.0;
    cout << "Final score: " << earned << " / " << totalMarks << " (" << percent << "%)\n";
    cout << (percent >= 60.0 ? "Result: PASS\n" : "Result: FAIL\n");
    studentReservation->markCompleted(earned, totalMarks);
    saveData();
    cout << "Exam submitted and result saved.\n";
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    saveData();

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

void Admin::displayResults() const
{
    bool foundResults = false;

    for (const Reservation &reservation : reservations)
    {
        if (!reservation.isCompleted())
        {
            continue;
        }

        const Student *studentFound = nullptr;

        for (const Student &student : students)
        {
            if (student.getId() == reservation.getStudentId())
            {
                studentFound = &student;
                break;
            }
        }

        int examNumber = reservation.getExamNumber();

        if (studentFound == nullptr ||
            examNumber < 1 ||
            examNumber > static_cast<int>(exams.size()))
        {
            continue;
        }

        const Exam &exam = exams[examNumber - 1];

        cout << "\n========== Exam Result ==========\n";
        cout << "Student: " << studentFound->getName() << '\n';
        cout << "Student ID: " << studentFound->getId() << '\n';
        cout << "Exam: " << exam.getName() << '\n';
        cout << "Score: " << reservation.getScore()
             << " / " << reservation.getTotalQuestions() << " marks\n";
        const double percentage = reservation.getTotalQuestions() > 0
            ? 100.0 * reservation.getScore() / reservation.getTotalQuestions() : 0.0;
        cout << "Percentage: " << percentage << "%\n";
        cout << "Result: " << (percentage >= 60.0 ? "PASS" : "FAIL") << '\n';
        cout << "Section performance:\n";
        const auto &running = reservation.getRunningQuestions();
        const auto &answers = reservation.getSelectedAnswers();
        for (size_t detailIndex = 0; detailIndex < exam.getDetails().size(); ++detailIndex)
        {
            const ExamDetail &detail = exam.getDetails()[detailIndex];
            const Subject *subject = nullptr;
            for (const Subject &candidate : subjects)
                if (candidate.getName() == detail.getSubjectName()) { subject = &candidate; break; }
            const Section *section = nullptr;
            if (subject)
                for (int sectionIndex = 0; sectionIndex < subject->getSectionsCount(); ++sectionIndex)
                    if (subject->getSection(sectionIndex)->getName() == detail.getSectionName())
                    { section = subject->getSection(sectionIndex); break; }
            int count = 0, correct = 0;
            for (size_t position = 0; position < running.size() && position < answers.size(); ++position)
                if (running[position].first == static_cast<int>(detailIndex) && section)
                {
                    ++count;
                    const Question *question = section->getQuestion(running[position].second);
                    if (question && question->checkAnswer(answers[position])) ++correct;
                }
            const int sectionScore = count ? detail.getMarks() * correct / count : 0;
            cout << "- " << detail.getSubjectName() << " / " << detail.getSectionName()
                 << ": " << sectionScore << " / " << detail.getMarks() << " marks\n";
        }

        foundResults = true;
    }

    if (!foundResults)
    {
        cout << "No completed exam results available.\n";
    }
}

void Admin::saveData() const
{
    ofstream departmentFile("data/departments.txt");
    ofstream studentFile("data/students.txt");
    ofstream subjectFile("data/subjects.txt");
    ofstream questionFile("data/questions.txt");
    ofstream examFile("data/exams.txt");
    ofstream reservationFile("data/reservations.txt");
    ofstream departmentSubjectFile("data/department_subjects.txt");
    ofstream sectionFile("data/sections.txt");
    ofstream runningFile("data/exam_running.txt");
    ofstream runningAnswersFile("data/exam_running_ans.txt");

    if (!departmentFile || !studentFile || !subjectFile || !questionFile || !examFile || !reservationFile || !departmentSubjectFile || !sectionFile || !runningFile || !runningAnswersFile)
    {
        cout << "Error saving data. Check the data folder.\n";
        return;
    }

    for (const Department &department : departments)
    {
        departmentFile << department.getName() << '\n';
    }

    for (const Department &department : departments)
    {
        for (const string &subjectName : department.getSubjects())
        {
            departmentSubjectFile << department.getName() << '|'
                                  << subjectName << '\n';
        }
    }

    for (const Student &student : students)
    {
        studentFile << student.getId() << '|'
                    << student.getName() << '|'
                    << student.getUsername() << '|'
                    << student.getPassword() << '\n';
    }

    for (const Subject &subject : subjects)
    {
        subjectFile << subject.getName() << '\n';
        for (const Section &section : subject.getSections())
        {
            sectionFile << subject.getName() << '|' << section.getName() << '\n';
            for (const auto &question : section.getQuestions())
            {
                questionFile << subject.getName() << '|' << section.getName() << '|';

                if (const auto *single = dynamic_cast<const SingleChoiceQuestion *>(question.get()))
                {
                    questionFile << 'S' << '|' << single->getText() << '|';

                    for (int i = 0; i < 4; i++)
                        questionFile << single->getOption(i) << '|';
                    questionFile << single->getCorrectAnswer() << '\n';
                }
                else if (const auto *multiple = dynamic_cast<const MultipleChoiceQuestion *>(question.get()))
                {
                    questionFile << 'M' << '|' << multiple->getText() << '|';
                    for (int i = 0; i < 4; i++) questionFile << multiple->getOption(i) << '|';
                    vector<char> answers = multiple->getCorrectAnswers();
                    for (size_t i = 0; i < answers.size(); i++)
                    {
                        if (i > 0) questionFile << ',';
                        questionFile << answers[i];
                    }
                    questionFile << '\n';
                }
            }
        }
    }

    for (const Exam &exam : exams)
    {
        examFile << exam.getName() << '|'
                 << exam.getDuration() << '|'
                 << exam.getDetails().size() << '\n';

        for (const ExamDetail &detail : exam.getDetails())
        {
            examFile << detail.getSubjectName() << '|'
                     << detail.getSectionName() << '|'
                     << detail.getQuestionCount() << '|'
                     << detail.getMarks() << '\n';
        }
    }
    for (const Reservation &reservation : reservations)
    {
        reservationFile << reservation.getId() << '|'
                        << reservation.getStudentId() << '|'
                        << reservation.getExamNumber() << '|'
                        << reservation.isCompleted() << '|'
                        << reservation.getScore() << '|'
                        << reservation.getTotalQuestions() << '|'
                        << reservation.isInProgress() << '|'
                        << reservation.getCurrentQuestion() << '|'
                        << reservation.getRemainingSeconds() << '\n';
        for (size_t position = 0; position < reservation.getRunningQuestions().size(); ++position)
        {
            runningFile << reservation.getId() << '|' << position << '|'
                        << reservation.getRunningQuestions()[position].first << '|'
                        << reservation.getRunningQuestions()[position].second << '\n';
            runningAnswersFile << reservation.getId() << '|' << position << '|';
            const auto &answers = reservation.getSelectedAnswers()[position];
            for (size_t i = 0; i < answers.size(); ++i)
            {
                if (i) runningAnswersFile << ',';
                runningAnswersFile << answers[i];
            }
            runningAnswersFile << '\n';
        }
    }

    cout << "Data saved successfully.\n";
}

void Admin::loadData()
{
    departments.clear();
    students.clear();
    subjects.clear();
    exams.clear();
    reservations.clear();

    ifstream departmentFile("data/departments.txt");
    ifstream studentFile("data/students.txt");
    ifstream subjectFile("data/subjects.txt");
    ifstream questionFile("data/questions.txt");
    ifstream examFile("data/exams.txt");
    ifstream reservationFile("data/reservations.txt");
    ifstream departmentSubjectFile("data/department_subjects.txt");
    ifstream sectionFile("data/sections.txt");
    ifstream runningFile("data/exam_running.txt");
    ifstream runningAnswersFile("data/exam_running_ans.txt");

    string examLine;
    string line;

    while (getline(departmentFile, line))
    {
        if (!line.empty())
            departments.emplace_back(line);
    }

    while (getline(studentFile, line))
    {
        stringstream stream(line);
        string idText;
        string name;
        string username;
        string password;

        if (getline(stream, idText, '|') &&
            getline(stream, name, '|') &&
            getline(stream, username, '|') &&
            getline(stream, password))
        {
            try
            {
                int id = stoi(idText);
                students.emplace_back(id, name, username, password);
            }
            catch (const invalid_argument &)
            {
                cout << "Skipping invalid student record.\n";
            }
            catch (const out_of_range &)
            {
                cout << "Skipping invalid student ID.\n";
            }
        }
    }

    while (getline(subjectFile, line))
    {
        if (!line.empty())
            subjects.emplace_back(line);
    }

    while (getline(sectionFile, line))
    {
        stringstream stream(line);
        string subjectName, sectionName;
        if (!getline(stream, subjectName, '|') || !getline(stream, sectionName) || sectionName.empty())
            continue;
        for (Subject &subject : subjects)
            if (subject.getName() == subjectName)
                subject.addSection(sectionName);
    }

    while (getline(departmentSubjectFile, line))
    {
        if (line.empty())
            continue;

        stringstream stream(line);
        string departmentName;
        string subjectName;

        if (!getline(stream, departmentName, '|') ||
            !getline(stream, subjectName))
        {
            continue;
        }

        for (Department &department : departments)
        {
            if (department.getName() == departmentName &&
                !department.hasSubject(subjectName))
            {
                department.addSubject(subjectName);
                break;
            }
        }
    }

    while (getline(examFile, examLine))
    {
        if (examLine.empty())
        {
            continue;
        }

        stringstream ss(examLine);

        string examName;
        string durationText;
        string detailsCountText;

        getline(ss, examName, '|');
        getline(ss, durationText, '|');
        getline(ss, detailsCountText);

        try
        {
            int duration = 0;
            int detailsCount = 0;
            bool legacyExam = false;
            try
            {
                duration = stoi(durationText);
                detailsCount = stoi(detailsCountText);
            }
            catch (const exception &)
            {
                legacyExam = true;
                duration = stoi(detailsCountText);
                detailsCount = 1;
            }

            Exam exam(examName, duration);
            if (legacyExam)
            {
                const string &subjectName = durationText;
                for (Subject &subject : subjects)
                    if (subject.getName() == subjectName)
                    {
                        if (!subject.hasSections()) subject.addSection("General");
                        const Section *section = subject.getSection(0);
                        if (section)
                            exam += ExamDetail(subjectName, section->getName(), 1, 100);
                        break;
                    }
                if (exam.getDetails().empty())
                {
                    cout << "Skipping legacy exam without a valid subject.\n";
                    continue;
                }
                exams.push_back(exam);
                continue;
            }

            for (int i = 0; i < detailsCount; i++)
            {
                if (!getline(examFile, line))
                {
                    break;
                }

                stringstream detailStream(line);

                string subjectName;
                string sectionName;
                string questionCountText;
                string marksText;

                getline(detailStream, subjectName, '|');
                getline(detailStream, sectionName, '|');
                getline(detailStream, questionCountText, '|');
                getline(detailStream, marksText);

                int questionCount = stoi(questionCountText);
                int marks = stoi(marksText);

                ExamDetail detail(
                    subjectName,
                    sectionName,
                    questionCount,
                    marks);

                exam += detail;
            }

            exams.push_back(exam);
        }
        catch (const invalid_argument &)
        {
            cout << "Invalid exam data found.\n";
        }
        catch (const out_of_range &)
        {
            cout << "Exam data is out of range.\n";
        }
    }

    while (getline(reservationFile, line))
    {
        if (line.empty())
            continue;

        stringstream stream(line);
        string idText;
        string studentIdText;
        string examNumberText;
        string completedText;
        string scoreText = "0";
        string totalQuestionsText = "0";
        string inProgressText = "0", currentQuestionText = "0", remainingSecondsText = "0";

        if (!getline(stream, idText, '|') ||
            !getline(stream, studentIdText, '|') ||
            !getline(stream, examNumberText, '|') ||
            !getline(stream, completedText, '|'))
        {
            continue;
        }

        getline(stream, scoreText, '|');
        getline(stream, totalQuestionsText, '|');
        getline(stream, inProgressText, '|');
        getline(stream, currentQuestionText, '|');
        getline(stream, remainingSecondsText);

        try
        {
            int id = stoi(idText);
            int studentId = stoi(studentIdText);
            int examNumber = stoi(examNumberText);
            bool completed = (completedText == "1");
            int score = stoi(scoreText);
            int totalQuestions = stoi(totalQuestionsText);
            bool inProgress = (inProgressText == "1");
            int currentQuestion = stoi(currentQuestionText);
            int remainingSeconds = stoi(remainingSecondsText);

            if (id <= 0 ||
                studentId <= 0 ||
                examNumber < 1 ||
                examNumber > static_cast<int>(exams.size()))
            {
                cout << "Skipping reservation with invalid IDs.\n";
                continue;
            }

            if (score < 0 || totalQuestions < 0 ||
                score > totalQuestions)
            {
                cout << "Skipping reservation with invalid score.\n";
                continue;
            }

            reservations.emplace_back(
                id,
                studentId,
                examNumber,
                completed,
                score,
                totalQuestions,
                inProgress,
                currentQuestion,
                remainingSeconds);
        }
        catch (const invalid_argument &)
        {
            cout << "Skipping invalid reservation record.\n";
        }
        catch (const out_of_range &)
        {
            cout << "Skipping reservation with out-of-range data.\n";
        }
    }

    while (getline(runningFile, line))
    {
        stringstream stream(line);
        string idText, positionText, detailText, questionText;
        if (!getline(stream, idText, '|') || !getline(stream, positionText, '|') ||
            !getline(stream, detailText, '|') || !getline(stream, questionText)) continue;
        try
        {
            int id = stoi(idText), position = stoi(positionText);
            int detailIndex = stoi(detailText), questionIndex = stoi(questionText);
            for (Reservation &reservation : reservations)
                if (reservation.getId() == id && position >= 0 && position < 10000)
                {
                    auto keys = reservation.getRunningQuestions();
                    if (keys.size() <= static_cast<size_t>(position)) keys.resize(static_cast<size_t>(position + 1), {-1, -1});
                    keys[static_cast<size_t>(position)] = {detailIndex, questionIndex};
                    reservation.setAttempt(keys, reservation.getCurrentQuestion(), reservation.getRemainingSeconds());
                    break;
                }
        }
        catch (const exception &) { cout << "Skipping invalid running-question record.\n"; }
    }
    while (getline(runningAnswersFile, line))
    {
        stringstream stream(line);
        string idText, positionText, answersText;
        if (!getline(stream, idText, '|') || !getline(stream, positionText, '|') || !getline(stream, answersText)) continue;
        try
        {
            int id = stoi(idText), position = stoi(positionText);
            vector<char> answers;
            stringstream answerStream(answersText);
            string answer;
            while (getline(answerStream, answer, ','))
                if (answer.size() == 1) answers.push_back(static_cast<char>(toupper(static_cast<unsigned char>(answer[0]))));
            for (Reservation &reservation : reservations)
                if (reservation.getId() == id && position >= 0)
                    reservation.setSelectedAnswer(static_cast<size_t>(position), answers);
        }
        catch (const exception &) { cout << "Skipping invalid running-answer record.\n"; }
    }

    while (getline(questionFile, line))
    {
        stringstream stream(line);
        string subjectName;
        string field2;
        string type;
        string sectionName;
        string questionText;
        string choices[4];
        string answersText;

        if (!getline(stream, subjectName, '|') || !getline(stream, field2, '|'))
        {
            continue;
        }

        if (field2 == "S" || field2 == "M")
        {
            type = field2;
            sectionName = "General";
        }
        else if (!getline(stream, type, '|') || !getline(stream, questionText, '|'))
            continue;

        if (questionText.empty() && (field2 == "S" || field2 == "M") && !getline(stream, questionText, '|'))
            continue;

        bool validRecord = true;

        for (int i = 0; i < 4; i++)
        {
            if (!getline(stream, choices[i], '|'))
            {
                validRecord = false;
                break;
            }
        }

        if (!validRecord || !getline(stream, answersText))
            continue;

        for (Subject &subject : subjects)
        {
            if (subject.getName() != subjectName)
                continue;

            if (field2 == "S" || field2 == "M")
                subject.addSection("General");
            Section *targetSection = nullptr;
            for (int sectionIndex = 0; sectionIndex < subject.getSectionsCount(); ++sectionIndex)
            {
                Section *candidate = subject.getSection(sectionIndex);
                if (candidate && candidate->getName() == sectionName)
                {
                    targetSection = candidate;
                    break;
                }
            }
            if (!targetSection)
                continue;

            if (type == "S" && answersText.size() == 1)
            {
                char answer = static_cast<char>(
                    toupper(static_cast<unsigned char>(answersText[0])));

                if (answer >= 'A' && answer <= 'D')
                {
                    targetSection->addQuestion(
                        make_unique<SingleChoiceQuestion>(
                            questionText, choices, answer));
                }
            }
            else if (type == "M")
            {
                vector<char> answers;
                stringstream answerStream(answersText);
                string answerText;
                bool validAnswers = true;

                while (getline(answerStream, answerText, ','))
                {
                    if (answerText.size() != 1)
                    {
                        validAnswers = false;
                        break;
                    }

                    char answer = static_cast<char>(
                        toupper(static_cast<unsigned char>(answerText[0])));

                    if (answer < 'A' || answer > 'D')
                    {
                        validAnswers = false;
                        break;
                    }

                    answers.push_back(answer);
                }

                if (validAnswers && !answers.empty())
                {
                    targetSection->addQuestion(
                        make_unique<MultipleChoiceQuestion>(
                            questionText, choices, answers));
                }
            }

            break;
        }
    }
}
