#ifndef SVM_COMMAND_NOP_H
#define SVM_COMMAND_NOP_H

#include "command.hpp"

using namespace std;

class commandNoOperation: public command {
public:
    commandNoOperation(ofstream *o) { outStream = o; };
    commandNoOperation(memory *i) { svmMemory = i; };
    string name() { return "nop"; };
    bytecode_t mnemonic_code() { return 0; };
    unsigned int operand_size() { return 1; };
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute();
    void write_bytecode(const vector<string>& cmd);
};

#endif
