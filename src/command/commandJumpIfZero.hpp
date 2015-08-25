#ifndef COMMAND_JZ_H
#define COMMAND_JZ_H

#include "command.hpp"

class commandJumpIfZero: public command {
public:
    commandJumpIfZero(std::ofstream *o, std::map<std::string, std::vector<counter_t> > *j) { outStream = o; jumpTable = j; }
    commandJumpIfZero(memory *i) { svmMemory = i; }
    std::string name() { return "jz"; }
    mnemonic_t mnemonic_code() { return 17; }
    unsigned int operand_size() { return 3; }
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, counter_t address);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
