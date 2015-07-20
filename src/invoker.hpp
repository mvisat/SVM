#ifndef SVM_INVOKER_H
#define SVM_INVOKER_H

#include "command/command.hpp"

#include <map>
#include <iostream>

using namespace std;

class invoker
{
public:
    invoker() {};

    void add(command *c) {
        if (c != 0) {
            mapOfCommand[c->getName()] = c;
        }
    };
    void execute(const vector<string>& cmd) {
        if (cmd.size() && find(cmd[0])) {
            command *c = mapOfCommand[cmd[0]];
            if (cmd.size() ==  c->getNumberOfOperands())
                c->execute(cmd);
            else
                throw svm_exception("Error: Invalid number of operands for '" + c->getName() + "'");
        }
        else if (cmd.size() && cmd[0] != "#" && cmd[0][0] != '.') {
            throw svm_exception("Error: Invalid syntax '" + cmd[0] + "'");
        }
    };
    bool find(const string& cmdName) {
        return mapOfCommand.find(cmdName) != mapOfCommand.end();
    };

private:
    map<string, command*> mapOfCommand;
};
#endif
