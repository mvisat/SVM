#ifndef SVM_COMMAND_LB_H
#define SVM_COMMAND_LB_H

#include "command.hpp"

using namespace std;

class commandLoadByte: public command {
public:
    commandLoadByte(ofstream *o) { outStream = o; };
    commandLoadByte(memory *i) { svmMemory = i; };
    string name() { return "lb"; };
    mnemonic_t mnemonic_code() { return 13; };
    unsigned int operand_size() { return 4; };
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, address_t C);
    void write_bytecode(const vector<string>& cmd);
};

#endif
