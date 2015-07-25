#ifndef SVM_COMMAND_LD_H
#define SVM_COMMAND_LD_H

#include "command.hpp"

using namespace std;

class commandLoad: public command {
public:
    commandLoad(ofstream *o) { outStream = o; };
    commandLoad(memory *i) { svmMemory = i; };
    string name() { return "ld"; };
    opcode_t opcode() { return 12; };
    unsigned int get_operand_size() { return 4; };
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, address_t C);
    void write_bytecode(const vector<string>& cmd);
};

#endif