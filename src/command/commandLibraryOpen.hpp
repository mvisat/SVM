#ifndef SVM_COMMAND_LOPEN_H
#define SVM_COMMAND_LOPEN_H

#include "command.hpp"

using namespace std;

class commandLibraryOpen: public command {
public:
    commandLibraryOpen(ofstream *o) { outStream = o; };
    commandLibraryOpen(memory *i) { svmMemory = i; };
    string name() { return "lopen"; };
    bytecode_t mnemonic_code() { return 24; };
    unsigned int operand_size() { return 2; };
    void execute(const vector<string>& cmd);
    void execute(const vector<bytecode_t>& cmd);
    void execute(const string& lib_name);
    void write_bytecode(const vector<string>& cmd);
};

#endif
