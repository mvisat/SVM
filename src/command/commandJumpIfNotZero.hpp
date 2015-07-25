#ifndef SVM_COMMAND_JNZ_H
#define SVM_COMMAND_JNZ_H

#include "command.hpp"

using namespace std;

class commandJumpIfNotZero: public command {
public:
    commandJumpIfNotZero(ofstream *o, map<string, vector<counter_t> > *j) { outStream = o; jumpTable = j; }
    commandJumpIfNotZero(memory *i) { svmMemory = i; }
    string name() { return "jnz"; }
    opcode_t opcode() { return 18; }
    unsigned int get_operand_size() { return 3; }
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(index_t rDest, counter_t address);
    void write_bytecode(const vector<string>& cmd);
};

#endif
