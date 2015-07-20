#ifndef SVM_COMMAND_ADD_H
#define SVM_COMMAND_ADD_H

#include "command.hpp"


using namespace std;

class commandAdd: public command {
public:
    commandAdd(memory *i) { svmMemory = i; };
    string getName() { return "add"; };
    int getNumberOfOperands() { return 4; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            int rSrc1 = parseRegister(cmd[2]);
            int rSrc2 = parseRegister(cmd[3]);
            svmMemory->setRegister(rDest, svmMemory->getRegister(rSrc1) + svmMemory->getRegister(rSrc2));
        }
    };
private:
    memory *svmMemory;
};

#endif
