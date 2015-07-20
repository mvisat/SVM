#ifndef SVM_COMMAND_LT_H
#define SVM_COMMAND_LT_H

#include "command.hpp"


using namespace std;

class commandLessThan: public command {
public:
    commandLessThan(memory *i) { svmMemory = i; };
    string getName() { return "lt"; };
    int getNumberOfOperands() { return 4; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            int rSrc1 = parseRegister(cmd[2]);
            int rSrc2 = parseRegister(cmd[3]);
            svmMemory->setRegister(rDest, svmMemory->getRegister(rSrc1) < svmMemory->getRegister(rSrc2));
        }
    };
private:
    memory *svmMemory;
};

#endif
