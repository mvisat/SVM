#ifndef SVM_COMMAND_LB_H
#define SVM_COMMAND_LB_H

#include "command.hpp"


using namespace std;

class commandLoadByte: public command {
public:
    commandLoadByte(memory *i) { svmMemory = i; };
    string getName() { return "lb"; };
    int getNumberOfOperands() { return 4; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            int rSrc = parseRegister(cmd[2]);
            int C = parseConstant(cmd[3]);
            svmMemory->setRegister(rDest,
                svmMemory->getMemory((address_t)svmMemory->getRegister(rSrc) + (address_t)C));
        }
    };
private:
    memory *svmMemory;
};

#endif
