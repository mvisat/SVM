#ifndef SVM_INVOKER_H
#define SVM_INVOKER_H

#include "command.hpp"

#include <map>
#include <iostream>

using namespace std;

class invoker
{
public:
    invoker();

    void add(command *c);
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd, counter_t pointer);
    void write_bytecode(const vector<string>& cmd);
private:
    map<string, command*> mapOfCommandName;
    vector<command*> mapOfCommandCode;
};

#endif
