#ifndef SVM_COMMAND_JMP_H
#define SVM_COMMAND_JMP_H

#include "command.hpp"


using namespace std;

class commandJump: public command {
public:
    commandJump(memory *i) { svmMemory = i; };
    string getName() { return "jmp"; };
    int getNumberOfOperands() { return 2; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            string label = cmd[1];
            svmMemory->setProgramCounter(svmMemory->getLabel(label));
        }
    };
private:
    memory *svmMemory;
};

#endif
