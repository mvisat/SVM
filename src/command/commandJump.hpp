#ifndef SVM_COMMAND_JMP_H
#define SVM_COMMAND_JMP_H

#include "command.hpp"

using namespace std;

class commandJump: public command {
public:
    commandJump(ofstream *o, map<string, vector<counter_t> > *j) { outStream = o; jumpTable = j; }
    commandJump(memory *i) { svmMemory = i; }
    string name() { return "jmp"; }
    opcode_t opcode() { return 19; }
    unsigned int get_operand_size() { return 2; }
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(counter_t address);
    void write_bytecode(const vector<string>& cmd);
};

#endif