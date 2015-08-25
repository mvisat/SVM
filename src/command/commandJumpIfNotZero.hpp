#ifndef COMMAND_JNZ_H
#define COMMAND_JNZ_H

#include "command.hpp"

class commandJumpIfNotZero: public command {
public:
    commandJumpIfNotZero(std::ofstream *o, std::map<std::string, std::vector<counter_t> > *j) { outStream = o; jumpTable = j; }
    commandJumpIfNotZero(memory *i) { svmMemory = i; }
    std::string name() { return "jnz"; }
    mnemonic_t mnemonic_code() { return 18; }
    unsigned int operand_size() { return 3; }
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(index_t rDest, counter_t address);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
