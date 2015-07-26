#ifndef SVM_COMMAND_JAL_H
#define SVM_COMMAND_JAL_H

#include "command.hpp"

using namespace std;

class commandJumpAndLink: public command {
public:
    commandJumpAndLink(ofstream *o, map<string, vector<counter_t> > *j) { outStream = o; jumpTable = j; }
    commandJumpAndLink(memory *i) { svmMemory = i; }
    string name() { return "jal"; }
    mnemonic_t mnemonic_code() { return 21; }
    unsigned int operand_size() { return 3; }
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest, counter_t address);
    void write_bytecode(const vector<string>& cmd);
};

#endif
