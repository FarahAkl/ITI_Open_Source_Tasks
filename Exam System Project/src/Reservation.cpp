#include "Reservation.h"
#include <iostream>
using namespace std;

Reservation::Reservation(int reservationId, int studentId,
                         int examNumber, bool completed)
    : id(reservationId),
      studentId(studentId),
      examNumber(examNumber),
      completed(completed)
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

void Reservation::markCompleted()
{
    completed = true;
}

void Reservation::display() const
{
    cout << "Reservation ID: " << id
         << " | Student ID: " << studentId
         << " | Exam Number: " << examNumber
         << " | Status: " << (completed ? "Completed" : "Pending")
         << '\n';
}
