#include "Reservation.h"
#include <iostream>

using namespace std;

Reservation::Reservation(
    int reservationId,
    int studentId,
    int examNumber,
    bool completed,
    int score,
    int totalQuestions)
    : id(reservationId),
      studentId(studentId),
      examNumber(examNumber),
      completed(completed),
      score(score),
      totalQuestions(totalQuestions)
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

void Reservation::markCompleted(int examScore, int questionCount)
{
    score = examScore;
    totalQuestions = questionCount;
    completed = true;
}

void Reservation::display() const
{
    cout << "Reservation ID: " << id << '\n';
    cout << "Student ID: " << studentId << '\n';
    cout << "Exam Number: " << examNumber << '\n';
    cout << "Status: " << (completed ? "Completed" : "Pending") << '\n';

    if (completed)
    {
        cout << "Score: " << score << " / " << totalQuestions << '\n';
    }
}
