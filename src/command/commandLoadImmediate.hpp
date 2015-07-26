#ifndef SVM_COMMAND_LDI_H
#define SVM_COMMAND_LDI_H

#include "command.hpp"

using namespace std;

class commandLoadImmediate: public command {
public:
    commandLoadImmediate(ofstream *o) { outStream = o; };
    commandLoadImmediate(memory *i) { svmMemory = i; };
    string name() { return "ldi"; };
    mnemonic_t mnemonic_code() { return 14; };
    unsigned int operand_size() { return 3; };
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest, register_t C);
    void write_bytecode(const vector<string>& cmd);
};

#endif
