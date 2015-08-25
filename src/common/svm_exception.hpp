#ifndef COMMON_EXCEPTION_H
#define COMMON_EXCEPTION_H

#include <string>
#include <exception>

class svm_exception: public std::exception {
public:
    explicit svm_exception(const std::string& s): msg(s) {};
    virtual ~svm_exception() throw() {};
    virtual const char* what() const throw() {
        return msg.c_str();
    };

private:
    std::string msg;
};

#endif
