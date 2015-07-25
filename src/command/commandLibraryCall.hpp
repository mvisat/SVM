#ifndef SVM_COMMAND_LIBC_H
#define SVM_COMMAND_LIBC_H

#include "command.hpp"

#include <iostream>

using namespace std;

class commandLibraryCall: public command {
public:
    commandLibraryCall(ofstream *o) { outStream = o; };
    commandLibraryCall(memory *i) { svmMemory = i; };
    string name() { return "libc"; };
    opcode_t opcode() { return 22; };
    unsigned int get_operand_size() { return 4; };
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(index_t rDest, index_t rSrc, const string& func);
    void write_bytecode(const vector<string>& cmd);
};

#endif
