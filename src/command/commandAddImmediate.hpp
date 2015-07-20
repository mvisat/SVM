#ifndef SVM_COMMAND_ADDI_H
#define SVM_COMMAND_ADDI_H

#include "command.hpp"


using namespace std;

class commandAddImmediate: public command {
public:
    commandAddImmediate(memory *i) { svmMemory = i; };
    string getName() { return "addi"; };
    int getNumberOfOperands() { return 4; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            int rSrc = parseRegister(cmd[2]);
            int C = parseConstant(cmd[3]);
            svmMemory->setRegister(rDest, svmMemory->getRegister(rSrc) + (register_t)C);
        }
    };
private:
    memory *svmMemory;
};

#endif
