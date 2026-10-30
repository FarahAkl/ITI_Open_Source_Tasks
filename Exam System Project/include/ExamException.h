#pragma once

#include <stdexcept>
#include <string>

class ExamException : public std::runtime_error
{
public:
    explicit ExamException(const std::string &message)
        : std::runtime_error(message) {}
};
