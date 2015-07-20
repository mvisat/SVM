#ifndef SVM_COMMAND_JZ_H
#define SVM_COMMAND_JZ_H

#include "command.hpp"


using namespace std;

class commandJumpIfZero: public command {
public:
    commandJumpIfZero(memory *i) { svmMemory = i; };
    string getName() { return "jz"; };
    int getNumberOfOperands() { return 3; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            string label = cmd[2];
            if (svmMemory->getRegister(rDest) == 0)
                svmMemory->setProgramCounter(svmMemory->getLabel(label));
        }
    };
private:
    memory *svmMemory;
};

#endif
