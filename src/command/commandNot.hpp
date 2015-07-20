#ifndef SVM_COMMAND_NOT_H
#define SVM_COMMAND_NOT_H

#include "command.hpp"


using namespace std;

class commandNot: public command {
public:
    commandNot(memory *i) { svmMemory = i; };
    string getName() { return "not"; };
    int getNumberOfOperands() { return 3; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            int rSrc = parseRegister(cmd[2]);
            svmMemory->setRegister(rDest, !svmMemory->getRegister(rSrc));
        }
    };
private:
    memory *svmMemory;
};

#endif
