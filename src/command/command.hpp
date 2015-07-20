#ifndef SVM_COMMAND_H
#define SVM_COMMAND_H

#include "../parser.hpp"
#include "../memory.hpp"

#include <vector>

using namespace std;

class command {
public:
    virtual string getName() = 0;
    virtual int getNumberOfOperands() = 0;
    virtual void execute(const vector<string>& cmd) = 0;
};

#endif
