#ifndef SVM_COMMAND_JR_H
#define SVM_COMMAND_JR_H

#include "command.hpp"

using namespace std;

class commandJumpRegister: public command {
public:
    commandJumpRegister(ofstream *o, map<string, vector<counter_t> > *j) { outStream = o; jumpTable = j; }
    commandJumpRegister(memory *i) { svmMemory = i; }
    string name() { return "jr"; }
    mnemonic_t mnemonic_code() { return 20; }
    unsigned int operand_size() { return 2; }
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest);
    void write_bytecode(const vector<string>& cmd);
};

#endif
