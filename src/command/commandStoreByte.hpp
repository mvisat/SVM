#ifndef SVM_COMMAND_STB_H
#define SVM_COMMAND_STB_H

#include "command.hpp"


using namespace std;

class commandStoreByte: public command {
public:
    commandStoreByte(memory *i) { svmMemory = i; };
    string getName() { return "stb"; };
    int getNumberOfOperands() { return 4; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            int rSrc = parseRegister(cmd[2]);
            int C = parseConstant(cmd[3]);
            svmMemory->setMemory(
                (address_t)svmMemory->getRegister(rSrc) + (address_t)C,
                svmMemory->getRegister(rDest) & 0xFF);
        }
    };
private:
    memory *svmMemory;
};

#endif
