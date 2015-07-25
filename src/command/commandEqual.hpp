#ifndef SVM_COMMAND_EQ_H
#define SVM_COMMAND_EQ_H

#include "command.hpp"

using namespace std;

class commandEqual: public command {
public:
    commandEqual(ofstream *o) { outStream = o; }
    commandEqual(memory *i) { svmMemory = i; }
    string name() { return "eq"; }
    opcode_t opcode() { return 9; }
    unsigned int get_operand_size() { return 4; }
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const vector<string>& cmd);
};

#endif
