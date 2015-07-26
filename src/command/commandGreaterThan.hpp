#ifndef SVM_COMMAND_GT_H
#define SVM_COMMAND_GT_H

#include "command.hpp"

using namespace std;

class commandGreaterThan: public command {
public:
    commandGreaterThan(ofstream *o) { outStream = o; }
    commandGreaterThan(memory *i) { svmMemory = i; }
    string name() { return "gt"; }
    bytecode_t mnemonic_code() { return 11; }
    unsigned int operand_size() { return 4; }
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const vector<string>& cmd);
};

#endif
