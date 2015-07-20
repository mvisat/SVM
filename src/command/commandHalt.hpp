#ifndef SVM_COMMAND_HALT_H
#define SVM_COMMAND_HALT_H

#include "command.hpp"

using namespace std;

class commandHalt: public command {
public:
    commandHalt(memory *i) { svmMemory = i; };
    string getName() { return "halt"; };
    int getNumberOfOperands() { return 1; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            svmMemory->setHalt(true);
        }
    };
private:
    memory *svmMemory;
};

#endif
