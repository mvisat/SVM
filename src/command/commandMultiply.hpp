#ifndef SVM_COMMAND_MUL_H
#define SVM_COMMAND_MUL_H

#include "command.hpp"

using namespace std;

class commandMultiply: public command {
public:
    commandMultiply(ofstream *o) { outStream = o; };
    commandMultiply(memory *i) { svmMemory = i; };
    string name() { return "mul"; };
    mnemonic_t mnemonic_code() { return 5; };
    unsigned int operand_size() { return 4; };
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const vector<string>& cmd);
};

#endif
