#ifndef COMMAND_JMP_H
#define COMMAND_JMP_H

#include "command.hpp"

class commandJump: public command {
public:
    commandJump(std::ofstream *o, std::map<std::string, std::vector<counter_t> > *j) { outStream = o; jumpTable = j; }
    commandJump(memory *i) { svmMemory = i; }
    std::string name() { return "jmp"; }
    mnemonic_t mnemonic_code() { return 19; }
    unsigned int operand_size() { return 2; }
    void execute(const std::vector<std::string>& cmd);
    void execute(const std::vector<bytecode_t>& cmd);
    void execute(counter_t address);
    void write_bytecode(const std::vector<std::string>& cmd);
};

#endif
