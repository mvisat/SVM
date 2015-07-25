#ifndef SVM_COMMAND_START_H
#define SVM_COMMAND_START_H

#include "command.hpp"

using namespace std;

class commandStart: public command {
public:
    commandStart(ofstream *o) { outStream = o; };
    commandStart(memory *i) { svmMemory = i; };
    string name() { return "start"; };
    opcode_t opcode() { return 1; };
    unsigned int get_operand_size() { return 1; };
    void execute(const vector<string>& cmd);
    void execute(const vector<opcode_t>& cmd);
    void execute();
    void write_bytecode(const vector<string>& cmd);
};

#endif
