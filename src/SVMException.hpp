#ifndef SVM_EXCEPTION_H
#define SVM_EXCEPTION_H

#include <exception>

using namespace std;

class SVMException: public exception {
public:
    explicit SVMException(const string& s): msg(s) {};
    virtual ~SVMException() throw() {};
    virtual const char* what() const throw() {
        return msg.c_str();
    };

private:
    string msg;
};

#endif
