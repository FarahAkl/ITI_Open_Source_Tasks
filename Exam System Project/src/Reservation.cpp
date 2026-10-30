#include "Reservation.h"
#include <iostream>

using namespace std;

Reservation::Reservation(
    int reservationId,
    int studentId,
    int examNumber,
    bool completed,
    int score,
    int totalQuestions,
    bool inProgress,
    int currentQuestion,
    int remainingSeconds)
    : id(reservationId),
      studentId(studentId),
      examNumber(examNumber),
      completed(completed),
      score(score),
      totalQuestions(totalQuestions),
      inProgress(inProgress),
      currentQuestion(currentQuestion),
      remainingSeconds(remainingSeconds)
{
}

int Reservation::getId() const
{
    return id;
}

int Reservation::getStudentId() const
{
    return studentId;
}

int Reservation::getExamNumber() const
{
    return examNumber;
}

bool Reservation::isCompleted() const
{
    return completed;
}

int Reservation::getScore() const
{
    return score;
}

int Reservation::getTotalQuestions() const
{
    return totalQuestions;
}

bool Reservation::isInProgress() const { return inProgress; }
int Reservation::getCurrentQuestion() const { return currentQuestion; }
int Reservation::getRemainingSeconds() const { return remainingSeconds; }
const vector<pair<int, int>> &Reservation::getRunningQuestions() const { return runningQuestions; }
const vector<vector<char>> &Reservation::getSelectedAnswers() const { return selectedAnswers; }

void Reservation::setAttempt(const vector<pair<int, int>> &questions, int current, int remaining)
{
    runningQuestions = questions;
    selectedAnswers.resize(questions.size());
    currentQuestion = current;
    remainingSeconds = remaining;
    inProgress = true;
}

void Reservation::setSelectedAnswer(size_t position, const vector<char> &answer)
{
    if (position >= selectedAnswers.size()) return;
    selectedAnswers[position] = answer;
}

void Reservation::markCompleted(int examScore, int questionCount)
{
    score = examScore;
    totalQuestions = questionCount;
    completed = true;
    inProgress = false;
}

void Reservation::display() const
{
    cout << "Reservation ID: " << id << '\n';
    cout << "Student ID: " << studentId << '\n';
    cout << "Exam Number: " << examNumber << '\n';
    cout << "Status: " << (completed ? "Finished" : (inProgress ? "In progress" : "Reserved")) << '\n';

    if (completed)
    {
        cout << "Score: " << score << " / " << totalQuestions << " marks\n";
    }
}
