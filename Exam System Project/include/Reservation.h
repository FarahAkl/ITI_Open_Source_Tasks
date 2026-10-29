
#pragma once

class Reservation
{
private:
    int id;
    int studentId;
    int examNumber;
    bool completed;
    int score;
    int totalQuestions;

public:
    Reservation(
        int reservationId,
        int studentId,
        int examNumber,
        bool completed = false,
        int score = 0,
        int totalQuestions = 0);

    int getId() const;
    int getStudentId() const;
    int getExamNumber() const;
    bool isCompleted() const;
    int getScore() const;
    int getTotalQuestions() const;

    void markCompleted(int examScore, int questionCount);
    void display() const;
};
