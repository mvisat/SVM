#ifndef SVM_COMMAND_STR_H
#define SVM_COMMAND_STR_H

#include "command.hpp"


using namespace std;

class commandStore: public command {
public:
    commandStore(memory *i) { svmMemory = i; };
    string getName() { return "str"; };
    int getNumberOfOperands() { return 4; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            int rSrc = parseRegister(cmd[2]);
            int C = parseConstant(cmd[3]);
            svmMemory->setMemory(
                (address_t)svmMemory->getRegister(rSrc) + (address_t)C,
                svmMemory->getRegister(rDest) & 0x00FF);
            svmMemory->setMemory(
                (address_t)svmMemory->getRegister(rSrc) + (address_t)C + 1,
                svmMemory->getRegister(rDest) & 0xFF00);
        }
    };
private:
    memory *svmMemory;
};

#endif
