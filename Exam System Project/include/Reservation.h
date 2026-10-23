#pragma once

class Reservation
{
private:
    int id;
    int studentId;
    int examNumber;
    bool completed;

public:
    Reservation(int reservationId, int studentId, int examNumber);

    int getId() const;
    int getStudentId() const;
    int getExamNumber() const;
    bool isCompleted() const;

    void markCompleted();
    void display() const;
};
