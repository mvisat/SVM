#ifndef SVM_COMMAND_LDI_H
#define SVM_COMMAND_LDI_H

#include "command.hpp"


using namespace std;

class commandLoadImmediate: public command {
public:
    commandLoadImmediate(memory *i) { svmMemory = i; };
    string getName() { return "ldi"; };
    int getNumberOfOperands() { return 3; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            int C = parseConstant(cmd[2]);
            svmMemory->setRegister(rDest, C);
        }
    };
private:
    memory *svmMemory;
};

#endif
