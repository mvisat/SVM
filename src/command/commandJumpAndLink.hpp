#ifndef COMMAND_JAL_H
#define COMMAND_JAL_H

#include "command.hpp"

class commandJumpAndLink: public command {
public:
    commandJumpAndLink(std::ofstream *o, std::map<std::string, std::vector<counter_t> > *j) { outStream = o; jumpTable = j; }
    commandJumpAndLink(memory *i) { svmMemory = i; }
    std::string name() { return "jal"; }
    mnemonic_t mnemonic_code() { return 21; }
    unsigned int operand_size() { return 3; }
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, counter_t address);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
