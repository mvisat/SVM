#ifndef SVM_EXCEPTION_H
#define SVM_EXCEPTION_H

#include <string>
#include <exception>

using namespace std;

class svm_exception: public exception {
public:
    explicit svm_exception(const string& s): msg(s) {};
    virtual ~svm_exception() throw() {};
    virtual const char* what() const throw() {
        return msg.c_str();
    };

private:
    string msg;
};

#endif
