#ifndef SVM_COMMAND_LOPEN_H
#define SVM_COMMAND_LOPEN_H

#include "command.hpp"


using namespace std;

class commandLibraryOpen: public command {
public:
    commandLibraryOpen(memory *i) { svmMemory = i; };
    string getName() { return "lopen"; };
    int getNumberOfOperands() { return 2; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            string libName = cmd[1];
            svmMemory->loadLib(libName);
        }
    };
private:
    memory *svmMemory;
};

#endif
