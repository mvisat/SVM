#ifndef SVM_COMMAND_ADD_H
#define SVM_COMMAND_ADD_H

#include "command.hpp"

using namespace std;

class commandAdd: public command {
public:
    commandAdd(ofstream *o) { outStream = o; };
    commandAdd(memory *i) { svmMemory = i; };
    string name() { return "add"; };
    opcode_t opcode() { return 2; };
    unsigned int get_operand_size() { return 4; };
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const vector<string>& cmd);
};

#endif
