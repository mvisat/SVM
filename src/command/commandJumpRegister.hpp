#ifndef COMMAND_JR_H
#define COMMAND_JR_H

#include "command.hpp"

class commandJumpRegister: public command {
public:
    commandJumpRegister(std::ofstream *o, std::map<std::string, std::vector<counter_t> > *j) { outStream = o; jumpTable = j; }
    commandJumpRegister(memory *i) { svmMemory = i; }
    std::string name() { return "jr"; }
    mnemonic_t mnemonic_code() { return 20; }
    unsigned int operand_size() { return 2; }
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
