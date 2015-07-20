#ifndef SVM_COMMAND_JR_H
#define SVM_COMMAND_JR_H

#include "command.hpp"


using namespace std;

class commandJumpRegister: public command {
public:
    commandJumpRegister(memory *i) { svmMemory = i; };
    string getName() { return "jr"; };
    int getNumberOfOperands() { return 2; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            svmMemory->setProgramCounter(svmMemory->getRegister(rDest));
        }
    };
private:
    memory *svmMemory;
};

#endif
