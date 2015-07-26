#ifndef SVM_COMMAND_START_H
#define SVM_COMMAND_START_H

#include "command.hpp"

using namespace std;

class commandStart: public command {
public:
    commandStart(ofstream *o) { outStream = o; };
    commandStart(memory *i) { svmMemory = i; };
    string name() { return "start"; };
    mnemonic_t mnemonic_code() { return 1; };
    unsigned int operand_size() { return 1; };
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute();
    void write_bytecode(const vector<string>& cmd);
};

#endif
