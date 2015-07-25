#ifndef SVM_COMMAND_GT_H
#define SVM_COMMAND_GT_H

#include "command.hpp"

using namespace std;

class commandGreaterThan: public command {
public:
    commandGreaterThan(ofstream *o) { outStream = o; }
    commandGreaterThan(memory *i) { svmMemory = i; }
    string name() { return "gt"; }
    opcode_t opcode() { return 11; }
    unsigned int get_operand_size() { return 4; }
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const vector<string>& cmd);
};

#endif
