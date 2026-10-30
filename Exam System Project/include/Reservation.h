
#pragma once
#include <utility>
#include <vector>
#include <cstddef>

using std::pair;
using std::size_t;
using std::vector;

class Reservation
{
private:
    int id;
    int studentId;
    int examNumber;
    bool completed;
    int score;
    int totalQuestions;
    bool inProgress;
    int currentQuestion;
    int remainingSeconds;
    vector<pair<int, int>> runningQuestions;
    vector<vector<char>> selectedAnswers;

public:
    Reservation(
        int reservationId,
        int studentId,
        int examNumber,
        bool completed = false,
        int score = 0,
        int totalQuestions = 0,
        bool inProgress = false,
        int currentQuestion = 0,
        int remainingSeconds = 0);

    int getId() const;
    int getStudentId() const;
    int getExamNumber() const;
    bool isCompleted() const;
    int getScore() const;
    int getTotalQuestions() const;
    bool isInProgress() const;
    int getCurrentQuestion() const;
    int getRemainingSeconds() const;
    const vector<pair<int, int>> &getRunningQuestions() const;
    const vector<vector<char>> &getSelectedAnswers() const;
    void setAttempt(const vector<pair<int, int>> &questions, int current, int remaining);
    void setSelectedAnswer(size_t position, const vector<char> &answer);

    void markCompleted(int examScore, int questionCount);
    void display() const;
};
