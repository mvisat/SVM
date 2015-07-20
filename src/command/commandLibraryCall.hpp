#ifndef SVM_COMMAND_LIBC_H
#define SVM_COMMAND_LIBC_H

#include "command.hpp"

#include <iostream>

using namespace std;

class commandLibraryCall: public command {
public:
    commandLibraryCall(memory *i) { svmMemory = i; };
    string getName() { return "libc"; };
    int getNumberOfOperands() { return 4; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            int rDest = parseRegister(cmd[1]);
            int rSrc = parseRegister(cmd[2]);
            string func = cmd[3];
            if (func == "@input") {
                int in;
                cin >> in;
                svmMemory->setRegister(rDest, (register_t)in);
            }
            else if (func == "@output") {
                cout << svmMemory->getRegister(rSrc) << endl;
            }
            else {
                FuncPrototype f = svmMemory->getLibFunction(func);
                if (f) {
                    int registerDummyDest = svmMemory->getRegister(rDest);
                    int registerDummySrc = svmMemory->getRegister(rSrc);
                    f(&registerDummyDest, registerDummySrc, (char*)svmMemory->getMemoryData());
                    svmMemory->setRegister(rDest, (register_t)registerDummyDest);
                }
            }
        }
    };
private:
    memory *svmMemory;
};

#endif
