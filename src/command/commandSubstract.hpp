#ifndef SVM_COMMAND_SUB_H
#define SVM_COMMAND_SUB_H

#include "command.hpp"

using namespace std;

class commandSubstract: public command {
public:
    commandSubstract(ofstream *o) { outStream = o; };
    commandSubstract(memory *i) { svmMemory = i; };
    string name() { return "sub"; };
    mnemonic_t mnemonic_code() { return 4; };
    unsigned int operand_size() { return 4; };
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc1, index_t rSrc2);
    void write_bytecode(const vector<string>& cmd);
};

#endif
