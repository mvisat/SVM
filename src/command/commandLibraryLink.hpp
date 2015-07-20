#ifndef SVM_COMMAND_LINK_H
#define SVM_COMMAND_LINK_H

#include "command.hpp"


using namespace std;

class commandLibraryLink: public command {
public:
    commandLibraryLink(memory *i) { svmMemory = i; };
    string getName() { return "link"; };
    int getNumberOfOperands() { return 2; };
    void execute(const vector<string>& cmd) {
        if (svmMemory != 0) {
            string functionName = cmd[1];
            svmMemory->linkLibFunction(functionName);
        }
    };
private:
    memory *svmMemory;
};

#endif
