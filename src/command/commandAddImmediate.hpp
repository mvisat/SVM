#ifndef SVM_COMMAND_ADDI_H
#define SVM_COMMAND_ADDI_H

#include "command.hpp"

using namespace std;

class commandAddImmediate: public command {
public:
    commandAddImmediate(ofstream *o) { outStream = o; }
    commandAddImmediate(memory *i) { svmMemory = i; }
    string name() { return "addi"; }
    opcode_t opcode() { return 3; }
    unsigned int get_operand_size() { return 4; }
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, register_t C);
    void write_bytecode(const vector<string>& cmd);
};

#endif
