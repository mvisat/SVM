#ifndef SVM_COMMAND_NOT_H
#define SVM_COMMAND_NOT_H

#include "command.hpp"

using namespace std;

class commandNot: public command {
public:
    commandNot(ofstream *o) { outStream = o; };
    commandNot(memory *i) { svmMemory = i; };
    string name() { return "not"; };
    opcode_t opcode() { return 8; };
    unsigned int get_operand_size() { return 3; };
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(index_t rDest, index_t rSrc);
    void write_bytecode(const vector<string>& cmd);
};

#endif
