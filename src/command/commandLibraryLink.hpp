#ifndef SVM_COMMAND_LINK_H
#define SVM_COMMAND_LINK_H

#include "command.hpp"

using namespace std;

class commandLibraryLink: public command {
public:
    commandLibraryLink(ofstream *o) { outStream = o; };
    commandLibraryLink(memory *i) { svmMemory = i; };
    string name() { return "link"; };
    opcode_t opcode() { return 25; };
    unsigned int get_operand_size() { return 2; };
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute(const string& function_name);
    void write_bytecode(const vector<string>& cmd);
};

#endif
