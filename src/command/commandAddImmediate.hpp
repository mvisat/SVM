#ifndef SVM_COMMAND_ADDI_H
#define SVM_COMMAND_ADDI_H

#include "command.hpp"

using namespace std;

class commandAddImmediate: public command {
public:
    commandAddImmediate(ofstream *o) { outStream = o; }
    commandAddImmediate(memory *i) { svmMemory = i; }
    string name() { return "addi"; }
    mnemonic_t mnemonic_code() { return 3; }
    unsigned int operand_size() { return 4; }
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, register_t C);
    void write_bytecode(const vector<string>& cmd);
};

#endif
