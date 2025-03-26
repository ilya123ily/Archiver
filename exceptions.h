#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <string>

const int ERROR = 111;

class Exception : public std::exception {
public:
    explicit Exception(const std::string& message) : message_{message} {
    }
    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

#endif