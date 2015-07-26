#ifndef SVM_COMMAND_STB_H
#define SVM_COMMAND_STB_H

#include "command.hpp"

using namespace std;

class commandStoreByte: public command {
public:
    commandStoreByte(ofstream *o) { outStream = o; };
    commandStoreByte(memory *i) { svmMemory = i; };
    string name() { return "stb"; };
    bytecode_t mnemonic_code() { return 16; };
    unsigned int operand_size() { return 4; };
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, address_t C);
    void write_bytecode(const vector<string>& cmd);
};

#endif
