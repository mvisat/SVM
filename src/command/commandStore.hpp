#ifndef SVM_COMMAND_STR_H
#define SVM_COMMAND_STR_H

#include "command.hpp"

using namespace std;

class commandStore: public command {
public:
    commandStore(ofstream *o) { outStream = o; };
    commandStore(memory *i) { svmMemory = i; };
    string name() { return "str"; };
    mnemonic_t mnemonic_code() { return 15; };
    unsigned int operand_size() { return 4; };
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, address_t C);
    void write_bytecode(const vector<string>& cmd);
};

#endif
