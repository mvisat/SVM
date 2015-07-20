#ifndef SVM_COMMAND_LD_H
#define SVM_COMMAND_LD_H

#include "command.hpp"


using namespace std;

class commandLoad: public command {
public:
    commandLoad(memory *i) { svmMemory = i; };
    string getName() { return "ld"; };
    int getNumberOfOperands() { return 4; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            int rSrc = parseRegister(cmd[2]);
            int C = parseConstant(cmd[3]);
            svmMemory->setRegister(rDest,
                (svmMemory->getMemory((address_t)svmMemory->getRegister(rSrc) + (address_t)C)) |
                (svmMemory->getMemory((address_t)svmMemory->getRegister(rSrc) + (address_t)C + 1) << 8));
        }
    };
private:
    memory *svmMemory;
};

#endif
