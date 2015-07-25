#ifndef SVM_COMMAND_HALT_H
#define SVM_COMMAND_HALT_H

#include "command.hpp"

using namespace std;

class commandHalt: public command {
public:
    commandHalt(ofstream *o) { outStream = o; }
    commandHalt(memory *i) { svmMemory = i; }
    string name() { return "halt"; }
    opcode_t opcode() { return 23; }
    unsigned int get_operand_size() { return 1; }
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute();
    void write_bytecode(const vector<string>& cmd);
};

#endif
