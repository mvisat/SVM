#ifndef SVM_COMMAND_NOT_H
#define SVM_COMMAND_NOT_H

#include "command.hpp"

using namespace std;

class commandNot: public command {
public:
    commandNot(ofstream *o) { outStream = o; };
    commandNot(memory *i) { svmMemory = i; };
    string name() { return "not"; };
    mnemonic_t mnemonic_code() { return 8; };
    unsigned int operand_size() { return 3; };
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc);
    void write_bytecode(const vector<string>& cmd);
};

#endif
