#ifndef SVM_COMMAND_JZ_H
#define SVM_COMMAND_JZ_H

#include "command.hpp"

using namespace std;

class commandJumpIfZero: public command {
public:
    commandJumpIfZero(ofstream *o, map<string, vector<counter_t> > *j) { outStream = o; jumpTable = j; }
    commandJumpIfZero(memory *i) { svmMemory = i; }
    string name() { return "jz"; }
    opcode_t opcode() { return 17; }
    unsigned int get_operand_size() { return 3; }
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(index_t rDest, counter_t address);
    void write_bytecode(const vector<string>& cmd);
};

#endif
