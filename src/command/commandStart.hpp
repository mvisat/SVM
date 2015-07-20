#ifndef SVM_COMMAND_START_H
#define SVM_COMMAND_START_H

#include "command.hpp"


using namespace std;

class commandStart: public command {
public:
    commandStart(memory *i) { svmMemory = i; };
    string getName() { return "start"; };
    int getNumberOfOperands() { return 1; };
    void execute(const vector<string>& cmd) {
    };
private:
    memory *svmMemory;
};

#endif
